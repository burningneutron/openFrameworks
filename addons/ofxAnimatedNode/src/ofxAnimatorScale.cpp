#include "ofxAnimatorBase.h"
#include "ofxAnimatorScale.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorScale::ofxAnimatorScale(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorScale:: ofxAnimatorScale(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set(_easyFuncType, _easyType, _to, _duration, _delay);
}

ofxAnimatorScale::~ofxAnimatorScale()
{
	delete tween;
}

void ofxAnimatorScale::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	easyFunc = &(getEasingFunc(_easyFuncType));

	easyType = _easyType;
	to = _to;
	duration = _duration;
	delay = _delay;	
}

void ofxAnimatorScale::start()
{
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode->getScale(), to,  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->start();
}

void ofxAnimatorScale::stop()
{
	// TODO
}

void ofxAnimatorScale::update()
{
	animatedNode->setScale(tween->update());
}

bool ofxAnimatorScale::isFinish()
{
	return tween->isCompleted();
}