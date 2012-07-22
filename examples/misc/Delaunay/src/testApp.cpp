#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackgroundHex(0xfdefc2);

	for( int i = 0; i < 100; i++ ){
		delaunay.addPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandomf());
	}

	delaunay.triangulate();

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofNoFill();
	ofSetColor(0, 0, 0, 0);
	delaunay.draw();
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