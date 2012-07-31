#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//Replace the default ofGLRenderer with ofxSosoRenderer which has overriden setupScreen() and setupScreenPerspective(). 
	//This lets us set up the scene graph how we want to. 
	//Warning: Up is up and down is down in this world.
	ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false)));

	//Create a scene.
	//The scene is a scene graph that renders objects added to its root and their children and their children's children and so on.
	//When the render mode of the scene is set to RENDER_ALPHA_DEPTH_SORTED, it handles sorting of both transparent and opaque objects in the z-axis.
	scene = new ofxScene(ofGetWidth(), ofGetHeight());
	scene->setBackgroundColor(10, 100, 10);

	//Make a root for the circle objects created below and position it.
	circleRoot = new ofxObject();
	//circleRoot->setTrans(-ofGetWidth()/2 + 180, 20, 0);
	scene->getRoot()->addChild(circleRoot);
	
	float r = 2000;
	int numImgs = 8;
	for(int i = 0; i < numImgs; i++){		
		char buf[256];
		sprintf(buf, "shirt\\%02d.png", 0);
		string filename = buf;

		int j = numImgs - i;
		float angle = TWO_PI / 4 - TWO_PI*(float)j/(float)numImgs;
		ofxImageObject *img = new ofxImageObject(filename);
		img->setCentered(true);
		img->setTrans(r*cos(angle),				//Set an object's translation.
			0, 
			r*sin(angle));																						
		circleRoot->addChild(img);										//Add the object to the scene.
		imgs.push_back(img);

	}

	ofxCircleObject *debugCircle = new ofxCircleObject(500, r);
	debugCircle->setColor(255, 0, 0);
	debugCircle->setAlpha(100);
	debugCircle->setRot(0, 0, 0);
	circleRoot->addChild(debugCircle);
	circleRoot->setTrans(0, 0, -4000);

	

	////Make some circle objects, position them, and add them to the circleRoot object.
	//int numCircles = 12;	
	//for(int i=0; i < numCircles; i++){
	//	float r = 70;
	//	ofxCircleObject *circ = new ofxCircleObject(200, 10.0);
	//	circ->setColor(255, 200-i*10, 200);										//Set an object's color.
	//	circ->setAlpha(100);													//Set an object's transparency independently.
	//	circ->setTrans(r*cos(TWO_PI*(float)i/(float)numCircles),				//Set an object's translation.
	//		r*sin(TWO_PI*(float)i/(float)numCircles), 
	//		-2.0);																						
	//	circleRoot->addChild(circ);												//Add the object to the scene.
	//	circles.push_back(circ);
	//}
}

//--------------------------------------------------------------
void testApp::update(){
	//Update the scene with the current time. This call propagates the idle() call to all objects as well.
	//Note: If you are capturing frames to create a movie, simply replace ofGetElapsedTimef() with a float variable that you increment by a fixed time interval each frame.
	scene->update(ofGetElapsedTimef());
}

//--------------------------------------------------------------
void testApp::draw(){
	//Call draw on scene, which initiates the drawing of the root object.
	scene->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
		circleRoot->stopMessages();
		circleRoot->doMessage3f(OF_ROTATE, 0, 5.f, OF_EASE_OUT, 0, 180, 0);
		circleRoot->doMessage3f(OF_ROTATE, 5.f, 2.f, OF_EASE_OUT, 0, 0, 0);
	}
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