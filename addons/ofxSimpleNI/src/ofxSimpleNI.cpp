#include "ofxSimpleNI.h"

XnFloat Colors[][3] =
{
	{0,1,1},
	{0,0,1},
	{0,1,0},
	{1,1,0},
	{1,0,0},
	{1,.5,0},
	{.5,1,0},
	{0,.5,1},
	{.5,0,1},
	{1,1,.5},
	{1,1,1}
};
XnUInt32 nColors = 10;

ofxSimpleNI::ofxSimpleNI()
{
	g_pDepthHist = 0;
	g_bNeedPose = FALSE;
	g_strPose[0] = '\0';
	g_bDrawBackground = TRUE;
	g_bDrawPixels = TRUE;
	g_bDrawSkeleton = TRUE;
	g_bPrintID = TRUE;
	g_bPrintState = TRUE;

	g_bPrintFrameID = TRUE;
	g_bMarkJoints = TRUE;

	verdana14.loadFont("openni\\font\\verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
}

ofxSimpleNI::~ofxSimpleNI()
{
	//g_scriptNode.Release();
	g_DepthGenerator.Release();
	g_UserGenerator.Release();
	//g_Player.Release();
	g_Context.Release();
}

void ofxSimpleNI::setupFromXml(string xmlFileName)
{
	XnStatus nRetVal = XN_STATUS_OK;
	xn::EnumerationErrors errors;

	//string ofXmlFileName = ofToDataPath(xmlFileName); // of007 hack to make sure ofSetRootPath is done!
	nRetVal = g_Context.InitFromXmlFile(xmlFileName.c_str(), g_scriptNode, &errors);
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		
		assert(0);
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));

		assert(0);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		assert(0);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_IMAGE, g_ImageGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		printf("No image node exists! Check your XML.");
		assert(0);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationStart, hCalibrationComplete, hPoseDetected, hCalibrationInProgress, hPoseInProgress;
	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
	{
		printf("Supplied user generator doesn't support skeleton\n");
		assert(0);
	}
	nRetVal = g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, this, hUserCallbacks);
	CHECK_RC(nRetVal, "Register to user callbacks");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationStart(UserCalibration_CalibrationStart, this, hCalibrationStart);
	CHECK_RC(nRetVal, "Register to calibration start");
	nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationComplete(UserCalibration_CalibrationComplete, this, hCalibrationComplete);
	CHECK_RC(nRetVal, "Register to calibration complete");

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
	{
		printf("No need to calibrate\n");
		assert(0);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	/*nRetVal = g_UserGenerator.GetSkeletonCap().RegisterToCalibrationInProgress(MyCalibrationInProgress, this, hCalibrationInProgress);
	CHECK_RC(nRetVal, "Register to calibration in progress");*/

}

void ofxSimpleNI::start()
{
	XnStatus nRetVal = XN_STATUS_OK;
	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");
	
	g_Context.WaitAndUpdateAll();

	
}

void ofxSimpleNI::stop()
{

}

