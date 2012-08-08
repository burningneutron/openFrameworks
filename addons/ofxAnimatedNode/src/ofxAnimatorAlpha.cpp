#include "ofxAnimatorBase.h"
#include "ofxAnimatorAlpha.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorAlpha::ofxAnimatorAlpha(ofxAnimatedNodeBase &_animatedNode): ofxAnimatorBase(_animatedNode)
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorAlpha::~ofxAnimatorAlpha()
{
	delete tween;
}

void ofxAnimatorAlpha::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, float to, float duration, float delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode.getAlpha(), to, (unsigned)(duration*1000), (unsigned)(delay*1000));
}

void ofxAnimatorAlpha::update()
{
	animatedNode.setAlpha(tween->update());
}
