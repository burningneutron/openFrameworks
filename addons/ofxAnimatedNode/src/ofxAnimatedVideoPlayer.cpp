#include "ofxAnimatedNodeBase.h"
#include "ofxAnimatedVideoPlayer.h"

ofAnimatedVideoPlayer::ofAnimatedVideoPlayer(): ofxAnimatedNodeBase()
{
	isCentered = false;
}

ofAnimatedVideoPlayer::ofAnimatedVideoPlayer(string filename)
{
	isCentered = false;
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

float ofAnimatedVideoPlayer::getWidth()
{
	return video.getWidth();
}

float ofAnimatedVideoPlayer::getHeight()
{
	return video.getHeight();
}

void ofAnimatedVideoPlayer::setSpeed(float speed)
{
	video.setSpeed(speed);
}

void ofAnimatedVideoPlayer::setLoopState(ofLoopType mode)
{
	video.setLoopState(mode);
}

void ofAnimatedVideoPlayer::setCentered(bool _isCentered)
{
	isCentered = _isCentered;
}