#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedImage.h"

ofxAnimatedImage::ofxAnimatedImage(): ofxAnimatedNodeBase()
{

}

ofxAnimatedImage::ofxAnimatedImage(string filename)
{
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
	img.draw(0,0);
}