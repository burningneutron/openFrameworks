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
	ofxAnimatorColor();
	ofxAnimatorColor(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofColor _to, float _duration, float _delay);

	~ofxAnimatorColor();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofColor _to, float _duration, float _delay);

	void start();
	void stop();
	void update();

	 bool isFinish();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;
	ofxAnimatorBase::EasingType easyType;
	ofColor to;
	float duration;
	float delay;

};
#endif