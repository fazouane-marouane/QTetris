#ifndef MENUMANAGER_H
#define MENUMANAGER_H
//	std includes
#include <map>
#include <memory>
#include <vector>
//	Qt
#include <QMainWindow>
#include <QStackedWidget>
#include <QStackedLayout>
//
#include "MenuInterface.h"
//#include "../AudioManager/AudioManager.h"


class MenuManager : public QWidget
{
	Q_OBJECT
public:
	MenuManager(QWidget *parent = 0);
	~MenuManager();

public slots:

	void showMenu(QString newMenu)
	{
		if(menusTable.find(newMenu)!=menusTable.end() )
		{
			menusTable[currentMenu]->stop();
			currentMenu=newMenu;
			std::shared_ptr<MenuInterface> subMenu;
			subMenu=menusTable[newMenu];
			stackedLayout->setCurrentWidget(dynamic_cast<QWidget*>(subMenu.get()) );
			subMenu->start();
			update();
			setFixedSize(dynamic_cast<QWidget*>(subMenu.get())->frameSize() );
		}
		else
		{
			close();
		}
	}
public:
	static MenuManager* menuInstance;
	MenuManager& addMenu(const QString& s, MenuInterface* m)
	{
		menusTable[s]=std::shared_ptr<MenuInterface>(m);
		return *this;
	}

	MenuManager& setWidget(const QString& s, QWidget* w);
	MenuManager& setBackButton(const QString& s, const QString& b);
	MenuManager& addSubMenu(const QString& m,const QString& submenu);

	void createLayout()
	{
		stackedLayout = new QStackedLayout;
		for(auto menu = menusTable.begin();menu!=menusTable.end();++menu)
		{
			menu->second->updateMenu();
			stackedLayout->addWidget(dynamic_cast<QWidget*>(menu->second.get()));
		}
		//
		setLayout(stackedLayout);
		mainMenu="Main Menu";
		showMenu(mainMenu);
		setWindowTitle(QString("QTetris") );
		setWindowIcon(QIcon("QTetris.png"));
	}

public:
	std::map<QString,std::shared_ptr<MenuInterface> > menusTable;
	QString mainMenu;
	QString currentMenu;
	QStackedLayout *stackedLayout;
};


#endif // MENUMANAGER_H
