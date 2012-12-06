#include "testApp.h"

#define XML_SETTING_FILE "data\\openni\\config\\SamplesConfig.xml"
#define HOST "127.0.0.1"
//#define HOST "192.168.0.108"
#define OSC_PORT 12345

bool cameraViewHidden = false;

//--------------------------------------------------------------
void testApp::setup(){
	simpleNI.setupFromXml(XML_SETTING_FILE);
	simpleNI.start();
	oscSender.setup(HOST, OSC_PORT);

	leftHandPos = -1;
	rightHandPos = -1;
}

//--------------------------------------------------------------
void testApp::update(){
	simpleNI.update();
	
	leftHandPos = getLeftHandPos();
	rightHandPos = getRightHandPos();

	if( leftHandPos >= 0 )
	{
		ofxOscMessage msg;
		msg.setAddress("/hand/left");
		msg.addIntArg(leftHandPos);
		oscSender.sendMessage(msg);
	}

	if( rightHandPos >= 0 )
	{
		ofxOscMessage msg;
		msg.setAddress("/hand/right");
		msg.addIntArg(rightHandPos);
		oscSender.sendMessage(msg);
	}

	if( leftHandPos < 0 && rightHandPos < 0)
	{
		ofxOscMessage msg;
		msg.setAddress("/hand");
		msg.addIntArg(-1);
		oscSender.sendMessage(msg);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	if( !cameraViewHidden ){
		simpleNI.drawColorImg(0,0,0);	

		simpleNI.drawRawDepthImg(0, 480, 0);
		simpleNI.drawScaledDepthImg(640, 480, 0);
	}

	simpleNI.drawSkeleton(0,0,0);

	string str = "framerate is ";                       
	str += ofToString(ofGetFrameRate(), 2)+"fps"; 
	ofSetWindowTitle(str);

	for( int i = 0; i < 3; i++ ){
		int interval = 640/7;

		if( i == leftHandPos){
			ofSetColor(255, 0, 0);
			ofFill();
		}
		ofRect((2*i+1)*interval + 640, 50, 0, interval, interval);
		ofNoFill();
		ofSetColor(255, 255, 255);

		if( i == rightHandPos){
			ofSetColor(0, 255, 0);
			ofFill();
		}
		ofRect((2*i+1)*interval + 640, 150, 0, interval, interval);
		ofNoFill();
		ofSetColor(255, 255, 255);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if( key == 'h' ){
		cameraViewHidden = !cameraViewHidden;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

int testApp::getLeftHandPos()
{
	// get first player id
	int player;
	if( simpleNI.getMiddleNearestUserID(player) ){
		float leftHandX, leftHandY;
		float headX, headY;
		float leftShouldX, leftShouldY;		
		float rightShouldX, rightShouldY;

		if( !simpleNI.getJointPos2D(player, XN_SKEL_LEFT_HAND, leftHandX, leftHandY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_HEAD, headX, headY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_LEFT_SHOULDER, leftShouldX, leftShouldY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_RIGHT_SHOULDER, rightShouldX, rightShouldY) ) return -1;

		/*cout << "leftHand " << leftHandX << " " << leftHandY << endl;
		cout << "head " << headX << " " << headY << endl;
		cout << "leftShoulder " << leftShouldX << " " << leftShouldY << endl;
		cout << "rightShoulder " << rightShouldX << " " << rightShouldY << endl;*/

		if( leftHandY < headY ){
			if( leftHandX < leftShouldX ) return 0;
			if( leftHandX >= leftShouldX && leftHandX < rightShouldX ) return 1;
			if( leftHandX >= rightShouldX ) return 2;
		}
	}

	return -1;
}

int testApp::getRightHandPos()
{
	int player;
	if( simpleNI.getMiddleNearestUserID(player) ){
		float rightHandX, rightHandY;
		float headX, headY;
		float leftShouldX, leftShouldY;		
		float rightShouldX, rightShouldY;

		if( !simpleNI.getJointPos2D(player, XN_SKEL_RIGHT_HAND, rightHandX, rightHandY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_HEAD, headX, headY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_LEFT_SHOULDER, leftShouldX, leftShouldY) ) return -1;
		if( !simpleNI.getJointPos2D(player, XN_SKEL_RIGHT_SHOULDER, rightShouldX, rightShouldY) ) return -1;

		if( rightHandY < headY ){
			if( rightHandX < leftShouldX ) return 0;
			if( rightHandX >= leftShouldX && rightHandX < rightShouldX ) return 1;
			if( rightHandX >= rightShouldX ) return 2;
		}
	}

	return -1;
}