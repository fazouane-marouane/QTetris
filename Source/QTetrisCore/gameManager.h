#ifndef GameManager_H
#define GameManager_H

//	Qt
#include <QKeyEvent>
#include <QBasicTimer>
#include <QWidget>
#include <QTimer>
//
#include "Scene.h"
#include "SceneObject.h"
#include "Tetromino.h"


/**
 * \class gameManager
 * \brief le class gameMangager va gerer les regles du jeu, e.g. le choi de tetromino a l'instant et a l'avenir,
 * la note, la niveau de difficulte, la vitenesse de jeu...
 */
class gameManager : public QWidget
{
	Q_OBJECT

public:
	gameManager(QWidget* parent=0);
	~gameManager(void);

	/**
	  * \brief mainloop : gerer les fontions ci-dessous
	  * 1) verifier si on a besoin un nouveau tetrimino par la valeur de "S.need_new_tetromino"
	  * 2) appeler S.doPhysics() : gerer la physique (gravite+ suppressions de lignes multiples...etc)
	  * 3) verifier le nombre de lignes supprime a la meme temps, et calculer la note.
	  * 4) appeler isGameOver(): verifier si le jeu est termine
	  */
	void mainLoop();

	/**
	  * \brief affichage
	  *  Appeler S.show() regulierement pour quelle ait une copie plus recente de son etat lorsqu'on voudra effectivement l'afficher a l'ecran.
	  */
	void affichage();

	/**
	 * \brief show: sert d'intermediaire entre la classe Scene et le widget d'affichage
	 *
	 * \return renvoi "Game Over" si le jeu a termine, sinon elle renvoi le dernier etat en date de la scene du Tetris
	 */
	QString Show()
	{
		if(var_gameOver)
			return "Game Over";
		return S.show();
	}

	/**
	  * \brief getScore: getter de la valeur courante du score
	  * \return score : la note que le joueur a gagne
	  */
	unsigned int getScore()
	{
		return score;
	}

	/**
	  * \brief getTeromino getter du tetromino courant
	  * \return S.getTeromino : le Tetromino courant(la piece qui tombe)
	  */
	Tetromino getTeromino()
	{
		return S.getTeromino();
	}

	/**
	  * \brief need_newTetromino
	  * \return S.need_new_tetromino : true si c'est on si on a besoin un nouveau Tetromino
	  */
	bool need_newTetromino()
	{
		return S.need_new_tetromino;
	}

	/**
	  * \brief exitGame : juste pour debug
	  * Affichage "Game Over" si le jeu est termine
	  */
	void exitGame();

	/**
	  * \brief IsGameOver
	  *  Si le valeur de "S.gameOver" = true, il va arreter tous les timeurs et fair "var_gameOver" = ture
	  */
	bool isGameOver();



public slots:
	/**
	 * \brief pause sert a mettre le gamemanager en pause ou a le relancer
	 */
	void pause()
	{
		if(timer.isActive())
		{
			timer.stop();
			timer2.stop();
			timer3.stop();
		}
		else
		{
			timer.start(freq_timer,this);
			timer2.start(freq_timer2,this);
			timer3.start(2*1000,this);
		}
	}

	/**
	  * \brief gestion des controles de clavier
	  * \param ev : "Qt::Key_Up"    = retourner
	  *             "Qt::Key_Right" = bouger a droit
	  *             "Qt::Key_Down"  = acceleration
	  *             "Qt:Key_Left"   = bouger a gauche
	  */
	void keyPressEvent(QKeyEvent *ev);
protected:
	/**
		* \brief timerEvent va gerer les "timer event"
		* \param event utiliser event->timerID pour verifier c'est le timeur qu'on veau:
		* event->time.timerID: appeler mainloop()
		* event->time2.timerID: appeler affichage()
		* event->time3.timerID: gerer les niveaus
		*/
	void timerEvent(QTimerEvent *event);

signals:
	/**
		* \brief scoreChanged va emettre un signal quand on a une nouvelle note
		* \param score<int> : la nouvelle note
		*/
	void scoreChanged(int);

	/**
	  * \brief nextLevel va emettre un signal quand on a un nouveau niveau
	  * \param niveau<int> : le nouveau niveau
	  */
	void nextLevel(int);

	/**
		* \brief tetrominoChanged va emettre un signal quand on a un nouveau tetromino
		* \param tmpType<int> : le type de tetromino
		* \param tmpRotatePosition<int> : la postition de rotation de tetromino
		* \param tmpCouleur<int> : le couleur de tetromino
		*/
	void tetrominoChanged(int,int,int);

private:
	bool var_gameOver; /** < Si le game a fini , var_gmaeover=true; */
	Scene S;
	QBasicTimer timer; /** < accelerer le rythme du jeu */
	QBasicTimer timer2;/** < afficher de maniere reguliere */
	QBasicTimer timer3;/** < augmenter le niveau toute les 20 secondes */
	int score; /** < la note que le joueur a gagne */
	int freq_timer;
	int freq_timer2;
	int niveau;	/** le niveau de la difficulté */
	int  tmpType;
	int tmpRotatePosition;
	int tmpCouleur;
	int count;
	bool execution_unique;
};

#endif // GameManager_H
