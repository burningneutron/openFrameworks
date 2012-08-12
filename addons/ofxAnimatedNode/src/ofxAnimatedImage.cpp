#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedImage.h"

ofxAnimatedImage::ofxAnimatedImage(): ofxAnimatedNodeBase()
{
	isCentered = false;
}

ofxAnimatedImage::ofxAnimatedImage(string filename)
{
	isCentered = false;
	set(filename);
}

ofxAnimatedImage::~ofxAnimatedImage()
{

}

void ofxAnimatedImage::set(string filename)
{
	img.loadImage(filename);
}

void ofxAnimatedImage::render()
{
	ofEnableAlphaBlending();
	if( isCentered){
		img.draw(-img.getWidth()/2, -img.getHeight()/2);
	}else{
		img.draw(0,0);
	}
	ofDisableAlphaBlending();
}

float ofxAnimatedImage::getWidth()
{
	return img.getWidth();
}

float ofxAnimatedImage::getHeight()
{
	return img.getHeight();
}

void ofxAnimatedImage::setCentered(bool _isCentered)
{
	isCentered = _isCentered;
}