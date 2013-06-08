#ifndef Menu_H
#define Menu_H

//	std includes
#include <vector>
//	Qt
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QSignalMapper>
//
#include "MenuInterface.h"
#include "Launcher.h"

class Menu : public QWidget, public MenuInterface
{
public:
	Menu(QWidget* parent=0, simpleMacro onStart_=[](){}, simpleMacro onStop_=[](){} );
	~Menu(void);
	void add_subMenu(QString subMenu);

	virtual void updateMenu()
	{
		QBoxLayout* controlLayout= new QVBoxLayout();
		// fill the menu layout
		std::vector<QPushButton*> menuButtons;
		for(auto label= childNodes.begin();label!=childNodes.end();++label)
		{
			QPushButton* tmp=new QPushButton(*label);
			tmp->setMinimumHeight(30);
			menuButtons.push_back(tmp);
		}
		QSignalMapper *m = new QSignalMapper(this);
		for(auto button= menuButtons.begin();button!=menuButtons.end();++button)
		{
			connect(*button, SIGNAL(clicked()),m, SLOT(map()));
			m->setMapping(*button, (*button)->text());
			controlLayout->addWidget(*button);
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
			connect(backButton, SIGNAL(clicked()),m, SLOT(map()));
			m->setMapping(backButton, "Exit");
		}
		backButton->setMinimumHeight(30);
		controlLayout->addWidget(backButton);
		//
		connect(m, SIGNAL(mapped(QString)), MenuManager::menuInstance, SLOT(showMenu(QString)));
		//
		setLayout(controlLayout);
		setFixedSize(QSize(250,menuButtons.size()*50+60) );
		update();
	}
protected:
	std::vector<QString> childNodes;
};

#endif // Menu_H
