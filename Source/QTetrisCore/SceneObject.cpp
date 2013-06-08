//	std
#include <map>
//	Qt
#include <QBrush>
//
#include "SceneObject.h"

//
int Size_x=20; /**< nombre de lignes dans la scene */
int Size_y=10; /**< nombre de colonnes dans la scene */

// rendu de la scene
char colorTab[]={'r','b','g','y','o','k'};	/**< Tableau de noms des couleurs possibles des pieces */
std::map<QChar,QColor> colorTab2;	/**< Table de correspondance des couleurs et de leurs noms */
RENDERTYPE renderMode=GRADIENT; /**< type de rendu de la scene. Les valeurs possibles: GRADIENT, TEXTURE ,GRADIENT */ //TEXTURE;//GRADIENT;


QBrush renderCube(const QChar color,const int x,const int y)
{
	QBrush brush;
	if(renderMode==SIMPLECOLOR)
		brush=colorTab2[color];
	else if(renderMode==GRADIENT)
	{
		QRadialGradient gradient(y, x, 20);
		gradient.setColorAt(0, colorTab2[color]);
		gradient.setColorAt(1, colorTab2[color].dark());
		brush=gradient;
	}
	else if(renderMode==TEXTURE)
	{
		brush.setStyle(Qt::DiagCrossPattern);
	}
	return brush;
}

void initializeColors()
{
	colorTab2[colorTab[0]]=QColor(255,0,0);
	colorTab2[colorTab[1]]=QColor(0,0,255);
	colorTab2[colorTab[2]]=QColor(30,150,10);
	colorTab2[colorTab[3]]=QColor(255,255,0);
	colorTab2[colorTab[4]]=QColor(255,128,0);
	colorTab2[colorTab[5]]=QColor(100,100,100);
}

SceneObject::SceneObject(int x, int y)
{
	if(x>=0 || y>=0)
		scene_basic_objects.insert(Points(std::tuple<int,int>(x,y),'r'));	// un petit cube
}

SceneObject::~SceneObject(void)
{
}

bool SceneObject::operator==(const SceneObject& Obj) const
{
	if(Obj.scene_basic_objects.size() != scene_basic_objects.size() )return false;
	// les deux objets on le meme nombre d'elements
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(	Obj.scene_basic_objects.find(*itr)==Obj.scene_basic_objects.end())
		{
			return false;
		}
	}
	return true;
}

bool SceneObject::operator<(const SceneObject& Obj) const
{
	Points upper_Bound(std::tuple<int,int>(Size_x,Size_y),'b');
	Points Obj_Upper_Bound(std::tuple<int,int>(Size_x,Size_y),'b');
	if( Obj.scene_basic_objects.size()==0 )return false;
	for(std::set<Points>::iterator itr= scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)<get_x(upper_Bound) )
			upper_Bound=*itr;
		else if(get_x(*itr)==get_x(upper_Bound) && get_y(*itr)<get_y(upper_Bound) )
			upper_Bound=*itr;
	}
	for(std::set<Points>::iterator itr= Obj.scene_basic_objects.begin();
		itr!=Obj.scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)<get_x(Obj_Upper_Bound) )
			Obj_Upper_Bound=*itr;
		else if(get_x(*itr)==get_x(Obj_Upper_Bound) && get_y(*itr)<get_y(Obj_Upper_Bound) )
			Obj_Upper_Bound=*itr;
	}
	if(get_x(upper_Bound)<get_x(Obj_Upper_Bound))
		return false;
	if(get_x(upper_Bound)==get_x(Obj_Upper_Bound) && get_y(upper_Bound)<=get_y(Obj_Upper_Bound) )
		return false;
	return true;
}

bool SceneObject::hitsTheFloor() const
{
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)==Size_x-1)
			return true;
	}
	return false;
}

bool SceneObject::hitsTheFloor2() const
{
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)>=Size_x)
			return true;
	}
	return false;
}

bool SceneObject::hitsTheCeil() const
{
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)==-1)
			return true;
	}
	return false;
}

bool SceneObject::hitsTheWall() const
{
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end();++itr)
	{
		if(get_y(*itr)>=Size_y || get_y(*itr)<0)
			return true;
	}
	return false;
}


bool SceneObject::collide(const SceneObject& Obj) const
{
	bool collide_bool=false;
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end() && !collide_bool;++itr)
	{
		for(std::set<Points>::iterator itr2=Obj.scene_basic_objects.begin();
			itr2!=Obj.scene_basic_objects.end();++itr2)
		{
			if(	std::get<0>(*itr)==std::get<0>(*itr2) )
			{
				collide_bool=true;
				break;
			}
		}
	}
	return collide_bool;
}

