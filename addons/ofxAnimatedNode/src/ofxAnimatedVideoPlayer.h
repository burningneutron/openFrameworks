#ifndef __OFX_ANIMATED_VIDEO_PLAYER_H__
#define __OFX_ANIMATED_VIDEO_PLAYER_H__

#include "ofVideoPlayer.h"

class ofxAnimatedNodeBase;

class ofAnimatedVideoPlayer: public ofxAnimatedNodeBase
{
public:
	ofAnimatedVideoPlayer();
	ofAnimatedVideoPlayer(string filename);
	~ofAnimatedVideoPlayer();

	void set(string filename);
	void update();
	void render();

	void play();
	void stop();

	float getWidth();
	float getHeight();
	void setSpeed(float speed);
	void setLoopState(ofLoopType mode);
	void setCentered(bool _isCentered);

private:
	ofVideoPlayer video;
	bool isCentered;
};
#endif