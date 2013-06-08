#ifndef Scene_H
#define Scene_H

// std
#include <iostream>
//	Qt
#include <QString>
#include <QWidget>
#include <QTimer>
#include <QTimerEvent>
#include <QDebug>
//
#include "SceneObject.h"
#include "Tetromino.h"

/**
 * \class Scene
 * \brief The Scene class is the scene manager used in the game. It's
 */
class Scene: public QWidget
{
	Q_OBJECT
public:
	Scene(void);
	~Scene(void);

	/**
	 * \brief simplify: regroupe les SceneObjects adjascents entre eux pour reduire le nombre d'objets separes presnets dans la scene.
	 */
	void simplify();

	/**
	 * \brief gravity: fait tomber tout les objets(tout le monde tombe a la meme vitesse) et les relie entre eux (a l'aide de simplify() )
	 */
	void gravity();

	/**
	 * \brief deleteLines: suppression des lignes completes; modifie le score
	 * \return	retourne le score
	 */
	unsigned int deleteLines();

	/**
	 * \brief doPhysics: gere la physique (gravite+ suppressions de lignes multiples...etc)
	 */
	void doPhysics();

	/**
	 * \brief show: affichage de la carte
	 * \return renvoie une chaine de caractere contenant l'ensemble
	 */
	QString show();

	/**
	 * \brief getTeromino:	donne le tetromino courant qu'on manipule
	 * \return le tetromino courant
	 */
	Tetromino getTeromino() const;

	/**
	 * \brief new_Teromino
	 * \param type
	 * \param rotation
	 * \param couleur
	 */
	void new_Teromino(const TetrominoType& type,int rotation,int couleur);

	/**
	 * \brief rotate fait tourner le tetromino courant.
	 *
	 * Si l'objet ne peut pas tourner car il a heurter un autre objet de la scene ou si il heurte un mur,
	 * l'objet sera decaler un peu a droite ou a gauche pour voir s'il peut s'y inserer. Sinon l'objet ne sera pas tourne
	 * car l'action invalide.
	 */
	void rotate();

	/**
	 * \brief makeMove: fait bouger le tetromino courant suivant la commande utilisateur (a droite, a gauche ou vers le bas).
	 * L'action ne sera pas effectuee si elle n'est pas valide.
	 *
	 * \param commande: la commande utilisateur
	 */
	void makeMove(const Movement& commande);
	bool gameOver;
	bool need_new_tetromino;
	bool processing;	/** < le mutex utilise par cette classe et le gamemanager pour ne pas generer d'incoherences entre les deux threads. */
protected:
	void timerEvent(QTimerEvent *event);
private:
	std::set<SceneObject> Objects; /**< l'ensemble des SceneObject presents sur la scene */
	Tetromino CurrentObject;	/** < le tetromino que l'utilisateur manipule */
	QString img;
	QBasicTimer timer;
};

#endif // Scene_H
