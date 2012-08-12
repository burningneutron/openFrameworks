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

	float getWidth();
	float getHeight();
	void setCentered(bool _isCentered);

private:
	ofImage img;
	bool isCentered;
};
#endif