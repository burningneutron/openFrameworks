#include "ofxAnimatorBase.h"
#include "ofxAnimatorRotation.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorRotation::ofxAnimatorRotation(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorRotation:: ofxAnimatorRotation(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set(_easyFuncType, _easyType, _to, _duration, _delay);
}

ofxAnimatorRotation::~ofxAnimatorRotation()
{
	delete tween;
}

void ofxAnimatorRotation::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	easyType = _easyType;
	to = _to;
	duration = _duration;
	delay = _delay;	
}

void ofxAnimatorRotation::start()
{
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode->getRotation()[0], to[0],  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->addValue(animatedNode->getRotation()[1], to[1]);
	tween->addValue(animatedNode->getRotation()[2], to[2]);
	tween->start();
}

void ofxAnimatorRotation::stop()
{
	// TODO
}

void ofxAnimatorRotation::update()
{
	ofVec3f newRotation;
	newRotation[0] = tween->update();
	newRotation[1] = tween->getTarget(1);
	newRotation[2] = tween->getTarget(2);
	animatedNode->setRotation(newRotation);
}

bool ofxAnimatorRotation::isFinish()
{
	return tween->isCompleted();
}