#ifndef Tetromino_H
#define Tetromino_H
#include "sceneobject.h"

typedef int TetrominoType;

/**
 * \enum Movement
 */
typedef enum{
	To_LEFT, /*!< fait bouger l'objet à gauche. */
	To_RIGHT, /*!< fait bouger l'objet à droite. */
	To_DOWN /*!< descent l'objet vers le bas. */
} Movement;


/**
 * \class Tetromino
 * \brief La classe Tetromino est un objet qui peut etre lui aussi present dans la Scene.
 * Il represente la piece tombante que l'utilisateur peut controller.
 *
 */
class Tetromino : public SceneObject
{
//	friend class widget;
public:
	Tetromino(void);

	/**
	 * \brief Constructeur Tetromino
	 * \param type :	l'entier qui determine le type de tetromino(L,T,Z...).
	 * Il s'agit du premier indice du tableau tetrominoDatabase. Il varie donc entre 0 et 6.
	 * \param rotatePosition :	l'entier qui determine la rotation de tetromino(L,T,Z...).
	 * Il s'agit du deuxieme indice du tableau tetrominoDatabase. Il varie entre 0 et 3.
	 * \param couleur :	L'entier qui determine la couleur. Il s'agit de l'indice de colorTab.
	 */
	Tetromino(const TetrominoType& type,const int rotatePosition,int couleur);
	~Tetromino(void);

	/**
	 * \brief move
	 *
	 * Cree une copie de l'objet avec l'une transformation du type To_LEFT,...
	 *
	 * \param commande:	la transformation à appliquer à l'objet courant.
	 * \return la copie transformée de l'objet courant.
	 */
	Tetromino move(const Movement& commande) const;

	/**
	 * \brief rotate
	 *
	 * Cree une copie de l'objet avec une rotation comme transformation.
	 *
	 * \return la copie transformée de l'objet courant.
	 */
	Tetromino rotate() const;

private:
	Points center;	/*!< la position du centre de l'objet(position et couleur). Sert de referentiel pour tout le tetromino */
	int rotatePosition;
	int elementType;
};

#endif
