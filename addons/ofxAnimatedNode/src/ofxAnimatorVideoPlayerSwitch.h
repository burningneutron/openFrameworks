#ifndef __OFX_ANIMATOR_VIDEO_PLAYER_SWITCH_H__
#define __OFX_ANIMATOR_VIDEO_PLAYER_SWITCH_H__

class ofxAnimatorBase;
class ofxAnimatedNodeBase;
class ofxTween;

class ofxAnimatorVideoPlayerSwitch: public ofxAnimatorBase
{
public:
	ofxAnimatorVideoPlayerSwitch();
	ofxAnimatorVideoPlayerSwitch(bool _to, float _delay);

	~ofxAnimatorVideoPlayerSwitch();

	void set(bool _to, float _delay);

	void start();
	void stop();
	void update();

	bool isFinish();

private:
	ofxTween *tween;
	ofxEasing *easyFunc;

	ofxAnimatorBase::EasingType easyType;
	bool to;
	float duration;
	float delay;

	bool isFirstTime;
};
#endif