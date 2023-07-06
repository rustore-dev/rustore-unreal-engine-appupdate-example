// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API UnrealPlayerImpl : public RuStoreListener
	{
	public:
		UnrealPlayerImpl() : RuStoreListener("com/Plugins/RuStoreCore/UnrealPlayerWrapper", "ru/rustore/unitysdk/core/IPlayerProvider") { }
		virtual ~UnrealPlayerImpl() { }
	};
}
