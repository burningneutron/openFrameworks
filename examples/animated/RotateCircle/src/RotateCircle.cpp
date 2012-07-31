#include "ofxRotateCircleObject.h"


ofxRotateCircleObject::ofxRotateCircleObject(int iResolution, float iRadius)
{
	resolution = iResolution;

	radius = iRadius;

	numCirclePoints = 4*resolution;
	circlePoints = new float[numCirclePoints];

	
}

ofxRotateCircleObject::~ofxRotateCircleObject(){}

void ofxRotateCircleObject::render()
{		
	ofFill();			

	int k = 0;
	float angleInc = M_TWO_PI/(float)resolution;

	glBegin(GL_TRIANGLE_STRIP);
	for(int i = 0; i < (resolution+1); i++){		
		float angle = (float)i*angleInc;
		glVertex3f(innerRadius * cos(angle), innerRadius * sin(angle), 0);
		glVertex3f(outerRadius * cos(angle), outerRadius * sin(angle), 0);				
	}
	glEnd();
}