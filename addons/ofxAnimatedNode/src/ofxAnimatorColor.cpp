#include "ofxAnimatorBase.h"
#include "ofxAnimatorColor.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxTween.h"

ofxAnimatorColor::ofxAnimatorColor(ofxAnimatedNodeBase &_animatedNode): ofxAnimatorBase(_animatedNode)
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorColor::~ofxAnimatorColor()
{
	delete tween;
}

void ofxAnimatorColor::set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, ofColor to, float duration, float delay)
{
	easyFunc = &(getEasingFunc(_easyFuncType));

	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), animatedNode.getColor()[0], to[0],  (unsigned)(duration*1000), (unsigned)(delay*1000));
	tween->addValue(animatedNode.getColor()[1], to[1]);
	tween->addValue(animatedNode.getColor()[2], to[2]);
	tween->addValue(animatedNode.getColor()[3], to[3]);
	tween->start();
}

void ofxAnimatorColor::update()
{
	ofColor newColor;
	newColor[0] = tween->update();
	newColor[1] = tween->getTarget(1);
	newColor[2] = tween->getTarget(2);
	newColor[3] = tween->getTarget(3);
	animatedNode.setColor(newColor);
}
