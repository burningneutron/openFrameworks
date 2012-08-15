#include <assert.h>
#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedVideoPlayer.h"

ofxAnimatedVideoPlayer::ofxAnimatedVideoPlayer(int _type): ofxAnimatedNodeBase()
{
	isCentered = false;
	type = _type;
	createVideoPlayer();
}

ofxAnimatedVideoPlayer::ofxAnimatedVideoPlayer(string filename, int _type)
{
	isCentered = false;
	type = _type;
	createVideoPlayer();
	set(filename);
}

void ofxAnimatedVideoPlayer::createVideoPlayer()
{
	if( type == VIDEO_PLAYER_QT ){
		video = new ofVideoPlayer;
	}else{
		assert(0);
	}
}

ofxAnimatedVideoPlayer::~ofxAnimatedVideoPlayer()
{
	if( video ) delete video;
}

void ofxAnimatedVideoPlayer::set(string filename, int type)
{	
	video->loadMovie(filename);
}

void ofxAnimatedVideoPlayer::update()
{
	video->update();

	ofxAnimatedNodeBase::update();
}

void ofxAnimatedVideoPlayer::render()
{
	if( type == VIDEO_PLAYER_QT){
		dynamic_cast<ofVideoPlayer*>(video)->draw(0,0);
	}else{
		assert(0);
	}
}

void ofxAnimatedVideoPlayer::play()
{
	video->play();
}

void ofxAnimatedVideoPlayer::stop()
{
	video->stop();
}

float ofxAnimatedVideoPlayer::getWidth()
{
	return video->getWidth();
}

float ofxAnimatedVideoPlayer::getHeight()
{
	return video->getHeight();
}

void ofxAnimatedVideoPlayer::setSpeed(float speed)
{
	video->setSpeed(speed);
}

void ofxAnimatedVideoPlayer::setLoopState(ofLoopType mode)
{
	video->setLoopState(mode);
}

void ofxAnimatedVideoPlayer::setCentered(bool _isCentered)
{
	isCentered = _isCentered;
}

void ofxAnimatedVideoPlayer::setFrame(int frame)
{
	video->setFrame(frame);
}

bool ofxAnimatedVideoPlayer::isPaused()
{
	return video->isPaused();
}

bool ofxAnimatedVideoPlayer::isLoaded()
{
	return video->isLoaded();
}

bool ofxAnimatedVideoPlayer::isPlaying()
{
	return video->isPlaying();
}