#ifndef SceneObject_H
#define SceneObject_H

//	std
#include <set>
#include <tuple>
#include <algorithm>
//	Qt
#include <QBrush>
#include <QChar>
#include <map>
//
extern int Size_x;
extern int Size_y;

/// Objets et fonctions servant a definir les modes de rendus possibles dans le jeu
typedef enum{ SIMPLECOLOR,GRADIENT,TEXTURE} RENDERTYPE;
extern char colorTab[6];
extern std::map<QChar,QColor> colorTab2;
extern RENDERTYPE renderMode;
void initializeColors();
QBrush renderCube(const QChar color,const int x,const int y);

/// Definition de macros servant a manipuler les objets du type Points pour rendre le code plus lisible
typedef std::tuple<std::tuple<int,int>,char > Points; /**< Contient les coordonees(x,y) du point et sa couleur(char) */
/**
 * \brief get_x
 * \param P: le point
 * \return la valeur de x du point P
 */
inline int get_x(const Points& P)
{
	return std::get<0>(std::get<0>(P));
}
/**
 * \brief get_y
 * \param P: le point
 * \return la valeur de y du point P
 */
inline int get_y(const Points& P)
{
	return std::get<1>(std::get<0>(P));
}
/**
 * \brief get_color
 * \param P: le point
 * \return la valeur de la couleur(sous forme de caractere) du point P
 */
inline char get_color(const Points& P)
{
	return std::get<1>(P);
}

/**
 * \brief The SceneObject class
 */
class SceneObject
{
public:
	SceneObject(int x,int y);
	~SceneObject(void);
	//
	/**
	 * \brief Operateur de comparaison ==
	 * \param Obj: un autre SceneObject a comparer avec l'objet courant
	 * \return true si Obj est egale a l'object courante (point par point) sans prendre en consideration des couleurs
	 */
	bool operator==(const SceneObject& Obj) const;

	/**
	 * \brief Operateur de comparaison <
	 *
	 * Par definition(le fonctionnement intrinseque de la classe Scene qui stock les SceneObject), les SceneObjects qu'on manipule
	 * sont disjoints. On peut alors creer une relation d'ordre en comparant les cubes elementaires les plus grands de Obj et de l'objet courant.
	 *
	 * \param Obj
	 * \return true si Obj est plus petit le l'objet courant
	 */
	bool operator<(const SceneObject& Obj) const;

	/**
	 * \brief hitsTheFloor verifie si l'objet est arrive a la dernier ligne en bas. Typiquement, le SceneObject present sur la scene
	 * ne peut plus descendre plus bas quand cette methode retourne true.
	 * \return true si l'objet atteint la derniere ligne du bas
	 */
	bool hitsTheFloor() const;

	/**
	 * \brief hitsTheFloor2 verifie si l'objet est enfonce en bas de la scene.
	 * \return true si une partie de l'SceneObject courant depasse le bas de la scene
	 */
	bool hitsTheFloor2() const;

	/**
	 * \brief hitsTheCeil verifie si l'objet est enfonce en haut de la scene.
	 * \return true si une partie de l'SceneObject courant depasse le haut de la scene
	 */
	bool hitsTheCeil() const;

	/**
	 * \brief hitsTheWall
	 * \return true si une partie de l'SceneObject courant depasse la scene de l'un des deux cotes.
	 */
	bool hitsTheWall() const;

	/**
	 * \brief collide: verifie la collision entre deux SceneObject, c'est a dire les deux possedent des parties
	 * qui occupent la meme zone spaciale(meme x et y) sur la scene.
	 *
	 * \param Obj: l'autre SceneObject a comparer avec le SceneObjet courant
	 * \return true s'il y a collision.
	 */
	bool collide(const SceneObject& Obj) const;

	/**
	 * \brief isAdjascent verifie si les deux SceneObject sont adjascents, c'est a dire si l'un deux possede une partie qui est
	 * directement a droite de l'autre(ou a sa gauche...).
	 *
	 * \param Obj: l'autre SceneObject a comparer avec le SceneObjet courant
	 * \return true si Obj et l'objet courant sont adjascents
	 */
	bool isAdjascent(const SceneObject& Obj) const;

	/**
	 * \brief isUnder verifie si l'objet courant possede une partie qui est directement en dessus de Obj.
	 * \param Obj: l'autre SceneObject a comparer avec le SceneObjet courant
	 * \return retourn true si l'objet courant possede une partie qui est directement en dessus de Obj
	 */
	bool isUnder(const SceneObject& Obj) const;

	/**
	 * \brief glue: comme le nom l'indique, cette fonction colle Obj a l'object courant.
	 * Rien n'interdit de coller deux SceneObject, pourvu qu'ils soient disjoints, mais pour preserver la logique du jeu,
	 * il ne faut coller que les objets proches entre eux(qui peuvent former un bloc unique).
	 *
	 * \param Obj: le SceneObjet a coller avec l'object courant
	 */
	void glue(SceneObject Obj);

	/**
	 * \brief simple_fall: fait tomber l'objet courant d'une ligne
	 * \return la copie de l'objet courant translate vers le bas.
	 */
	SceneObject simple_fall() const;

	/**
	 * \brief deleteLine: verifie supprime la ligne l si celle-ci peut etre complete.
	 *
	 * Apres suppression, on obtient des fragments connexes qui composent l'objet courant apres suppression de la ligne.
	 *
	 * \param l: la ligne a supprimer
	 * \return les fragments connexes de l'objet courant apress suppression+ un boolean qui est egale a true s'il y a eu suppression
	 */
	std::tuple<std::set<SceneObject>,bool> deleteLine(int l) const;

	/**
	 * \brief print: affiche le contenu du SceneObject courant sur le tableau passe en parametre
	 * \param map tableau de taille [Size_x][Size_y]
	 */
	void print(char** map) const;
protected:
	std::set<Points> scene_basic_objects;
};

#endif
