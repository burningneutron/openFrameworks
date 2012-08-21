#include "ofxAnimatorBase.h"
#include "ofxAnimatorVideoPlayerSwitch.h"
#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedVideoPlayer.h"
#include "ofxTween.h"

ofxAnimatorVideoPlayerSwitch::ofxAnimatorVideoPlayerSwitch(): ofxAnimatorBase()
{
	easyFunc = 0;
	tween = new ofxTween;
}

ofxAnimatorVideoPlayerSwitch:: ofxAnimatorVideoPlayerSwitch( bool _to, float _delay)
{
	easyFunc = 0;
	tween = new ofxTween;
	set( _to, _delay);
}

ofxAnimatorVideoPlayerSwitch::~ofxAnimatorVideoPlayerSwitch()
{
	delete tween;
}

void ofxAnimatorVideoPlayerSwitch::set(bool _to, float _delay)
{
	easyFunc = &(getEasingFunc(ofxAnimatorBase::Linear));

	easyType = ofxAnimatorBase::EaseIn;
	to = _to;
	duration = _delay;
	delay = 0;	
	isFirstTime = true;
}

void ofxAnimatorVideoPlayerSwitch::start()
{
	tween->setParameters(*easyFunc, static_cast<ofxTween::ofxEasingType>(getOfxEasingType(easyType)), 0, 1.f,  (unsigned)(duration*1000), (unsigned)(delay*1000));
}

void ofxAnimatorVideoPlayerSwitch::stop()
{
	// TODO
}

void ofxAnimatorVideoPlayerSwitch::update()
{
	tween->update();
	if( tween->isCompleted() && isFirstTime ){
		if( to ) dynamic_cast<ofxAnimatedVideoPlayer*>(animatedNode)->play();
		else dynamic_cast<ofxAnimatedVideoPlayer*>(animatedNode)->stop();

		isFirstTime = false;
	}
}

bool ofxAnimatorVideoPlayerSwitch::isFinish()
{
	return tween->isCompleted();
}
