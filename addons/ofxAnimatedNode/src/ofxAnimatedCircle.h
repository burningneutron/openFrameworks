#ifndef __OFX_ANIMATED_CIRCLE_H__
#define __OFX_ANIMATED_CIRCLE_H__

class ofxAnimatedNodeBase;

class ofxAnimatedCircle: public ofxAnimatedNodeBase
{
public:
	ofxAnimatedCircle();
	ofxAnimatedCircle(int _resolution, float _outRadious, float _innerRadius);
	~ofxAnimatedCircle();

	void set(int _resolution, float _outRadious, float _innerRadius);
	void render();

private:
	int resolution,	numCirclePoints;
	float outerRadius, innerRadius;

	vector<float> innerCirclePoints, outerCirclePoints;
};
#endif