#pragma once

#include "ofMain.h"

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>
#include <XnPropNames.h>

using std::string;
using std::map;

#define CHECK_RC(nRetVal, what)										\
	if (nRetVal != XN_STATUS_OK)									\
{																\
	printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));\
	assert(0);													\
}

class ofxSimpleNI
{
public:
	ofxSimpleNI();
	~ofxSimpleNI();
	
	void setupFromXml(string xmlFileName);
	//void setupFromONI(string oniFileName);

	void start();
	void stop();

	void update();

	void drawColorImg(float x, float y , float z);
	void drawScaledDepthImg(float x, float y , float z);
	void drawRawDepthImg(float x, float y, float z);
	void drawSkeleton(float x, float y, float z);

	int getPlayerNum();
	bool getFirstUserID(int &id);
	bool getNearestUserID(int &id);
	bool getMiddleNearestUserID(int &id);
	bool getJointPos2D(int userID, XnSkeletonJoint JOINT, float &x, float &y);

	// callbacks
	static void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
	static void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
	static void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie);
	static void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie);
	static void XN_CALLBACK_TYPE UserCalibration_CalibrationComplete(xn::SkeletonCapability& capability, XnUserID nId, XnCalibrationStatus eStatus, void* pCookie);


	xn::Context g_Context;
	xn::ScriptNode g_scriptNode;
	xn::DepthGenerator g_DepthGenerator;
	xn::ImageGenerator g_ImageGenerator;
	xn::UserGenerator g_UserGenerator;
	xn::Player g_Player;

	xn::DepthMetaData g_depthMD;
	xn::ImageMetaData g_imageMD;
	xn::SceneMetaData g_sceanMD;
	float* g_pDepthHist;
	int g_nZRes;


	XnBool g_bNeedPose;
	XnChar g_strPose[20];
	XnBool g_bDrawBackground;
	XnBool g_bDrawPixels;
	XnBool g_bDrawSkeleton;
	XnBool g_bPrintID;
	XnBool g_bPrintState;

	XnBool g_bPrintFrameID;
	XnBool g_bMarkJoints;
	std::map<XnUInt32, std::pair<XnCalibrationStatus, XnPoseDetectionStatus> > m_Errors;

public:

	int colorImgWidth, colorImgHeight;
	int depthImgWidth, depthImgHeight;
	ofImage colorImg;
	ofImage depthImg;
	ofShortImage rawdepthImg;

	ofTrueTypeFont	verdana14;

	bool isNormalizeDepth;

private:
	const XnChar* GetCalibrationErrorString(XnCalibrationStatus error);
	const XnChar* GetPoseErrorString(XnPoseDetectionStatus error);
	void DrawCircle(float x, float y, float radius, float ox, float oy, float oz);
	void DrawJoint(XnUserID player, XnSkeletonJoint eJoint, float ox, float oy, float oz);
	bool DrawLimb(XnUserID player, XnSkeletonJoint eJoint1, XnSkeletonJoint eJoint2, float ox, float oy, float oz);
};