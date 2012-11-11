#include "testApp.h"
#include "Poco/Net/SocketAddress.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("client");

	tcpClient.connect(Poco::Net::SocketAddress("127.0.0.1", 80));
	//try{
	//	udpClient.setReuseAddress(true);
	//	//udpClient.bind(Poco::Net::SocketAddress("127.0.0.1", 321), true);		
	//	udpClient.connect(Poco::Net::SocketAddress("127.0.0.1", 321));		
	//	udpClient.setReceiveTimeout(1000);

	//	cout << udpClient.available() << endl;
	//	cout << udpClient.address().toString() << endl;
	//}catch(Poco::Exception &e){
	//	cout <<  e.displayText() << endl;
	//}

	/*Poco::Net::SocketStream str(client);
	str << "GET / HTTP/1.1\r\n"
		"Host: 127.0.0.1\r\n"
		"\r\n";
	str.flush();
	Poco::StreamCopier::copyStream(str, std::cout);*/

}

//--------------------------------------------------------------
void testApp::update(){

	int bufLen = 640*480*3;
	unsigned char *buf = new unsigned char[bufLen];
	Poco::Timespan span(250000);
	//if (udpClient.poll(span, Poco::Net::Socket::SELECT_READ))
	{
		try{
			int recLen = tcpClient.receiveBytes(buf, bufLen);
			//Poco::Net::SocketAddress sender;
			//int recLen = udpClient.sendBytes(buf, bufLen);
			////int recLen = udpClient.receiveFrom(buf, bufLen, sender);
			//cout << "buf len: " << bufLen <<" recLen: " << recLen <<  "buf[0]: " << buf[0] << endl;

		}catch(Poco::Exception &e){
			cout <<  e.displayText() << endl;
		}
	}/*else{
		cout << " cannot read " << endl;
	}*/
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