bool SceneObject::isAdjascent(const SceneObject& Obj) const
{
	bool adjascence_bool=false;
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end() && !adjascence_bool;++itr)
	{
		int x=get_x(*itr);
		int y=get_y(*itr);
		for(std::set<Points>::iterator itr2=Obj.scene_basic_objects.begin();
			itr2!=Obj.scene_basic_objects.end();++itr2)
		{
			if(std::get<0>(*itr2)==std::tuple<int,int>(x,y-1) ||
					std::get<0>(*itr2)==std::tuple<int,int>(x,y+1))
			{
				adjascence_bool=true;
				break;
			}
		}
	}
	return adjascence_bool;
}

bool SceneObject::isUnder(const SceneObject& Obj) const
{
	bool under_bool=false;
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();
		itr!=scene_basic_objects.end() && !under_bool;++itr)
	{
		int x=get_x(*itr);
		int y=get_y(*itr);
		for(std::set<Points>::iterator itr2=Obj.scene_basic_objects.begin();
			itr2!=Obj.scene_basic_objects.end();++itr2)
		{
			if(std::get<0>(*itr2)==std::tuple<int,int>(x-1,y))
			{
				under_bool=true;
				break;
			}

		}
	}
	return under_bool;
}

void SceneObject::glue(SceneObject Obj)
{
	for(std::set<Points>::iterator itr=Obj.scene_basic_objects.begin();
		itr!=Obj.scene_basic_objects.end();++itr)
		scene_basic_objects.insert(*itr);
}

SceneObject SceneObject::simple_fall() const
{
	SceneObject tmp(-1,-1);	// objet vide
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();itr!=scene_basic_objects.end();++itr)
		tmp.scene_basic_objects.insert(Points(std::tuple<int,int>(get_x(*itr)+1,get_y(*itr) ),get_color(*itr)));
	return tmp;
}

void SceneObject::print(char** map) const
{
	for(std::set<Points>::iterator itr=scene_basic_objects.begin();itr!=scene_basic_objects.end();++itr)
	{
		if(get_x(*itr)>=0 &&get_y(*itr)>=0)
			map[get_x(*itr)][get_y(*itr)]=get_color(*itr);
	}
}

std::tuple<std::set<SceneObject>,bool> SceneObject::deleteLine(int l) const
{
	std::set<SceneObject> tmp;
	std::set<Points> copy=scene_basic_objects;	// temp object
	// suppression de la ligne: l
	{
		std::set<Points>::iterator itr=copy.begin(), itr0=copy.begin();
		int j=0;
		for(;itr!=copy.end();++itr)
		{
			if(std::get<0>(*itr)==std::tuple<int,int>(l,j))
			{
				itr0=itr;
				itr0++;
				copy.erase(itr);
				itr=itr0;
				break;
			}
		}
		if(itr==copy.end())
			return std::tuple<std::set<SceneObject>,bool>(tmp,false);
		itr=itr0;
		j++;
		while(j<Size_y && itr!=copy.end())
		{
			while(itr!=copy.end() && std::get<0>(*itr)!=std::tuple<int,int>(l,j))
			{
				itr++;
			}
			if(itr==copy.end())
				break;
			itr0=itr;
			itr0++;
			copy.erase(itr);
			itr=itr0;
			j++;
		}
		if(j<Size_y)
			return std::tuple<std::set<SceneObject>,bool>(tmp,false);
	}
	//
	while(! copy.empty())	// while there's stil some basic objects
	{
		std::set<Points>::iterator itr= copy.begin();	// pick the first basic object (simple cube)
		SceneObject Obj(-1,-1);
		Obj.scene_basic_objects.insert(*itr);
		itr++;
		for(;itr!=copy.end();++itr)	// traiter les objets suivants
		{
			bool new_point=false;
			do
			{
				new_point=false;
				for(std::set<Points>::iterator itr2=Obj.scene_basic_objects.begin();
					itr2!=Obj.scene_basic_objects.end();++itr2)
				{
					Points P1=*itr;
					Points P2=*itr2;
					int d_x=std::abs(get_x(P1)-get_x(P2) );
					int d_y=std::abs(get_y(P1)-get_y(P2) );

					if((d_x+d_y)==1 && Obj.scene_basic_objects.find(*itr)==Obj.scene_basic_objects.end() )
					{
						Obj.scene_basic_objects.insert(*itr);
						new_point=true;
						break;
					}
				}
			}while(new_point==true);
		}
		tmp.insert(Obj);
		// on reduit la taille de 'copy'
		itr=Obj.scene_basic_objects.begin();
		for(;itr!=Obj.scene_basic_objects.end();++itr)
		{
			copy.erase(*itr);
		}
	}
	//
	return std::tuple<std::set<SceneObject>,bool>(tmp,true);
}
