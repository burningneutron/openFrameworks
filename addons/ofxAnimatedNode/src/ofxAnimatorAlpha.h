#ifndef __OFX_ANIMATED_ALPHA_H__
#define __OFX_ANIMATED_ALPHA_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorAlpha: public ofxAnimatorBase
{
public:
	ofxAnimatorAlpha();
	ofxAnimatorAlpha(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay);

	~ofxAnimatorAlpha();

	void set(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay);

	void start();
	void stop();
	void update();

	bool isFinish();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;

	ofxAnimatorBase::EasingType easyType;
	float to;
	float duration;
	float delay;
};
#endif