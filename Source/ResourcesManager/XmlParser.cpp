// std
#include <iostream>
//
#include "XmlParser.h"
#include "ResourceManager.h"
#include "../MenuManager/Launcher.h"
#include "../MenuManager/Menu.h"
#include "../MenuManager/menumanager.h"
#include "../ExtraWidgets/AudioController.h"


XmlParser::XmlParser(QWidget *parent) : QWidget(parent)
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::parse()
{
	QDomDocument dom("mon_xml");
	QFile file("config.xml");
	if (!file.open(QIODevice::ReadOnly))
		return false;
	if (!dom.setContent(&file))
	{
		file.close();
		return false;
	}
	file.close();
	QDomElement docElem = dom.documentElement();
	QDomNode n = docElem.firstChild();
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		if(e.tagName()=="MenuConfiguration")
		{
			constructMenu(e.firstChild(),"");
		}
		else if(e.tagName()=="MediaPlayer")
		{
			constructMediaPlayer(e.firstChild());
		}

		n = n.nextSibling();
	}
	MenuManager* m=dynamic_cast<MenuManager*>(ResourceManager::getInstance().getWidget("Menu Manager") );
	m->createLayout();
	return true;
}

void XmlParser::constructMediaPlayer(QDomNode n)
{
	AudioController* audio_controller=dynamic_cast<AudioController*>(ResourceManager::getInstance().getWidget("Volume Controller") );
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		if(e.tagName()=="media" && e.hasAttribute("title") && e.hasAttribute("file"))
		{
			audio_controller->addMedia(e.attribute("title"));
			AudioManager::getInstance().addMedia(e.attribute("title"), e.attribute("file"));
		}
		n = n.nextSibling();
	}
}

void XmlParser::constructMenu(QDomNode n,const QString& s)
{
	MenuManager* m=dynamic_cast<MenuManager*>(ResourceManager::getInstance().getWidget("Menu Manager") );
	while(!n.isNull())
	{
		QDomElement e = n.toElement();
		simpleMacro onstart=[](){},onexit=[](){};
		QString back=s;
		QString widgetName=e.attribute("title");
		QWidget* w;
		if(e.hasAttribute("onStart"))
			onstart=ResourceManager::getInstance().getMacro(e.attribute("onStart").toStdString());
		if(e.hasAttribute("onExit"))
			onexit=ResourceManager::getInstance().getMacro(e.attribute("onExit").toStdString());
		if(e.hasAttribute("backButton"))
			back=e.attribute("backButton");
		if(e.hasAttribute("widget") )
			widgetName=e.attribute("widget");
		//
		//QMessageBox::information(NULL, "Information","Parent: "+back+" | "+ e.attribute("title"));
		if(e.tagName()=="menu")
		{
			m->addMenu(e.attribute("title"),new Menu(0,onstart,onexit))
					.setBackButton(e.attribute("title"),back);
			constructMenu(e.firstChild(),e.attribute("title"));
			QDomNode child=e.firstChild();
			while(!child.isNull())
			{
				QDomElement child_elem = child.toElement();
				m->addSubMenu(e.attribute("title"),child_elem.attribute("title"));
				child = child.nextSibling();
			}
		}
		else
		{
			w=ResourceManager::getInstance().getWidget(widgetName.toStdString());
			m->addMenu(e.attribute("title"),new Launcher(0,onstart,onexit) )
					.setWidget(e.attribute("title"),w)
					.setBackButton(e.attribute("title"),back);
		}
		n = n.nextSibling();
	}
}
