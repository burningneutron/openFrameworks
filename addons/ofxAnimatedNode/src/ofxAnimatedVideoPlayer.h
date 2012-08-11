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
	void setSpeed(float speed);
	void setLoopState(ofLoopType mode);

private:
	ofVideoPlayer video;
};
#endif