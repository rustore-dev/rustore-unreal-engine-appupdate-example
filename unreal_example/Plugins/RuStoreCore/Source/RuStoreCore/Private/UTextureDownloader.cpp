// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTextureDownloader.h"
#include "AndroidJavaClass.h"
#include "Async/Async.h"
#include "Serialization/BulkData.h"

using namespace RuStoreSDK;

UTextureDownloader::UTextureDownloader(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UTextureDownloader* UTextureDownloader::DownloadImage(FString url)
{
    UTextureDownloader* blueprintNode = NewObject<UTextureDownloader>(GetTransientPackage());
    blueprintNode->Start(url, blueprintNode);
    return blueprintNode;
}

void UTextureDownloader::Start(const FString url, UTextureDownloader* object)
{
    AsyncTask(ENamedThreads::AnyThread, [url, object]()
        {
            auto texture2D = object->DownloadImageAsTexture2D(url);

            AsyncTask(ENamedThreads::GameThread, [object, texture2D]()
                {
                    if (texture2D != nullptr)
                    {
                        object->Complete.Broadcast(texture2D);
                    }
                    else
                    {
                        object->Failure.Broadcast();
                    }
	            });
        });
}

UTexture2D* UTextureDownloader::DownloadImageAsTexture2D(FString url)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    AndroidJavaObject* image = javaClass->CallStaticAJObject("DownloadImage", "Lcom/Plugins/RuStoreCore/RuStoreImage;", url);

    int32 srcWidth = image->GetInt("width");
    int32 srcHeight = image->GetInt("height");
    TArray<uint8>* rawData = image->GetByteArray("bgra");
    bool isComplete = image->GetBool("isComplete");

    if (!isComplete)
    {
        delete rawData;
        delete image;
        return nullptr;
    }

    UTexture2D* texture2D = UTexture2D::CreateTransient(srcWidth, srcHeight, EPixelFormat::PF_B8G8R8A8);
    void* data = texture2D->PlatformData->Mips[0].BulkData.Lock(EBulkDataLockFlags::LOCK_READ_WRITE);
    FMemory::Memcpy(data, rawData->GetData(), rawData->Num());
    texture2D->PlatformData->Mips[0].BulkData.Unlock();
    texture2D->UpdateResource();
    texture2D->Filter = TextureFilter::TF_Trilinear;

    delete rawData;
    delete image;

    return texture2D;
}
