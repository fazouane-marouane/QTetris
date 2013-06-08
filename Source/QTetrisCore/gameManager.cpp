//	std
#include <random>
#include <time.h>
#include <iostream>
//	Qt
#include <QThread>
#include <QDebug>
//
#include "gameManager.h"


gameManager::gameManager(QWidget *parent): QWidget(parent)
{
	var_gameOver=false;

	srand( (unsigned) time(NULL)); //creer le seed
	niveau=1;
	S.processing=false;
	score=0;
	S.show();
	freq_timer=400;
	freq_timer2=10;
	timer.start(freq_timer,this);	// accelerer le rythme du jeu
	timer2.start(freq_timer2,this);	// afficher de maniere reguliere
	timer3.start(2*1000,this);	// augmenter le niveau toute les 20 secondes
	tmpType=rand()%7;
	tmpRotatePosition=rand()%4;
	count=0;
	execution_unique=true;

	tmpCouleur=rand()%sizeof(colorTab);
}

gameManager::~gameManager(void){}


void gameManager::affichage()
{
	S.show();
}

void gameManager::mainLoop()
{
	if(S.need_new_tetromino)
	{	// verifier s'il faut une nouvelle piece ou pas et preparer la suivante
		S.new_Teromino(tmpType,tmpRotatePosition,tmpCouleur);
		tmpType=rand()%7;
		tmpRotatePosition=rand()%4;
		tmpCouleur=rand()%sizeof(colorTab);
		emit tetrominoChanged(tmpType,tmpRotatePosition,tmpCouleur);
	}
	if(S.processing)	// verifier le mutex de la classe Scene (pour ne pas generer d'incoherence)
		return;
	S.processing=true;	// blocker le mutex quand on a la main
	unsigned int n=0;	// stockera le nombre de ligne supprime
	unsigned int tmp=1;
	while(tmp>0)
	{
		tmp=S.deleteLines();	// combien de lignes supprimes en une seule iteration
		n+=tmp;
	}
	S.doPhysics();	// faire tomber les pieces
	isGameOver();	// verifier si le jeux est fini ou pas encore

	if(n!=0)	// calculer le score en fonction du nombre de lignes supprimes
	{
		switch(n%4)
		{
		case 0:
			break;
		case 1:
			score+=10*niveau; break;
		case 2:
			score+=30*niveau; break;
		case 3:
			score+=50*niveau; break;
		}
		score+=80*(n/4)*niveau;	// si n<4 score reste inchange. par contre si l'on arrive a supprimer plus de 4 lignes en meme
								// temps on gagne un joli bonus!
		emit scoreChanged(score);	// donner le signal pour afficher le nouveau score
	}
	S.processing=false;
}

void gameManager::exitGame()
{
	std::cout<<"Game Over!!"<<std::endl;
}


void gameManager::keyPressEvent(QKeyEvent *ev)
{
	switch(ev->key())
	{
	case Qt::Key_Up:
		S.rotate();
		break;
	case Qt::Key_Right:
		S.makeMove(To_RIGHT);
		break;
	case Qt::Key_Down:
		S.makeMove(To_DOWN);
		break;
	case Qt::Key_Left:
		S.makeMove(To_LEFT);
		break;
	case Qt::Key_PageUp:
		break;
	case Qt::Key_PageDown:
		break;
	default:
		QWidget::keyPressEvent(ev);
	}
}

bool gameManager::isGameOver()
//IsGameOver() checks if there are blocks in the first row. That means the game is over.
{
	if(S.gameOver && execution_unique)
	{
		execution_unique=false;
		timer.stop();
		timer2.stop();
		timer3.stop();
		var_gameOver=true;
		exitGame();
	}
	return var_gameOver;
}

void gameManager::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer.timerId()) {
		mainLoop();
		update();
	}
	else if(event->timerId() == timer2.timerId()) {
		affichage();
		update();
	}
	else if(event->timerId() == timer3.timerId()) {
		count++;
		if(count>20)
		{	// accelere le jeu
			timer3.stop();
			freq_timer=std::max(freq_timer-50,20);
			pause();
			niveau++;
			emit nextLevel(niveau);
			pause();
			count=0;
			timer3.start(2*1000,this);
		}
	}
	else {
		QWidget::timerEvent(event);
	}
}
