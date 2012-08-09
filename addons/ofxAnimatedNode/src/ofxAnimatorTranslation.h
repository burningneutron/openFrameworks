#ifndef __OFX_ANIMATED_TRANSLATION_H__
#define __OFX_ANIMATED_TRANSLATION_H__
#include "ofVec3f.h"

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorTranslation: public ofxAnimatorBase
{
public:
	ofxAnimatorTranslation();
	ofxAnimatorTranslation(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay);

	~ofxAnimatorTranslation();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay);

	void start();
	void stop();
	void update();

	bool isFinish();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;

	ofxAnimatorBase::EasingType easyType;
	ofVec3f to;
	float duration;
	float delay;
};
#endif