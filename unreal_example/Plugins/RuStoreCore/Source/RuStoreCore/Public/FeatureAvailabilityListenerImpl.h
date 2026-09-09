#pragma once

#include "CoreMinimal.h"
#include "URuStoreCore.h"
#include "FURuStoreFeatureAvailabilityResult.h"
#include "ResponseListener.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API FeatureAvailabilityListenerImpl : public ResponseListener<FURuStoreFeatureAvailabilityResult>
	{
	protected:
		FURuStoreFeatureAvailabilityResult* ConvertResponse(AndroidJavaObject* responseObject) override;

	public:
		FeatureAvailabilityListenerImpl(
			TFunction<void(long requestId, TSharedPtr<FURuStoreFeatureAvailabilityResult, ESPMode::ThreadSafe>)> onSuccess,
			TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
			TFunction<void(RuStoreListener*)> onFinish
		) : ResponseListener<FURuStoreFeatureAvailabilityResult>("ru/rustore/unrealsdk/core/wrappers/FeatureAvailabilityListenerWrapper", "ru/rustore/unrealsdk/core/callbacks/FeatureAvailabilityListener", onSuccess, onFailure, onFinish)
		{
		}

		virtual ~FeatureAvailabilityListenerImpl();
	};
}
