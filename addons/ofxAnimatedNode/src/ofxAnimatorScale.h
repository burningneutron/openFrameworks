#ifndef __OFX_ANIMATED_SCALE_H__
#define __OFX_ANIMATED_SCALE_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorScale: public ofxAnimatorBase
{
public:
	ofxAnimatorScale();
	ofxAnimatorScale(ofxAnimatorBase::EasingFuncType _easyFuncType, ofxAnimatorBase::EasingType _easyType, float _to, float _duration, float _delay);

	~ofxAnimatorScale();

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