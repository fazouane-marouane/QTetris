#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//	Qt
#include <QMainWindow>
#include <QWidget>
#include <QLCDNumber>
#include <QBasicTimer>
#include <QPushButton>
//
#include "widget.h"
#include "Scene.h"
#include "gameManager.h"
#include "NextTetrominoWidget.h"


/**
 * \class MainWindow
 * \brief la fonction principaux du class mainwindow est a construire un GUI pour jour.
 * Il va mettre en semble la widget de jeu, le widget de tetromino suivant, la note,
 * le niveau, les choix des couleurs des pieces...
 * Il va aussi gerer des connections entre les differents elements.
 */
class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
public slots:
	/**
	  * \brief quand le jeu viens de commencer, la fonction start va initiliser l'affichage de niveau et de note
	  * Il va aussi creer des connections entre les elements inclus.
	  */
	void start()
	{
		levelView->display(1);
		scoreView->display(0);
		if(w.G!=NULL)
			delete w.G;
		w.G=new gameManager;
		connect(w.G,SIGNAL(tetrominoChanged(int,int,int)),&wFur,SLOT(display(int,int,int)));
		connect(w.G,SIGNAL(scoreChanged(int)),scoreView,SLOT(display(int)));
		connect(w.G,SIGNAL(nextLevel(int)),levelView,SLOT(display(int)));
		connect(pauseButton,SIGNAL(clicked()),&w,SLOT(pause()));
		w.start();
		w.G->mainLoop();
	}

	/**
	  * \brief Guand la fonction stop recoit un signal de GameOver(), il va envoyer un signal de la note
	  * Il va aussi détruire des connections entre les elements inclus.
	  */
	void stop()
	{
		emit new_Score(scoreView->intValue());
		disconnect(pauseButton,SIGNAL(clicked()),&w,SLOT(pause()));
		disconnect(w.G,SIGNAL(tetrominoChanged(int,int,int)),&wFur,SLOT(display(int,int,int)));
		disconnect(w.G,SIGNAL(scoreChanged(int)),scoreView,SLOT(display(int)));
		disconnect(w.G,SIGNAL(nextLevel(int)),levelView,SLOT(display(int)));
		w.stop();
		delete w.G;
		w.G=NULL;
	}
signals:
	/**
	  * \brief a la fin du jeu la fonction new_score va envoyer un signal au system de HighScores du jeu
	  * \param score : le score obtenu du joueur
	  */
	void new_Score(int score);
protected slots:
	/**
	  * \brief le slot changeRenderingMode va changer le type de rendering conrrespondant au signal
	  * \param mode : le type de rendering
	  * mode = 0 : renderMode=SIMPLECOLOR
	  * mode = 1 : renderMode=GRADIENT
	  * mode = 2 : renderMode=TEXTURE
	  */
	void changeRenderingMode(int mode);
private:
	QBasicTimer timer;
	widget w;
	NextTetrominoWidget wFur;
	QLCDNumber* scoreView;
	QLCDNumber* levelView;
	QPushButton* pauseButton;
};

#endif // MAINWINDOW_H
