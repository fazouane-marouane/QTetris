// Qt
#include <QLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
//
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent),
	w()
{
	QHBoxLayout* mainLayout = new QHBoxLayout();
	QVBoxLayout* rightSide = new QVBoxLayout();
	scoreView= new QLCDNumber(5);
	levelView= new QLCDNumber(5);
	levelView->display(1);
	scoreView->setFixedHeight(50);
	levelView->setFixedHeight(50);
	pauseButton=new QPushButton(QString("Pause"));
	QComboBox *combo = new QComboBox();	// selectionner de mode de rendu des cubes (rendering)
	combo->addItem("Couleurs simples");
	combo->addItem("Gradients");
	combo->addItem("Textures simples");
	combo->setCurrentIndex(1);
	mainLayout->addWidget(&w);
	//
	{	// Next Tetromino widget
		QHBoxLayout* layout = new QHBoxLayout();
		QGroupBox *groupBox = new QGroupBox(tr("Next Tetromino"));
		layout->setSizeConstraint(QLayout::SetMaximumSize);
		layout->addWidget(&wFur);
		groupBox->setLayout(layout);
		rightSide->addWidget(groupBox);
	}
	{	// Score widget
		QHBoxLayout* layout = new QHBoxLayout();
		QGroupBox *groupBox = new QGroupBox(tr("Score"));
		layout->addWidget(scoreView);
		groupBox->setLayout(layout);
		rightSide->addWidget(groupBox);
	}
	{	// level widget
		QHBoxLayout* layout = new QHBoxLayout();
		QGroupBox *groupBox = new QGroupBox(tr("Level"));
		layout->addWidget(levelView);
		groupBox->setLayout(layout);
		rightSide->addWidget(groupBox);
	}
	{	// rendering widget
		QHBoxLayout* layout = new QHBoxLayout();
		QGroupBox *groupBox = new QGroupBox(tr("Rendering mode"));
		layout->addWidget(combo);
		groupBox->setLayout(layout);
		rightSide->addWidget(groupBox);
	}
	{	// pause widget
		rightSide->addWidget(pauseButton);
	}
	//
	rightSide->setSizeConstraint(QLayout::SetMaximumSize);
	mainLayout->addLayout(rightSide);
	setLayout(mainLayout);
	//mainLayout->
	//setFixedHeight(w.frameSize().height()+20);
	connect(combo,SIGNAL(activated(int)),this,SLOT(changeRenderingMode(int)));
	connect(&w,SIGNAL(gameOver()),this,SLOT(stop()) );
}

MainWindow::~MainWindow()
{}

void MainWindow::changeRenderingMode(int mode)
{
	switch(mode)
	{
	case 0:
		renderMode=SIMPLECOLOR; break;
	case 1:
		renderMode=GRADIENT; break;
	case 2:
		renderMode=TEXTURE; break;
	}
}
