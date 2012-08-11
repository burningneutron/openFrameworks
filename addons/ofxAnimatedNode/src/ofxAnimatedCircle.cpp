#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedCircle.h"

ofxAnimatedCircle::ofxAnimatedCircle(): ofxAnimatedNodeBase()
{
	set(0, 0, 0);
}
ofxAnimatedCircle::ofxAnimatedCircle(int _resolution, float _outRadious, float _innerRadius)
{
	set(_resolution, _outRadious, _innerRadius);
}

ofxAnimatedCircle::~ofxAnimatedCircle()
{
	
}

void ofxAnimatedCircle::set(int _resolution, float _outRadious, float _innerRadius)
{

	resolution = _resolution;

	outerRadius = _outRadious;
	innerRadius = _innerRadius;	

	numCirclePoints = 2*resolution;
	outerCirclePoints.resize(numCirclePoints);
	innerCirclePoints.resize(numCirclePoints);

	float angleInc = M_TWO_PI/(float)resolution;
	for( int i = 0; i < resolution; i++ ){
		float angle = (float)i*angleInc;
		outerCirclePoints[2*i] = outerRadius * cos(angle);
		outerCirclePoints[2*i+1] = outerRadius * sin(angle);

		innerCirclePoints[2*i] = innerRadius * cos(angle);
		innerCirclePoints[2*i+1] = innerRadius * sin(angle);
	}
}

void ofxAnimatedCircle::render()
{
	ofFill();			

	int k = 0;
	float angleInc = M_TWO_PI/(float)resolution;

	glBegin(GL_TRIANGLE_STRIP);
	for(int i = 0; i < resolution; i++){		
		float angle = (float)i*angleInc;
		glVertex3f(innerCirclePoints[2*i], innerCirclePoints[2*i+1], 0);
		glVertex3f(outerCirclePoints[2*i], outerCirclePoints[2*i+1], 0);				
	}
	glVertex3f(innerCirclePoints[0], innerCirclePoints[1], 0);
	glVertex3f(outerCirclePoints[0], outerCirclePoints[1], 0);
	glEnd();
}
