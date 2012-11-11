#ifndef __MM_BACKEND_API_H__
#define __MM_BACKEND_API_H__

#include "FlashRuntimeExtensions.h"
#define MM_API  __declspec(dllexport)

extern "C"
{
	MM_API void extensionInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet);
	MM_API void extensionFinalizer(void* extData);
	MM_API FREObject getMouseXY(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
	MM_API FREObject fillBitmapRandomColor(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);

	MM_API FREObject openCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
	MM_API FREObject startCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);	
	MM_API FREObject updateCameraFrame(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
	MM_API FREObject stopCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
	MM_API FREObject closeCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
	MM_API FREObject getCameraFrameSize(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
};
#endif