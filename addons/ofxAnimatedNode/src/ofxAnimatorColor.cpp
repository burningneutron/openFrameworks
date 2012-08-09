#include "ofxAnimatorBase.h"
#include "ofxAnimatorColor.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorColor::ofxAnimatorColor(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorColor:: ofxAnimatorColor(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofColor _to, float _duration, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set(_easyFuncType, _easyType, _to, _duration, _delay);
}

ofxAnimatorColor::~ofxAnimatorColor()
{
	delete tween;
}

void ofxAnimatorColor::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, ofColor _to, float _duration, float _delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	easyType = _easyType;
	to = _to;
	duration = _duration;
	delay = _delay;	
}

void ofxAnimatorColor::start()
{
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode->getColor()[0], to[0],  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->addValue(animatedNode->getColor()[1], to[1]);
	tween->addValue(animatedNode->getColor()[2], to[2]);
	tween->addValue(animatedNode->getColor()[3], to[3]);
	tween->start();
}

void ofxAnimatorColor::stop()
{
	// TODO
}

void ofxAnimatorColor::update()
{
	ofColor newColor;
	newColor[0] = tween->update();
	newColor[1] = tween->getTarget(1);
	newColor[2] = tween->getTarget(2);
	newColor[3] = tween->getTarget(3);
	animatedNode->setColor(newColor);
}
