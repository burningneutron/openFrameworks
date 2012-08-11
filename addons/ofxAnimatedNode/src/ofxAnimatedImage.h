#ifndef __OFX_ANIMATED_IMAGE_H__
#define __OFX_ANIMATED_IMAGE_H__

#include "ofImage.h"

class ofxAnimatedNodeBase;

class ofxAnimatedImage: public ofxAnimatedNodeBase
{
public:
	ofxAnimatedImage();
	ofxAnimatedImage(string filename);
	~ofxAnimatedImage();

	void set(string filename);
	void render();

private:
	ofImage img;
};
#endif