void ofxSimpleNI::update()
{
	// Read next available data
	g_Context.WaitAndUpdateAll();
	//g_Context.WaitOneUpdateAll(g_UserGenerator);
	//g_DepthGenerator.WaitAndUpdateData();

	// Process the data
	g_DepthGenerator.GetMetaData(g_depthMD);
	g_ImageGenerator.GetMetaData(g_imageMD);
	g_UserGenerator.GetUserPixels(0, g_sceanMD);

	// width, height;
	depthImgWidth = g_depthMD.XRes();
	depthImgHeight = g_depthMD.YRes();

	colorImgWidth = g_imageMD.XRes();
	colorImgHeight = g_imageMD.YRes();

	g_nZRes = g_depthMD.ZRes();
	if( g_pDepthHist == 0 ){
		g_pDepthHist = (float*)malloc(g_nZRes * sizeof(float));
	}
	memset(g_pDepthHist, 0, g_nZRes*sizeof(float));

	//printf("depth width %d, depth height %d\n", depthImgWidth, depthImgHeight);

	// allocate buffer
	rawdepthImg.allocate(depthImgWidth, depthImgHeight, OF_IMAGE_GRAYSCALE);
	depthImg.allocate(depthImgWidth, depthImgHeight, OF_IMAGE_GRAYSCALE);
	colorImg.allocate(colorImgWidth, colorImgHeight, OF_IMAGE_COLOR);

	// copy to ofxImage
	const XnDepthPixel* pDepth = g_depthMD.Data();
	unsigned int nNumberOfPoints = 0;
	for (XnUInt y = 0; y < g_depthMD.YRes(); ++y)
	{
		for (XnUInt x = 0; x < g_depthMD.XRes(); ++x, ++pDepth)
		{
			if (*pDepth != 0)
			{
				g_pDepthHist[*pDepth]++;
				nNumberOfPoints++;
			}
		}
	}
	for (int nIndex=1; nIndex<g_nZRes; nIndex++)
	{
		g_pDepthHist[nIndex] += g_pDepthHist[nIndex-1];
	}
	if (nNumberOfPoints)
	{
		for (int nIndex=1; nIndex<g_nZRes; nIndex++)
		{
			g_pDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (g_pDepthHist[nIndex] / nNumberOfPoints)));
		}
	}

	for(int y = 0; y < g_depthMD.YRes(); y++){
		const XnDepthPixel *rawDepth = g_depthMD.Data() + g_depthMD.XRes() * y;
		unsigned char *scaledDepth = depthImg.getPixels() + (int)depthImg.getWidth() * y;
		int ZRes = g_depthMD.ZRes();
		for(int x = 0; x < g_depthMD.XRes(); x++){
			//*scaledDepth++ = *rawDepth * 255 / ZRes;
			//*scaledDepth++ = *rawDepth * 255 / ZRes;
			//*scaledDepth++ = *rawDepth * 255 / ZRes;
			//rawDepth++;
			if (*rawDepth != 0)
			{
				int nHistValue = g_pDepthHist[*rawDepth];
				*scaledDepth++ = nHistValue;
			}else{
				*scaledDepth++ = 0;
			}
			rawDepth++;

		}
	}

	rawdepthImg.setFromPixels(g_depthMD.Data(), g_depthMD.XRes(), g_depthMD.YRes(), OF_IMAGE_GRAYSCALE);
	colorImg.setFromPixels(g_imageMD.Data(), g_imageMD.XRes(), g_imageMD.YRes(), OF_IMAGE_COLOR);
}

void ofxSimpleNI::drawColorImg(float x, float y , float z)
{
	colorImg.draw(x, y, z);
}

void ofxSimpleNI::drawScaledDepthImg(float x, float y , float z)
{
	depthImg.draw(x, y, z);
}

void ofxSimpleNI::drawRawDepthImg(float x, float y , float z)
{
	rawdepthImg.draw(x, y, z);
}

