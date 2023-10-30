// Copyright Epic Games, Inc. All Rights Reserved.

#include "UCompleteUpdateNode.h"

using namespace RuStoreSDK;

UCompleteUpdateNode::UCompleteUpdateNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UCompleteUpdateNode* UCompleteUpdateNode::CompleteUpdateAsync(URuStoreAppUpdateManager* target)
{
    auto node = NewObject<UCompleteUpdateNode>(GetTransientPackage());
    
    target->CompleteUpdate(
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
