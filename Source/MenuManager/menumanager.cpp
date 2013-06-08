#include "menumanager.h"
#include "Launcher.h"
#include "Menu.h"
#include "../QTetrisCore/mainwindow.h"

MenuManager* MenuManager::menuInstance=NULL;

MenuManager::MenuManager(QWidget *parent)
	: QWidget(parent),mainMenu("Main Menu"),currentMenu("Main Menu")
{
	menuInstance=this;
}

MenuManager::~MenuManager()
{

}

MenuManager& MenuManager::setWidget(const QString& s, QWidget* w)
{
	dynamic_cast<Launcher*>(menusTable[s].get())->set_Widget(w);
	return *this;
}

MenuManager& MenuManager::setBackButton(const QString& s, const QString& b)
{
	if(b!="")
		menusTable[s]->setParent(b);
	return *this;
}

MenuManager& MenuManager::addSubMenu(const QString& m,const QString& submenu)
{
	menusTable[m]->add_subMenu(submenu);
	return *this;
}
