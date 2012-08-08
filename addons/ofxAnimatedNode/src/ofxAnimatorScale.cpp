#include "ofxAnimatorBase.h"
#include "ofxAnimatorScale.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorScale::ofxAnimatorScale(ofxAnimatedNodeBase &_animatedNode): ofxAnimatorBase(_animatedNode)
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorScale::~ofxAnimatorScale()
{
	delete tween;
}

void ofxAnimatorScale::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, float to, float duration, float delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode.getScale(), to,  (unsigned)(duration*1000), (unsigned)(delay*1000));
}

void ofxAnimatorScale::update()
{
	animatedNode.setScale(tween->update());
}
