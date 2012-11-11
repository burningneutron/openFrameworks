#include "api.h"

#include <stdio.h>
#include <stdlib.h>

#include<windows.h>

#include "ofMain.h"
#include "ofThread.h"

extern "C"
{
	void contextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctions, const FRENamedFunction** functions)
	{
		*numFunctions = 8;

		FRENamedFunction* func = (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*numFunctions));
		// register methods.
		func[0].name = (const uint8_t*) "getMouseXY";
		func[0].functionData = NULL;
		func[0].function = &getMouseXY;

		func[1].name = (const uint8_t*) "fillBitmapRandomColor";
		func[1].functionData = NULL;
		func[1].function = &fillBitmapRandomColor;

		func[2].name = (const uint8_t*) "openCamera";
		func[2].functionData = NULL;
		func[2].function = &openCamera;

		func[3].name = (const uint8_t*) "startCamera";
		func[3].functionData = NULL;
		func[3].function = &startCamera;

		func[4].name = (const uint8_t*) "updateCameraFrame";
		func[4].functionData = NULL;
		func[4].function = &updateCameraFrame;

		func[5].name = (const uint8_t*) "stopCamera";
		func[5].functionData = NULL;
		func[5].function = &stopCamera;

		func[6].name = (const uint8_t*) "closeCamera";
		func[6].functionData = NULL;
		func[6].function = &closeCamera;

		func[7].name = (const uint8_t*) "getCameraFrameSize";
		func[7].functionData = NULL;
		func[7].function = &getCameraFrameSize;

		*functions = func;
	}

	void contextFinalizer(FREContext ctx)
	{
		return;
	}

	void extensionInitializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
	{
		*ctxInitializer = &contextInitializer;
		*ctxFinalizer = &contextFinalizer;
	}

	void extensionFinalizer(void* extData)
	{
		return;
	}


	FREObject getMouseXY(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		FREObject value = argv[0];

		int x = (int) cursorPos.x;
		int y = (int) cursorPos.y;


		FREObject fX,fY;


		FRENewObjectFromInt32(x,&fX);
		FRENewObjectFromInt32(y,&fY);

		FRESetObjectProperty(value,(const uint8_t*)"x",fX,NULL);                
		FRESetObjectProperty(value,(const uint8_t*)"y",fY,NULL);        

		return NULL;
	}

	FREObject fillBitmapRandomColor(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		FREObject as3Bitmap = argv[0];

		FREBitmapData bitmapData;

		FREAcquireBitmapData(as3Bitmap, &bitmapData);
		// do something
		uint32_t r = rand() % 255;
		uint32_t g = rand() % 255;
		uint32_t b = rand() % 255;

		uint32_t* ptr = bitmapData.bits32;
		int offset = bitmapData.lineStride32 - bitmapData.width;
		int alpha = 255;
		for( uint32_t j = 0; j < bitmapData.height; j++ ){
			for( uint32_t i = 0; i < bitmapData.width; i++ ){
				*ptr++ = (alpha << 24) | (r << 16) | (g << 8) | b;
			}

			ptr += offset;
		}

		FREInvalidateBitmapDataRect(as3Bitmap, 0, 0, bitmapData.width, bitmapData.height);
		FREReleaseBitmapData(as3Bitmap);

		return NULL;
	}

	ofVideoGrabber gGrabber;

	FREObject openCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		gGrabber.initGrabber(1280, 720);

		
		return NULL;
	}

	FREObject getCameraFrameSize(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		int w = gGrabber.getWidth();
		int h = gGrabber.getHeight();

		FREObject fX,fY;

		FRENewObjectFromInt32(w,&fX);
		FRENewObjectFromInt32(h,&fY);

		FREObject value = argv[0];

		FRESetObjectProperty(value,(const uint8_t*)"w",fX,NULL);                
		FRESetObjectProperty(value,(const uint8_t*)"h",fY,NULL);
		return NULL;
	}

	FREObject startCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		return NULL;
	}

	FREObject updateCameraFrame(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		gGrabber.update();
		if( !gGrabber.isFrameNew() ) return NULL;

		FREObject as3Bitmap = argv[0];

		FREBitmapData bitmapData;

		FREAcquireBitmapData(as3Bitmap, &bitmapData);
		// do something
		uint32_t r = rand() % 255;
		uint32_t g = rand() % 255;
		uint32_t b = rand() % 255;

		unsigned char *pixel = gGrabber.getPixels();

		uint32_t* ptr = bitmapData.bits32;
		int offset = bitmapData.lineStride32 - bitmapData.width;
		int alpha = 255;
		for( uint32_t j = 0; j < bitmapData.height; j++ ){
			ptr = bitmapData.bits32 + bitmapData.lineStride32*(bitmapData.height-j-1);
			for( uint32_t i = 0; i < bitmapData.width; i++ ){
				r = *pixel++; g = *pixel++; b = *pixel++;
				*ptr++ = (alpha << 24) | (r << 16) | (g << 8) | b;
			}
		}

		FREInvalidateBitmapDataRect(as3Bitmap, 0, 0, bitmapData.width, bitmapData.height);
		FREReleaseBitmapData(as3Bitmap);

		return NULL;
	}

	FREObject stopCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		return NULL;	
	}

	FREObject closeCamera(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		gGrabber.close();
		return NULL;
	}
};