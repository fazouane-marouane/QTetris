#ifndef Launcher_H
#define Launcher_H

//	 std includes
#include <vector>
//	Qt
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QSignalMapper>
//
#include "MenuInterface.h"
#include "menumanager.h"

// interface pour les menus simple ou pour la fenetre du jeu
class Launcher : public QWidget, public MenuInterface
{
public:
	Launcher(QWidget* parent=0, simpleMacro onStart_=[](){}, simpleMacro onStop_=[](){} ):
		QWidget(parent), MenuInterface(onStart_, onStop_){ widgetLaunched=NULL;}
	~Launcher(void)
	{}
	void set_Widget(QWidget* widgetLaunched_)
	{
		widgetLaunched=widgetLaunched_;
		widgetLaunched->show();
	}
	virtual void updateMenu()
	{
		QBoxLayout* controlLayout= new QVBoxLayout();
		QSignalMapper *m = new QSignalMapper(this);
		if(widgetLaunched)
		{
			controlLayout->addWidget(widgetLaunched);
		}
		// Back button
		QPushButton* backButton;
		if(!parentNode.isEmpty())
		{
			backButton= new QPushButton("Back");
			connect(backButton, SIGNAL(clicked()),m, SLOT(map()));
			m->setMapping(backButton, parentNode);
		}
		else
		{
			backButton= new QPushButton("Exit");
			connect(backButton, SIGNAL(clicked()), MenuManager::menuInstance, SLOT(Exit()));
		}
		backButton->setMinimumHeight(30);
		controlLayout->addWidget(backButton);
		//
		connect(m, SIGNAL(mapped(QString)), MenuManager::menuInstance, SLOT(showMenu(QString)));
		//
		setLayout(controlLayout);
		setMinimumHeight(widgetLaunched->frameSize().height()+80);
		setMinimumWidth(widgetLaunched->frameSize().width()+20);
		setMaximumWidth(widgetLaunched->frameSize().width()+80);
		update();
	}
private:
	QWidget* widgetLaunched;
};

#endif // Launcher_H
