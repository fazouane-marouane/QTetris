// Qt
#include <QBoxLayout>
#include <QSlider>
//
#include "AudioController.h"
#include "../ResourcesManager/ResourceManager.h"


AudioController::AudioController(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* layout=new QVBoxLayout;
	combo=new QComboBox;
	QSlider* horizontalSlider=new QSlider(Qt::Horizontal);
	//
	horizontalSlider->setRange(0,100);
	horizontalSlider->setSingleStep(5);
	horizontalSlider->setValue(100);
	//
	layout->addWidget(combo);
	layout->addWidget(horizontalSlider);
	//
	connect(horizontalSlider, SIGNAL(sliderMoved(int)), &AudioManager::getInstance(), SLOT(setVolume(int)));
	connect(this,SIGNAL(mediaChanged(QString)),&AudioManager::getInstance(),SLOT(setMedia(QString)));
	connect(&AudioManager::getInstance(),SIGNAL(mediaChanged(QString)),this,SLOT(changeMedia(QString)) );
	connect(combo,SIGNAL(activated(QString)),this, SLOT(mediaChosen(QString)));
	//
	setFixedHeight(100);
	setFixedWidth(300);
	setLayout(layout);
}

AudioController::~AudioController()
{

}
