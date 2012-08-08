#include "ofxAnimatorBase.h"
#include "ofxAnimatorTranslation.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorTranslation::ofxAnimatorTranslation(ofxAnimatedNodeBase &_animatedNode): ofxAnimatorBase(_animatedNode)
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorTranslation::~ofxAnimatorTranslation()
{
	delete tween;
}

void ofxAnimatorTranslation::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, ofVec3f to, float duration, float delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode.getTranslation()[0], to[0],  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->addValue(animatedNode.getTranslation()[1], to[1]);
	tween->addValue(animatedNode.getTranslation()[2], to[2]);
	tween->start();
}

void ofxAnimatorTranslation::update()
{
	ofVec3f newTrans;
	newTrans[0] = tween->update();
	newTrans[1] = tween->getTarget(1);
	newTrans[2] = tween->getTarget(2);
	animatedNode.setTranslation(newTrans);
}
