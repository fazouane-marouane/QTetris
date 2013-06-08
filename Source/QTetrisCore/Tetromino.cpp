#include "Tetromino.h"

extern int tetrominoDatabase[7 /*elementType */ ][4 /* rotatePosition */ ][5 /* ligne_x */ ][5 /* column_y */ ];

Tetromino::Tetromino(void):SceneObject(-1,-1), center(std::tuple<int,int>(-1,-1),'r'),rotatePosition(0),elementType(0)
{
}


Tetromino::~Tetromino(void)
{
}

Tetromino::Tetromino(const TetrominoType& type,const int rotatePosition_,int couleur):
	SceneObject(-1,-1),center(std::tuple<int,int>(-3,Size_y/2),colorTab[couleur]), rotatePosition(rotatePosition_),elementType(type)
{
	// Construct the sceneObject
	// Remarque: De la position du centre et du sens de l'objet(la rotatePosition) on deduit
	//			la position des autres cubes basiques(les objets elementaires) qui composent le tetromino.
	for(int i=0;i<5;++i)
	{
		for(int j=0;j<5;++j)
		{
			if(tetrominoDatabase[elementType][rotatePosition][i][j]==1)
				scene_basic_objects.insert(Points(std::tuple<int,int>(i-5,j+Size_y/2-2),get_color(center)));
		}
	}
}

Tetromino Tetromino::rotate() const
{
	Tetromino Tmp;
	Tmp.rotatePosition=(rotatePosition+1)%4;
	Tmp.elementType=elementType;
	Tmp.center=center;
	//
	for(int i=0;i<5;++i)
	{
		for(int j=0;j<5;++j)
		{
			if(tetrominoDatabase[Tmp.elementType][Tmp.rotatePosition][i][j]==1)
				Tmp.scene_basic_objects.insert(Points(std::tuple<int,int>(i-2+get_x(center) ,j+get_y(center)-2),get_color(center)));
		}
	}
	return Tmp;
}

Tetromino Tetromino::move(const Movement& commande) const
{
	Tetromino Tmp;
	Tmp.rotatePosition=rotatePosition;
	Tmp.elementType=elementType;
	//
	Points repere;
	switch(commande)
	{
	case To_LEFT:
		repere=Points(std::tuple<int,int>(get_x(center),get_y(center)-1),get_color(center)); break;
	case To_RIGHT:
		repere=Points(std::tuple<int,int>(get_x(center),get_y(center)+1),get_color(center)); break;
	case To_DOWN:
		repere=Points(std::tuple<int,int>(get_x(center)+1,get_y(center)),get_color(center)); break;
	};
	for(int i=0;i<5;++i)
	{
		for(int j=0;j<5;++j)
		{
			if(tetrominoDatabase[Tmp.elementType][rotatePosition][i][j]==1)
				Tmp.scene_basic_objects.insert(Points(std::tuple<int,int>(i-2+ get_x(repere),j+get_y(repere)-2),get_color(center)));
		}
	}
	Tmp.center=repere;
	return Tmp;
}
