// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGetAppUpdateInfoNode.h"

using namespace RuStoreSDK;

UGetAppUpdateInfoNode::UGetAppUpdateInfoNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UGetAppUpdateInfoNode* UGetAppUpdateInfoNode::GetAppUpdateInfoAsync(URuStoreAppUpdateManager* target)
{
    auto node = NewObject<UGetAppUpdateInfoNode>(GetTransientPackage());
    
    target->GetAppUpdateInfo(
        [node](long requestId, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe> response) {
            node->Success.Broadcast(*response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(FURuStoreAppUpdateInfo(), *error);
        }
    );

    return node;
}
