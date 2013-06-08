#ifndef ResourceManager_H
#define ResourceManager_H

//	std includes
#include <map>
#include <string>
#include <functional>
// Qt
#include <QWidget>
//
#include "../MenuManager/MenuInterface.h"

class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		static ResourceManager* ResourceInstance_=NULL;
		if(!ResourceInstance_)
		{
			ResourceInstance=new ResourceManager;
			ResourceInstance_=ResourceInstance;
		}
		if(!ResourceInstance)
		{
			ResourceInstance=new ResourceManager;
			ResourceInstance_=ResourceInstance;
		}
		return *ResourceInstance;
	}

	static void destroy()
	{
		if(ResourceInstance)
			delete ResourceInstance;
		ResourceInstance=NULL;
	}

	ResourceManager& addWidget(const std::string&s,QWidget* w)
	{
		widgets[s]=w;
		return *this;
	}
	ResourceManager& addMacro(const std::string&s,const simpleMacro& m)
	{
		macros[s]=m;
		return *this;
	}
	ResourceManager& addInfo(const QString& info,const QString& content)
	{
		information[info]=content;
		return *this;
	}
	QWidget* getWidget(const std::string& s)
	{
		return widgets[s];
	}

	simpleMacro getMacro(const std::string& s)
	{
		return macros[s];
	}

	QString getInfo(QString info)
	{
		return information[info];
	}

private:
	static ResourceManager* ResourceInstance;
	ResourceManager(void);
	~ResourceManager(void);
	std::map<std::string, QWidget* > widgets;
	std::map<std::string, simpleMacro > macros;
	std::map<QString,QString> information;
};


#endif //ResourceManager_H
