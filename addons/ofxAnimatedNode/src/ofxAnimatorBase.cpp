#include "ofxTween.h"
#include "ofxAnimatorBase.h"

ofxEasing& getEasingFunc(ofxAnimatorBase::EasingFuncType type)
{
	static ofxEasingBack 	easingback;
	static ofxEasingBounce 	easingbounce;
	static ofxEasingCirc 	easingcirc;
	static ofxEasingCubic 	easingcubic;
	static ofxEasingElastic easingelastic;
	static ofxEasingExpo 	easingexpo;
	static ofxEasingLinear 	easinglinear;
	static ofxEasingQuad 	easingquad;
	static ofxEasingQuart 	easingquart;
	static ofxEasingQuint 	easingquint;
	static ofxEasingSine	easingsine;
	
	switch(type){
	case ofxAnimatorBase::Bounce:
		return easingbounce;
		break;
	case ofxAnimatorBase::Cubic:
		return easingcubic;
		break;
	case ofxAnimatorBase::Elastic:
		return easingelastic;
		break;
	case ofxAnimatorBase::Linear:
		return easinglinear;
		break;
	case ofxAnimatorBase::Quart:
		return easingquart;
		break;
	case ofxAnimatorBase::Back:
		return easingback;
		break;
	case ofxAnimatorBase::Circ:
		return easingcirc;
		break;
	case ofxAnimatorBase::Expo:
		return easingexpo;
		break;
	case ofxAnimatorBase::Quad:
		return easingquad;
		break;
	case ofxAnimatorBase::Quint:
		return easingquint;
		break;
	case ofxAnimatorBase::Sine:
		return easingsine;
		break;
	default:
		return easinglinear;
	}
}

int getOfxEasingType(ofxAnimatorBase::EasingType type)
{
	switch(type)
	{
	case ofxTween::easeIn:
		return ofxAnimatorBase::EaseIn;
		break;
	case ofxTween::easeOut:
		return ofxAnimatorBase::EaseOut;
		break;
	case ofxTween::easeInOut:
		return ofxAnimatorBase::EaseInOut;
		break;
	default:
		return ofxAnimatorBase::EaseInOut;
		break;
	}
}