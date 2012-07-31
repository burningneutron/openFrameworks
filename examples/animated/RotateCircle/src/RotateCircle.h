#pragma once

#include "ofxObject.h"

class ofxRotateCircleObject : public ofxObject{

public:
	ofxRotateCircleObject(int iResolution, float iRadius);
	~ofxRotateCircleObject();

	void						render();

public:	
	int							resolution,
								numCirclePoints;
	float						radius;
	
	float						*circlePoints;
};