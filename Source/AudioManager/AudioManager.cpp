#include "AudioManager.h"

// Constructors/Destructors
//
AudioManager* AudioManager::m_Instance=NULL;

AudioManager::AudioManager(QWidget* parent ):
	mediaPlayer(0, QMediaPlayer::VideoSurface),
	soundEffectsPlayer(0, QMediaPlayer::VideoSurface),
	QWidget(parent),
	playlist(new QMediaPlaylist(0))
{
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(onChange(int)));
}

AudioManager::~AudioManager(){}

void AudioManager::playMusic()
{
	static bool lazyInitialization=false;
	if(!lazyInitialization)
	{
		mediaPlayer.setPlaylist(playlist);
		lazyInitialization=true;
	}
	switch(mediaPlayer.state()) {
	case QMediaPlayer::PlayingState:
		mediaPlayer.pause();
		break;
	default:
		mediaPlayer.play();
		break;
	}
}

void AudioManager::stopMusic()
{
	mediaPlayer.stop();
}

void AudioManager::playSoundEffect()
{
	switch(soundEffectsPlayer.state()) {
	case QMediaPlayer::PlayingState:
		break;
	default:
		QString fileName1 = QString("SoundEffect2.mp3");
		if (!fileName1.isEmpty()) {
			soundEffectsPlayer.setMedia(QUrl::fromLocalFile(fileName1));
		}
		soundEffectsPlayer.play();
		break;
	}
}

void AudioManager::setVolume(int v)
{
	mediaPlayer.setVolume(v);
}
