#ifndef __OFX_ANIMATED_ALPHA_H__
#define __OFX_ANIMATED_ALPHA_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorAlpha: public ofxAnimatorBase
{
public:
	ofxAnimatorAlpha(ofxAnimatedNodeBase &_animatedNode);

	~ofxAnimatorAlpha();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, float to, float duration, float delay);

	void update();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;
};
#endif