#ifndef BUILDER_H
#define BUILDER_H
#include "ResourceManager.h"
#include "XmlParser.h"
#include "../MenuManager/menumanager.h"
#include "../ExtraWidgets/AudioController.h"
#include "../ExtraWidgets/Login.h"
#include "../ExtraWidgets/HighScores.h"
#include "../QTetrisCore/mainwindow.h"

class Builder
{
public:
	Builder();
	~Builder();
	void build();
	void start();
private:
	XmlParser *xml_parser;
	MenuManager* menu_manager;
	AudioController* audioControl;
	HighScores* scores;
	Login* login_widget;
	MainWindow* QTetris;

};

#endif // BUILDER_H
