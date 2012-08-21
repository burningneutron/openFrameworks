#include "ofxAnimatorBase.h"
#include "ofxAnimatorTranslation.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorTranslation::ofxAnimatorTranslation(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorTranslation:: ofxAnimatorTranslation(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set(_easyFuncType, _easyType, _to, _duration, _delay);
}

ofxAnimatorTranslation::~ofxAnimatorTranslation()
{
	delete tween;
}

void ofxAnimatorTranslation::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofVec3f _to, float _duration, float _delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	easyType = _easyType;
	to = _to;
	duration = _duration;
	delay = _delay;	
}

void ofxAnimatorTranslation::start()
{
	tween->setFrameBasedAnimation(true);
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode->getTranslation()[0], to[0],  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->addValue(animatedNode->getTranslation()[1], to[1]);
	tween->addValue(animatedNode->getTranslation()[2], to[2]);
	tween->start();
}

void ofxAnimatorTranslation::stop()
{
	// TODO
}

void ofxAnimatorTranslation::update()
{
	ofVec3f newTrans;
	newTrans[0] = tween->update();
	newTrans[1] = tween->getTarget(1);
	newTrans[2] = tween->getTarget(2);
	animatedNode->setTranslation(newTrans);
}

bool ofxAnimatorTranslation::isFinish()
{
	return tween->isCompleted();
}
