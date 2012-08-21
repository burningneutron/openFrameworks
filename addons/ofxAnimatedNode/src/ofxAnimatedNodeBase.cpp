#include "ofxAnimatedNode.h"
#include "ofxAnimatorBase.h"

#include <deque>

using namespace std;

ofxAnimatedNodeBase::ofxAnimatedNodeBase()
{
	color = ofColor(255,255,255);
	alpha = 1.f;
	translation = ofVec3f(0.f, 0.f, 0.f);
	scale = 1.f;
	show = true;
}

ofxAnimatedNodeBase::~ofxAnimatedNodeBase()
{
	for( int i = 0; i < (int)animators.size(); i++ ){
		delete animators[i];
	}
}

ofColor ofxAnimatedNodeBase::getColor() const
{
	return color;
}

void ofxAnimatedNodeBase::setColor( ofColor _color )
{
	color = _color;
}

ofVec3f ofxAnimatedNodeBase::getTranslation() const
{
	return translation;
}

void ofxAnimatedNodeBase::setTranslation( ofVec3f _translation )
{
	translation = _translation;
}

ofVec3f ofxAnimatedNodeBase::getRotation() const
{
	return rotation;
}

void ofxAnimatedNodeBase::setRotation( ofVec3f _rotation )
{
	rotation = _rotation;
}

float ofxAnimatedNodeBase::getAlpha() const
{
	return alpha;
}

void ofxAnimatedNodeBase::setAlpha( float _alpha )
{
	alpha = _alpha;
}

float ofxAnimatedNodeBase::getScale() const
{
	return scale;
}

void ofxAnimatedNodeBase::setScale( float _scale )
{
	scale = _scale;
}

bool ofxAnimatedNodeBase::isShow() const
{
	return show;
}

void ofxAnimatedNodeBase::setShow()
{
	show = true;
}

void ofxAnimatedNodeBase::setHide()
{
	show = false;
}

void ofxAnimatedNodeBase::update()
{
	for( deque<ofxAnimatorBase*>::iterator it = animators.begin(); it != animators.end(); ){
		(*it)->update();
		if( (*it)->isFinish() ) it = animators.erase(it);
		else it++;
	}
}

void ofxAnimatedNodeBase::preDraw()
{
	ofEnableAlphaBlending();
	ofSetColor(color, alpha*255);
	ofPushMatrix();
	ofTranslate(translation[0], translation[1], translation[2]);
	ofScale(scale, scale, scale);
	ofRotate(rotation[2], 0, 0, 1);
	ofRotate(rotation[1], 0, 1, 0);
	ofRotate(rotation[0], 1, 0, 0);
}

void ofxAnimatedNodeBase::draw()
{
	if(!show) return;

	preDraw();
	render();
	postDraw();
}

void ofxAnimatedNodeBase::postDraw()
{
	ofPopMatrix();
}

void ofxAnimatedNodeBase::bindAnimator(ofxAnimatorBase* _animator)
{
	_animator->bind(this);
	_animator->start();
	animators.push_back(_animator);
}