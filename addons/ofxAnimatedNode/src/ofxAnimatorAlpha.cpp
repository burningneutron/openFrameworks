#include "ofxAnimatorBase.h"
#include "ofxAnimatorAlpha.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorAlpha::ofxAnimatorAlpha(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorAlpha:: ofxAnimatorAlpha(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set(_easyFuncType, _easyType, _to, _duration, _delay);
}

ofxAnimatorAlpha::~ofxAnimatorAlpha()
{
	delete tween;
}

void ofxAnimatorAlpha::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	easyType = _easyType;
	to = _to;
	duration = _duration;
	delay = _delay;	
}

void ofxAnimatorAlpha::start()
{
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode->getAlpha(), to, (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->start();
}

void ofxAnimatorAlpha::stop()
{
	// TODO
}

void ofxAnimatorAlpha::update()
{
	animatedNode->setAlpha(tween->update());
}

bool ofxAnimatorAlpha::isFinish()
{
	return tween->isCompleted();
}