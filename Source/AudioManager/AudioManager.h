#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

//	std includes
#include <string>
#include <iostream>
#include <list>
//	Qt
#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

class AudioManager : public QWidget
{
	Q_OBJECT
protected:
	/**
	 * Empty Constructor
	 */
	AudioManager(QWidget* parent=0);

	/**
	 * Empty Destructor
	 */
	virtual ~AudioManager();
public slots:
	void playMusic();
	void stopMusic();
	void playSoundEffect();
	void setVolume(int v);

public:
	/**
	 *	Singleton (DesingPattern)
	 */
	static AudioManager& getInstance()
	{
		static AudioManager* m_Instance_=NULL;
		if(!m_Instance_)
		{
			m_Instance=new AudioManager;
			m_Instance_=m_Instance;
		}
		if(!m_Instance)
		{
			m_Instance=new AudioManager;
			m_Instance_=m_Instance;
		}
		return *m_Instance;
	}

	static void destroy()
	{
		if(m_Instance)
			delete m_Instance;
		m_Instance=NULL;
	}

	AudioManager& addMedia(const QString& title, const QString& name)
	{
		static int n=0;
		playlist->addMedia(QUrl::fromLocalFile(QString("assets/audio/")+name));
		playlist_map[title]=n;
		n++;
		return *this;
	}

public slots:
	void setMedia(const QString& title)
	{
		if(playlist_map[title]!=playlist->currentIndex())
		{
			stopMusic();
			playlist->setCurrentIndex(playlist_map[title]);
			playMusic();
			emit mediaChanged(title);
		}
	}

private slots:
	void onChange(int n)
	{
		QString title;
		for(auto itr=playlist_map.begin();itr!=playlist_map.end();++itr)
		{
			if(itr->second==n)
			{
				title=itr->first;
				break;
			}
		}
		emit mediaChanged(title);
	}

signals:
	void mediaChanged(const QString& title);

private:
	// Singleton Instance
	//
	static AudioManager* m_Instance;
	QMediaPlayer mediaPlayer;
	QMediaPlayer soundEffectsPlayer;
	QMediaPlaylist* playlist;
	std::map<QString,int> playlist_map;
};


#endif // AUDIOMANAGER_H
