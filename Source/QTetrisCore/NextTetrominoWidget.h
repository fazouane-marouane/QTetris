#ifndef NextTetrominoWidget_H
#define NextTetrominoWidget_H

//	Qt
#include <QWidget>
#include <QGraphicsView>
//
#include "gameManager.h"
#include "Tetromino.h"

/**
 * \class NextTetrominoWidget
 * \brief Cette classe est un objet qui peut etre present dans "scene" qui se trouve dans le coin de l'ecran.
 * Il represente la piece a venir.
 */
class NextTetrominoWidget : public QGraphicsView
{
	Q_OBJECT

public:
	explicit NextTetrominoWidget(QWidget *parent = 0);
	~NextTetrominoWidget();

public slots:
public slots:
	/**
	 * \brief display va affichager la piece suivante sur l'ecrain
	 * \param tmpType<int> : le type de tetromino
	 * \param tmpRotatePosition<int> : la postition de rotation de tetromino
	 * \param tmpCouleur<int> : le couleur de tetromino
	 */
	void display(int,int,int);

private:
	QGraphicsScene* scene; /** < "scene" est la partie de l'ecran qui va affichager la piece suivante*/
};

#endif // NextTetrominoWidget_H
