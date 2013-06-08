#ifndef MenuInterface_H
#define MenuInterface_H

// std includes
#include <functional>
//	Qt
#include <QString>
#include <QWidget>

typedef std::function<void(void)> simpleMacro; /** < fonctions lambdas a executer lors d'evenements particuliers */

/**
 * \brief L'interface MenuInterface sert a regrouper les fonctionnalites communes ou pas de la classe Launcher et de la classe Menu.
 * Elle sert a manipuler les deux classes filles indifferement et a limiter les redondances de code.
 */
class MenuInterface
{
public:
	MenuInterface(simpleMacro onStart_=[](){}, simpleMacro onStop_=[](){} ):
		onStart(onStart_), onStop(onStop_) {}
	~MenuInterface(void){}
	virtual QString getType() const
	{ return ""; }
	virtual void add_subMenu(QString subMenu){}
	virtual void setParent(QString parentMenu)
	{parentNode=parentMenu;}
	virtual void start()
	{
		onStart();
	}
	virtual void stop()
	{
		onStop();
	}

	virtual void updateMenu()
	{}
protected:
	simpleMacro onStart;
	simpleMacro onStop;
	QString parentNode;
};

#endif  // MenuInterface_H
