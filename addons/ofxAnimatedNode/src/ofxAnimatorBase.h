#ifndef __OFX_ANIMATOR_BASE_H__
#define __OFX_ANIMATOR_BASE_H__

class ofxAnimatedNodeBase;
class ofxEasing;
class ofxTween;

class ofxAnimatorBase
{
public:
	enum EasingFuncType{
		Bounce,
		Cubic,
		Elastic,
		Linear,
		Quart,
		Back,
		Circ,
		Expo,
		Quad,
		Quint,
		sine
	};

	enum EasingType{
		EaseIn,
		EaseOut,
		EaseInOut
	};

	ofxAnimatorBase(ofxAnimatedNodeBase& _animatedNode): animatedNode(_animatedNode)
	{

	}

	~ofxAnimatorBase()
	{

	}

	virtual void update() = 0;
protected:
	ofxAnimatedNodeBase& animatedNode;

};

// helper function
ofxEasing& getEasingFunc(ofxAnimatorBase::EasingFuncType type);
int getOfxEasingType(ofxAnimatorBase::EasingType type);

#endif