#ifndef __OFX_ANIMATED_NODE_BASE_H__
#define __OFX_ANIMATED_NODE_BASE_H__

#include "ofMain.h"

class ofxAnimatorBase;

class ofxAnimatedNodeBase
{
public:
	ofxAnimatedNodeBase();
	~ofxAnimatedNodeBase();

	ofColor getColor() const;
	void setColor( ofColor _color );

	ofVec3f getTranslation() const;
	void setTranslation( ofVec3f _translation );

	float getAlpha() const;
	void setAlpha( float _alpha );

	float getScale() const;
	void setScale( float _scale );

	bool isShow() const;
	void setShow();
	void setHide();

	virtual void update();

	void preDraw();
	void draw();
	virtual void render() = 0;
	void postDraw();

	void bindAnimator(ofxAnimatorBase* _animator);

private:
	ofColor color;
	ofVec3f translation;
	float alpha;
	float scale;
	bool show;

	std::vector<ofxAnimatorBase*> animators;
};

#endif