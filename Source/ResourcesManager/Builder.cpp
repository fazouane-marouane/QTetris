#include "Builder.h"

Builder::Builder():
	xml_parser(NULL),
	menu_manager(NULL),
	audioControl(NULL),
	scores(NULL),
	login_widget(NULL),
	QTetris(NULL)
{
	initializeColors();
}

Builder::~Builder()
{
	// D'apres Qt dans un exemple d'allocation de widget:
	//The button is now a child of the window and will be deleted when the window is destroyed.
	//Note that hiding or closing the window does not automatically destroy it. It will be destroyed when the example exits.

	// Donc Qt gere la desallocation de ses widgets
}

void Builder::build()
{
	AudioManager::getInstance().setVolume(100);

	//	Allocation des ressources
	xml_parser = new XmlParser();
	menu_manager=new MenuManager;
	audioControl=new AudioController;
	scores=new HighScores;
	login_widget= new Login();
	QTetris=new MainWindow;

	//	Creation des branchements
	QObject::connect(login_widget, SIGNAL(userNameChanged(QString)), scores,SLOT(updateUserName(QString)));
	QObject::connect(login_widget,SIGNAL(logged()),QTetris,SLOT(start()));
	QObject::connect(QTetris,SIGNAL(new_Score(int)),scores,SLOT(addScore(int)));
	//	Exposer des widgets et des macros au gestionnaire de ressources
	ResourceManager::getInstance()
			.addWidget("Menu Manager",menu_manager)
			.addWidget("Volume Controller",audioControl)
			.addWidget("HighScores",scores)
			.addWidget("Login",login_widget)
			.addWidget("QTetris",QTetris)
			.addMacro("Play music",	[](){AudioManager::getInstance().playMusic();})
			.addMacro("Stop music",	[](){AudioManager::getInstance().stopMusic();})
			.addMacro("Nothing",	[](){});
}

void Builder::start()
{
	//	Creer le menu et lancer le menu principal
	if(xml_parser!=NULL && xml_parser->parse())
	{
		menu_manager->show();
	}
	else
	{
		exit(1);
	}
}
