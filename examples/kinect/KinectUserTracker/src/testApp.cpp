#include "testApp.h"

//#define XML_SETTING_FILE "bin\\data\\openni\\config\\SamplesConfig.xml"
#define XML_SETTING_FILE "data\\openni\\config\\SamplesConfig.xml"

//--------------------------------------------------------------
void testApp::setup(){
	simpleNI.setupFromXml(XML_SETTING_FILE);
	simpleNI.start();
}

//--------------------------------------------------------------
void testApp::update(){
	simpleNI.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	simpleNI.drawColorImg(0,0,0);
	simpleNI.drawScaledDepthImg(640, 0, 0);
	simpleNI.drawSkeleton(0,0,0);
	simpleNI.drawRawDepthImg(0, 480, 0);

	string str = "framerate is ";                       
	str += ofToString(ofGetFrameRate(), 2)+"fps"; 
	ofSetWindowTitle(str);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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