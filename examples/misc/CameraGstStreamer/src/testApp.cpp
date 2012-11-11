#include "testApp.h"
#include <gst/app/gstappsink.h>
#include <gst/app/gstappbuffer.h>

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);

	grabber.initGrabber(320, 240);


	//int quality = settings.getValue("settings:quality",48);
	//int keyframe_freq = settings.getValue("settings:keyframe-freq",64);
	//bool keyframe_auto = settings.getValue("settings:keyframe-auto",true);
	//string server = settings.getValue("settings:server","91.121.134.23");
	//int port = settings.getValue("settings:port",8002);
	//string mount = settings.getValue("settings:mount","kinect.ogg");
	//string passwd = settings.getValue("settings:passwd","myd9v");
	//int width = settings.getValue("settings:width",320);
	//int height = settings.getValue("settings:height",240);

	int quality = 48;
	int keyframe_freq = 64;
	bool keyframe_auto = true;
	string server = "127.0.0.1";
	int port = 8002;
	string mount = "kinect.ogg";
	string passwd = "myd9v";
	int width = 640;
	int height = 480;

	/*"v4l2src device=/dev/video0 ! video/x-raw-yuv,width=320,height=240 ! "
	"queue ! videorate ! video/x-raw-yuv,framerate=25/2 ! "
	"videoscale ! video/x-raw-yuv,width=320,height=240 ! "
	"ffmpegcolorspace ! tee name=tscreen ! queue ! "
	"autovideosink tscreen. ! queue ! "
	"theoraenc quality=16 ! queue ! "
	"oggmux name=mux pulsesrc ! audio/x-raw-int,rate=22050,channels=1 ! queue ! audioconvert ! vorbisenc quality=0.2 ! queue ! mux. mux. ! queue ! "
	"shout2send ip=www.giss.tv port=8000 mount=mountpoint.ogg password=xxxxx streamname= description= genre= url=";*/

	string appsrc;
	string videorate;
	string videoscale;
	if( 1 ){
		appsrc = "appsrc  name=video_src is-live=true do-timestamp=true ! "
				"video/x-raw-rgb,width=640,height=480,depth=24,bpp=24,framerate=30/1,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! queue ! ";
		videorate  = "videorate ! video/x-raw-rgb,depth=24,bpp=24,framerate=25/2,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! ";
		videoscale = "videoscale ! video/x-raw-rgb,width=" + ofToString(width) + ",height=" + ofToString(height) + ",depth=24,bpp=24,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! ";
	}else{
		appsrc = "appsrc  name=video_src is-live=true do-timestamp=true ! "
						"video/x-raw-gray,width=640,height=480,depth=8,bpp=8,framerate=30/1 ! queue ! ";
		videorate  = "videorate ! video/x-raw-gray,depth=8,bpp=8,framerate=25/2 ! ";
		videoscale = "videoscale ! video/x-raw-gray,width=" + ofToString(width) + ",height=" + ofToString(height) + ",depth=8,bpp=8 ! ";
	}


	string colorspace = " ffmpegcolorspace ! video/x-raw-yuv,width=" + ofToString(width) + ",height=" + ofToString(height) + " ! ";
	string theoraenc = ofVAArgsToString("theoraenc quality=%d keyframe-auto=%s keyframe-freq=%d ! queue ! ",quality,keyframe_auto?"true":"false",keyframe_freq);
	string audio = "oggmux name=mux pulsesrc ! audio/x-raw-int,rate=22050,channels=1 ! queue ! audioconvert ! vorbisenc quality=0.2 ! queue ! mux. mux. ! queue ! ";
	string shoutcast = ofVAArgsToString("shout2send name=shoutsink ip=%s port=%d mount=%s password=%s streamname= description= genre= url=",server.c_str(),port,mount.c_str(),passwd.c_str());


	string pipeline = appsrc + videorate + videoscale + colorspace + theoraenc + audio + shoutcast;


			/*ofVAArgsToString("appsrc  name=video_src is-live=true do-timestamp=true ! "
			"video/x-raw-rgb,width=640,height=480,depth=24,bpp=24,framerate=30/1,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! queue ! "
			"videorate ! video/x-raw-rgb,depth=24,bpp=24,framerate=25/2,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! videoscale ! "
			"video/x-raw-rgb,width=%d,height=%d,depth=24,bpp=24,endianness=4321,red_mask=16711680, green_mask=65280, blue_mask=255 ! ffmpegcolorspace ! "
			"video/x-raw-yuv,width=%d,height=%d ! theoraenc quality=%d keyframe-auto=%s keyframe-freq=%d ! "
			"oggmux ! shout2send name=shoutsink ip=%s port=%d mount=%s password=%s streamname= description= genre= url="
			,width,height,width,height,quality,keyframe_auto?"true":"false",keyframe_freq,server.c_str(),port,mount.c_str(),passwd.c_str());*/


	gst.setPipelineWithSink(pipeline,"shoutsink",false);
	gstSrc = (GstAppSrc*)gst_bin_get_by_name(GST_BIN(gst.getPipeline()),"video_src");
	if(gstSrc){
		gst_app_src_set_stream_type (gstSrc,GST_APP_STREAM_TYPE_STREAM);
		g_object_set (G_OBJECT(gstSrc), "format", GST_FORMAT_TIME, NULL);
	}

	pixels.allocate(640,480,OF_IMAGE_COLOR);

	gst.play();
}

//--------------------------------------------------------------
void testApp::update(){
	grabber.update();
	
	if(grabber.isFrameNew()){
		GstBuffer * buffer;
		if( 1 ){
			unsigned char * lpBits24 = grabber.getPixels();
			memcpy(pixels.getPixels(), lpBits24, 640*480*3);
			//for(int i=0;i<640*480;i++){
			//	int nPos24 = i*3;
			//	
			//		pixels[nPos24] = lpBits24[;
			//		pixels[nPos24+1] = (lpBits24[i*3]+lpBits24[i*3+1]+lpBits24[i*3+2])*.3333;
			//		pixels[nPos24+2] =  0;
			//	
			//}
			buffer = gst_app_buffer_new (pixels.getPixels(), 640*480*3, NULL, pixels.getPixels());
		}

		GstFlowReturn flow_return = gst_app_src_push_buffer(gstSrc, buffer);
		if (flow_return != GST_FLOW_OK) {
			ofLog(OF_LOG_WARNING,"error pushing buffer");
		}
		gst.update();
	}

	grabber.draw(0,0);
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