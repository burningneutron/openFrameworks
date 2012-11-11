#include "testApp.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"

//--------------------------------------------------------------
void testApp::setup(){
	srv = Poco::Net::ServerSocket(80); 
	ofSetWindowTitle("server");
	ss = srv.acceptConnection();

	try{
		ds.bind(Poco::Net::SocketAddress("127.0.0.1", 321), true);
		//ds.connect(Poco::Net::SocketAddress("127.0.0.1", 321));
	}catch(Poco::Exception &e)
	{
		cout << e.displayText() << endl;
	}
}

//--------------------------------------------------------------
void testApp::update(){
	
	//Poco::Net::SocketStream str(ss);
	//str << "HTTP/1.0 200 OK\r\n"
	//	"Content-Type: text/html\r\n"
	//	"\r\n"
	//	"<html><head><title>My 1st Web Server</title></head>"
	//	"<body><h1>Hello, world!</h1></body></html>"
	//	<< std::flush;

	//cout << "server update" << endl;

	int bufLen = 640*480*3;
	//int bufLen = 10000;
	unsigned char *buf = new unsigned char[bufLen];
	try{
		buf[0] = 's';
		int sendLen = ss.sendBytes(buf, bufLen);
		cout << " send bytes: " << sendLen << endl;
		//int sendLen = ds.sendBytes(buf, bufLen);
		
		//int sendLen = ds.sendTo(buf, bufLen, Poco::Net::SocketAddress("localhost", 321));	
		//int sendLen = ds.sendBytes(buf, bufLen);	
		//cout << "buf len: " << bufLen <<" sendLen: " << sendLen << endl;

		/*Poco::Net::SocketAddress sender;
		int recLen = ds.receiveFrom(buf, bufLen, sender);		
		cout << "buf len: " << bufLen <<" recLen: " << recLen << " Buf[0]" << buf[0] << endl;*/
	}catch(Poco::Exception &e)
	{
		cout << ss.address().toString() << endl;
		cout << e.displayText() << endl;
	}
	delete []buf;

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