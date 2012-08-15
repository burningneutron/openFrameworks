#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	srv = Poco::Net::ServerSocket(80); 
	ofSetWindowTitle("server");
	ss = srv.acceptConnection();
}

//--------------------------------------------------------------
void testApp::update(){
	
	Poco::Net::SocketStream str(ss);
	str << "HTTP/1.0 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"\r\n"
		"<html><head><title>My 1st Web Server</title></head>"
		"<body><h1>Hello, world!</h1></body></html>"
		<< std::flush;

	cout << "server update" << endl;
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