void ofxSimpleNI::drawSkeleton(float x, float y, float z)
{
	char strLabel[50] = "";
	XnUserID aUsers[15];
	XnUInt16 nUsers = 15;
	g_UserGenerator.GetUsers(aUsers, nUsers);
	for (int i = 0; i < nUsers; ++i)
	{
		if (g_bPrintID)
		{
			XnPoint3D com;
			g_UserGenerator.GetCoM(aUsers[i], com);
			g_DepthGenerator.ConvertRealWorldToProjective(1, &com, &com);

			XnUInt32 nDummy = 0;

			xnOSMemSet(strLabel, 0, sizeof(strLabel));
			if (!g_bPrintState)
			{
				// Tracking
				xnOSStrFormat(strLabel, sizeof(strLabel), &nDummy, "%d", aUsers[i]);
			}
			else if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]))
			{
				// Tracking
				xnOSStrFormat(strLabel, sizeof(strLabel), &nDummy, "%d - Tracking", aUsers[i]);
			}
			else if (g_UserGenerator.GetSkeletonCap().IsCalibrating(aUsers[i]))
			{
				// Calibrating
				xnOSStrFormat(strLabel, sizeof(strLabel), &nDummy, "%d - Calibrating [%s]", aUsers[i], GetCalibrationErrorString(m_Errors[aUsers[i]].first));
			}
			else
			{
				// Nothing
				xnOSStrFormat(strLabel, sizeof(strLabel), &nDummy, "%d - Looking for pose [%s]", aUsers[i], GetPoseErrorString(m_Errors[aUsers[i]].second));
			}


			glColor4f(1-Colors[i%nColors][0], 1-Colors[i%nColors][1], 1-Colors[i%nColors][2], 1);

			//glRasterPos2i(com.X, com.Y);
			verdana14.drawString(strLabel, com.X, com.Y);
			glColor4f(1.f, 1.f, 1.f, 1.f);
		}

		if (g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]))
		{
			glColor4f(1-Colors[aUsers[i]%nColors][0], 1-Colors[aUsers[i]%nColors][1], 1-Colors[aUsers[i]%nColors][2], 1);

			// Draw Joints
			if (g_bMarkJoints)
			{
				// Try to draw all joints
				DrawJoint(aUsers[i], XN_SKEL_HEAD, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_NECK, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_TORSO, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_WAIST, x, y, z);

				DrawJoint(aUsers[i], XN_SKEL_LEFT_COLLAR, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_SHOULDER, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_ELBOW, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_WRIST, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_HAND, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_FINGERTIP, x, y, z);

				DrawJoint(aUsers[i], XN_SKEL_RIGHT_COLLAR, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_SHOULDER, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_ELBOW, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_WRIST, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_HAND, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_FINGERTIP, x, y, z);

				DrawJoint(aUsers[i], XN_SKEL_LEFT_HIP, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_KNEE, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_ANKLE, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_LEFT_FOOT, x, y, z);

				DrawJoint(aUsers[i], XN_SKEL_RIGHT_HIP, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_KNEE, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_ANKLE, x, y, z);
				DrawJoint(aUsers[i], XN_SKEL_RIGHT_FOOT, x, y, z);
			}

			glColor4f(1.f, 1.f, 1.f, 1.f);
		}

		glBegin(GL_LINES);

		// Draw Limbs
		DrawLimb(aUsers[i], XN_SKEL_HEAD, XN_SKEL_NECK, x, y, z);

		DrawLimb(aUsers[i], XN_SKEL_NECK, XN_SKEL_LEFT_SHOULDER, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_LEFT_SHOULDER, XN_SKEL_LEFT_ELBOW, x, y, z);
		if (!DrawLimb(aUsers[i], XN_SKEL_LEFT_ELBOW, XN_SKEL_LEFT_WRIST, x, y, z))
		{
			DrawLimb(aUsers[i], XN_SKEL_LEFT_ELBOW, XN_SKEL_LEFT_HAND, x, y, z);
		}
		else
		{
			DrawLimb(aUsers[i], XN_SKEL_LEFT_WRIST, XN_SKEL_LEFT_HAND, x, y, z);
			DrawLimb(aUsers[i], XN_SKEL_LEFT_HAND, XN_SKEL_LEFT_FINGERTIP, x, y, z);
		}


		DrawLimb(aUsers[i], XN_SKEL_NECK, XN_SKEL_RIGHT_SHOULDER, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_RIGHT_SHOULDER, XN_SKEL_RIGHT_ELBOW, x, y, z);
		if (!DrawLimb(aUsers[i], XN_SKEL_RIGHT_ELBOW, XN_SKEL_RIGHT_WRIST, x, y, z))
		{
			DrawLimb(aUsers[i], XN_SKEL_RIGHT_ELBOW, XN_SKEL_RIGHT_HAND, x, y, z);
		}
		else
		{
			DrawLimb(aUsers[i], XN_SKEL_RIGHT_WRIST, XN_SKEL_RIGHT_HAND, x, y, z);
			DrawLimb(aUsers[i], XN_SKEL_RIGHT_HAND, XN_SKEL_RIGHT_FINGERTIP, x, y, z);
		}

		DrawLimb(aUsers[i], XN_SKEL_LEFT_SHOULDER, XN_SKEL_TORSO, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_RIGHT_SHOULDER, XN_SKEL_TORSO, x, y, z);

		DrawLimb(aUsers[i], XN_SKEL_TORSO, XN_SKEL_LEFT_HIP, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_LEFT_HIP, XN_SKEL_LEFT_KNEE, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_LEFT_KNEE, XN_SKEL_LEFT_FOOT, x, y, z);

		DrawLimb(aUsers[i], XN_SKEL_TORSO, XN_SKEL_RIGHT_HIP, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_RIGHT_HIP, XN_SKEL_RIGHT_KNEE, x, y, z);
		DrawLimb(aUsers[i], XN_SKEL_RIGHT_KNEE, XN_SKEL_RIGHT_FOOT, x, y, z);

		DrawLimb(aUsers[i], XN_SKEL_LEFT_HIP, XN_SKEL_RIGHT_HIP, x, y, z);
		glEnd();
	}
}

