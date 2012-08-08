#ifndef __OFX_ANIMATED_SCALE_H__
#define __OFX_ANIMATED_SCALE_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorScale: public ofxAnimatorBase
{
public:
	ofxAnimatorScale(ofxAnimatedNodeBase &_animatedNode);

	~ofxAnimatorScale();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType easyType, float to, float duration, float delay);

	void update();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;
};
#endif