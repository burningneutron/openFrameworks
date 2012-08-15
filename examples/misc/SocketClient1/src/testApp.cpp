#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("client");

	client.connect(Poco::Net::SocketAddress("127.0.0.1", 80));

	Poco::Net::SocketStream str(client);
	str << "GET / HTTP/1.1\r\n"
		"Host: 127.0.0.1\r\n"
		"\r\n";
	str.flush();
	Poco::StreamCopier::copyStream(str, std::cout);

}

//--------------------------------------------------------------
void testApp::update(){

	
}

//--------------------------------------------------------------
void testApp::draw(){

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