const XnChar* ofxSimpleNI::GetCalibrationErrorString(XnCalibrationStatus error)
{
	switch (error)
	{
	case XN_CALIBRATION_STATUS_OK:
		return "OK";
	case XN_CALIBRATION_STATUS_NO_USER:
		return "NoUser";
	case XN_CALIBRATION_STATUS_ARM:
		return "Arm";
	case XN_CALIBRATION_STATUS_LEG:
		return "Leg";
	case XN_CALIBRATION_STATUS_HEAD:
		return "Head";
	case XN_CALIBRATION_STATUS_TORSO:
		return "Torso";
	case XN_CALIBRATION_STATUS_TOP_FOV:
		return "Top FOV";
	case XN_CALIBRATION_STATUS_SIDE_FOV:
		return "Side FOV";
	case XN_CALIBRATION_STATUS_POSE:
		return "Pose";
	default:
		return "Unknown";
	}
}

const XnChar* ofxSimpleNI::GetPoseErrorString(XnPoseDetectionStatus error)
{
	switch (error)
	{
	case XN_POSE_DETECTION_STATUS_OK:
		return "OK";
	case XN_POSE_DETECTION_STATUS_NO_USER:
		return "NoUser";
	case XN_POSE_DETECTION_STATUS_TOP_FOV:
		return "Top FOV";
	case XN_POSE_DETECTION_STATUS_SIDE_FOV:
		return "Side FOV";
	case XN_POSE_DETECTION_STATUS_ERROR:
		return "General error";
	default:
		return "Unknown";
	}
}

static const float DEG2RAD = 3.14159/180;
void  ofxSimpleNI::DrawCircle(float x, float y, float radius, float ox, float oy, float oz)
{
	glBegin(GL_TRIANGLE_FAN);

	for (int i=0; i < 360; i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex3f(x + cos(degInRad)*radius + ox, y + sin(degInRad)*radius + oy, oz);
	}

	glEnd();
}
void ofxSimpleNI::DrawJoint(XnUserID player, XnSkeletonJoint eJoint, float ox, float oy, float oz)
{
	if (!g_UserGenerator.GetSkeletonCap().IsTracking(player))
	{
		printf("not tracked!\n");
		return;
	}

	if (!g_UserGenerator.GetSkeletonCap().IsJointActive(eJoint))
	{
		return;
	}

	XnSkeletonJointPosition joint;
	g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, eJoint, joint);

	if (joint.fConfidence < 0.5)
	{
		return;
	}

	XnPoint3D pt;
	pt = joint.position;

	g_DepthGenerator.ConvertRealWorldToProjective(1, &pt, &pt);

	DrawCircle(pt.X, pt.Y, 2, ox, oy, oz);
}

