#ifndef __OFX_ANIMATED_VIDEO_PLAYER_H__
#define __OFX_ANIMATED_VIDEO_PLAYER_H__

#include "ofVideoPlayer.h"

class ofxAnimatedNodeBase;

#define VIDEO_PLAYER_QT  0
#define VIDEO_PLAYER_GST 1

class ofxAnimatedVideoPlayer: public ofxAnimatedNodeBase
{
public:
	ofxAnimatedVideoPlayer(int type = VIDEO_PLAYER_QT);
	ofxAnimatedVideoPlayer(string filename, int type = VIDEO_PLAYER_QT);
	~ofxAnimatedVideoPlayer();

	void set(string filename, int type = VIDEO_PLAYER_QT);
	void update();
	void render();

	void play();
	void stop();

	float getWidth();
	float getHeight();
	void setSpeed(float speed);
	void setLoopState(ofLoopType mode);
	void setCentered(bool _isCentered);

	void setFrame(int frame);  // frame 0 = first frame...

	bool isPaused();
	bool isLoaded();
	bool isPlaying();

private:
	ofBaseVideoPlayer *video;
	bool isCentered;

	int type;

	void createVideoPlayer();
};
#endif