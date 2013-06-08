#ifndef WIDGET_H
#define WIDGET_H

//	Qt
#include <QWidget>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
//
#include "gameManager.h"
#include "Tetromino.h"


/**
 * \class widget
 * \brief Affichager le scene de jeu et traiter préliminairement les controles qui vont etre passe au gameManager.
 */

class widget :public QGraphicsView
{
	Q_OBJECT

public:
	explicit widget(QWidget *parent = 0);
	~widget();
	gameManager* G;
signals:
	/**
	 * \brief emettre le signal de gameOver quand le jeu est termine
	 */
	void gameOver();
protected:
	/**
	 * \brief timerEvent gere l'affichage des pixels dans la scene
	 * \param event : utiliser event->timerID pour verifier c'est le timeur qu'on veau
	 */
	void timerEvent(QTimerEvent *event);

	/**
	 * \brief resizeEvent adapte la taille de "scene", sans lui la scene est trop petite.
	 */
	void resizeEvent(QResizeEvent * event);
public slots:
	/**
	 * \brief pause ou continue le jeu (selon le choix de l'utilisateur)
	 */
	void pause();

	/**
	 * \brief mettre en service le widget
	 */
	void start()
	{
		timer.start(10, this);	// prendre les entrees
	}
	/**
	  * \brief arreter le widget
	  */
	void stop()
	{
		timer.stop();
	}

protected:
	/**
	  * \brief quand le timer et gameManager marche, keyPressEvent() va passer les evenements au GameManager
	  *        sinon il va passer le controle au parent
	  * \param ev : ev signifie le type event, e.g.
	  *  Qt::Key_Up
	  *	 Qt::Key_Right
	  *  Qt::Key_Down
	  *	 Qt::Key_Left
	  */
	void keyPressEvent(QKeyEvent *ev);

	/**
	  * \brief fonction drawBackground va affichager le fond de scene. Cette fonction est geree par Qt.
	  */
	void drawBackground(QPainter *painter, const QRectF &rect);
private:
	QBasicTimer timer;	/** < timer servant a demarrer/stopper/mettre en pause/continuer/ ou accelerer le jeu */
	QGraphicsScene* scene;	/** < gere le cote graphique de la scene */
	Tetromino ancienne_position;
	bool bool_gameover;
};

#endif // WIDGET_H
