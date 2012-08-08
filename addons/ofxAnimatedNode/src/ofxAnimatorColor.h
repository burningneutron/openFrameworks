#ifndef __OFX_ANIMATED_COLOR_H__
#define __OFX_ANIMATED_COLOR_H__

#include "ofMain.h"

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofVec3f;
class ofxTween;


class ofxAnimatorColor: public ofxAnimatorBase
{
public:
	ofxAnimatorColor(ofxAnimatedNodeBase &_animatedNode);

	~ofxAnimatorColor();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, ofColor to, float duration, float delay);

	void update();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;
};
#endif