bool ofxSimpleNI::DrawLimb(XnUserID player, XnSkeletonJoint eJoint1, XnSkeletonJoint eJoint2, float ox, float oy, float oz)
{
	if (!g_UserGenerator.GetSkeletonCap().IsTracking(player))
	{
		printf("not tracked!\n");
		return true;
	}

	if (!g_UserGenerator.GetSkeletonCap().IsJointActive(eJoint1) ||
		!g_UserGenerator.GetSkeletonCap().IsJointActive(eJoint2))
	{
		return false;
	}

	XnSkeletonJointPosition joint1, joint2;
	g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, eJoint1, joint1);
	g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, eJoint2, joint2);

	if (joint1.fConfidence < 0.5 || joint2.fConfidence < 0.5)
	{
		return true;
	}

	XnPoint3D pt[2];
	pt[0] = joint1.position;
	pt[1] = joint2.position;

	g_DepthGenerator.ConvertRealWorldToProjective(2, pt, pt);
	glVertex3i(pt[0].X + ox, pt[0].Y + oy, 0);
	glVertex3i(pt[1].X + ox, pt[1].Y + oy, 0);

	return true;
}

// Callback: New user was detected
void XN_CALLBACK_TYPE ofxSimpleNI::User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	ofxSimpleNI *simpleNI = static_cast<ofxSimpleNI*>(pCookie);
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d New User %d\n", epochTime, nId);
	// New user found
	if (simpleNI->g_bNeedPose)
	{
		simpleNI->g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(simpleNI->g_strPose, nId);
	}
	else
	{
		simpleNI->g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
}

// Callback: An existing user was lost
void XN_CALLBACK_TYPE ofxSimpleNI::User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	ofxSimpleNI *simpleNI = static_cast<ofxSimpleNI*>(pCookie);
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Lost user %d\n", epochTime, nId);	
}

// Callback: Detected a pose
void XN_CALLBACK_TYPE ofxSimpleNI::UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
{
	ofxSimpleNI *simpleNI = static_cast<ofxSimpleNI*>(pCookie);
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Pose %s detected for user %d\n", epochTime, strPose, nId);
	simpleNI->g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
	simpleNI->g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}

// Callback: Started calibration
void XN_CALLBACK_TYPE ofxSimpleNI::UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
{
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	printf("%d Calibration started for user %d\n", epochTime, nId);
}

// Callback: Finished calibration
void XN_CALLBACK_TYPE ofxSimpleNI::UserCalibration_CalibrationComplete(xn::SkeletonCapability& capability, XnUserID nId, XnCalibrationStatus eStatus, void* pCookie)
{
	ofxSimpleNI *simpleNI = static_cast<ofxSimpleNI*>(pCookie);
	XnUInt32 epochTime = 0;
	xnOSGetEpochTime(&epochTime);
	if (eStatus == XN_CALIBRATION_STATUS_OK)
	{
		// Calibration succeeded
		printf("%d Calibration complete, start tracking user %d\n", epochTime, nId);		
		simpleNI->g_UserGenerator.GetSkeletonCap().StartTracking(nId);
	}
	else
	{
		// Calibration failed
		printf("%d Calibration failed for user %d\n", epochTime, nId);
		if(eStatus==XN_CALIBRATION_STATUS_MANUAL_ABORT)
		{
			printf("Manual abort occured, stop attempting to calibrate!");
			return;
		}
		if (simpleNI->g_bNeedPose)
		{
			simpleNI->g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(simpleNI->g_strPose, nId);
		}
		else
		{
			simpleNI->g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}
}