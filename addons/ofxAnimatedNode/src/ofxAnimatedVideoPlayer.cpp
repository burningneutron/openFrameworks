#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedVideoPlayer.h"

ofAnimatedVideoPlayer::ofAnimatedVideoPlayer(): ofxAnimatedNodeBase()
{

}

ofAnimatedVideoPlayer::ofAnimatedVideoPlayer(string filename)
{
	set(filename);
}

ofAnimatedVideoPlayer::~ofAnimatedVideoPlayer()
{

}

void ofAnimatedVideoPlayer::set(string filename)
{
	video.loadMovie(filename);
}

void ofAnimatedVideoPlayer::update()
{
	video.idleMovie();

	ofxAnimatedNodeBase::update();
}

void ofAnimatedVideoPlayer::render()
{
	video.draw(0,0);
}

void ofAnimatedVideoPlayer::play()
{
	video.play();
}

void ofAnimatedVideoPlayer::stop()
{
	video.stop();
}

void ofAnimatedVideoPlayer::setSpeed(float speed)
{
	video.setSpeed(speed);
}

void ofAnimatedVideoPlayer::setLoopState(ofLoopType mode)
{
	video.setLoopState(mode);
}