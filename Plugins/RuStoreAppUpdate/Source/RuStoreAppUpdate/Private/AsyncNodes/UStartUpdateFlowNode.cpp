// Copyright Epic Games, Inc. All Rights Reserved.

#include "UStartUpdateFlowNode.h"

using namespace RuStoreSDK;

const EURuStoreUpdateFlowResult UStartUpdateFlowNode::errorResponse = EURuStoreUpdateFlowResult::RESULT_CANCELED;

UStartUpdateFlowNode::UStartUpdateFlowNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UStartUpdateFlowNode* UStartUpdateFlowNode::StartUpdateFlowAsync(URuStoreAppUpdateManager* target, EURuStoreAppUpdateOptions appUpdateOptions)
{
    auto node = NewObject<UStartUpdateFlowNode>(GetTransientPackage());
    
    target->StartUpdateFlow(
        appUpdateOptions,
        [node](long requestId, EURuStoreUpdateFlowResult response) {
            node->Success.Broadcast(response, FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(errorResponse, *error);
        }
    );

    return node;
}
