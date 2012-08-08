#ifndef __OFX_ANIMATED_TRANSLATION_H__
#define __OFX_ANIMATED_TRANSLATION_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofVec3f;
class ofxTween;

class ofxAnimatorTranslation: public ofxAnimatorBase
{
public:
	ofxAnimatorTranslation(ofxAnimatedNodeBase &_animatedNode);

	~ofxAnimatorTranslation();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, ofVec3f to, float duration, float delay);

	void update();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;
};
#endif