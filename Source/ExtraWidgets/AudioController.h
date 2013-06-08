#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H
//	Qt
#include <QWidget>
#include <QComboBox>
//
#include "../AudioManager/AudioManager.h"

class AudioController : public QWidget
{
	Q_OBJECT
public:
	AudioController(QWidget *parent = 0);
	~AudioController();

public slots:
	void addMedia(const QString& m)
	{
		combo->addItem(m);
	}

	void changeMedia(const QString& m)
	{
		combo->setCurrentText(m);
	}
private slots:
	void mediaChosen(const QString& m)
	{
		emit mediaChanged(m);
	}

signals:
	void mediaChanged(const QString& m);

private:
	QComboBox* combo;
};

#endif // AUDIOCONTROLLER_H
