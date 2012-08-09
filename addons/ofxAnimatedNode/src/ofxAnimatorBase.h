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
		Sine
	};

	enum EasingType{
		EaseIn,
		EaseOut,
		EaseInOut
	};

	ofxAnimatorBase()
	{

	}

	~ofxAnimatorBase()
	{

	}

	void bind( ofxAnimatedNodeBase *_animatedNode)
	{
		animatedNode = _animatedNode;
	}

	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update() = 0;
	virtual bool isFinish() = 0;
protected:
	ofxAnimatedNodeBase* animatedNode;

};

// helper function
ofxEasing& getEasingFunc(ofxAnimatorBase::EasingFuncType type);
int getOfxEasingType(ofxAnimatorBase::EasingType type);

#endif