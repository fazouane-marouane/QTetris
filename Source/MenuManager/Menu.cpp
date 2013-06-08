#include "Menu.h"


Menu::Menu(QWidget* parent, simpleMacro onStart_, simpleMacro onStop_):
	QWidget(parent),
	MenuInterface(onStart_, onStop_)
{
}

Menu::~Menu(void)
{
}

void Menu::add_subMenu(QString subMenu)
{
	childNodes.push_back(subMenu);
}
