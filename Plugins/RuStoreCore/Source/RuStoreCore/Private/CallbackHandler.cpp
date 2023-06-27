#include "CallbackHandler.h"
#include "Async/Async.h"

void CallbackHandler::AddCallback(TFunction<void()> callback)
{
    AsyncTask(ENamedThreads::GameThread, callback);
}
