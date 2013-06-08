//	std
#include <time.h>
//
#include "Scene.h"


Scene::Scene(void) // No Tetromino at the begining
{
	need_new_tetromino=true;
	gameOver=false;
	processing=false;
	srand(time(NULL));
	simplify();
	show();
}


Scene::~Scene(void)
{
}

Tetromino Scene::getTeromino() const
{
	return CurrentObject;
}

QString Scene::show()
{
	if(processing)
		return img;
	char** map=new char*[Size_x];
	for(int i=0;i<Size_x;++i)
		map[i]=new char[Size_y];
	for(int i=0;i<Size_x;++i)
		for(int j=0;j<Size_y;++j)
			map[i][j]=' ';
	if(!need_new_tetromino)
		CurrentObject.print(map);
	for(std::set<SceneObject>::iterator itr=Objects.begin(); itr!=Objects.end();++itr)
		itr->print(map);
	QString s("");
	for(int i=0;i<Size_x;++i)
	{
		for(int j=0;j<Size_y;++j)
		{
			s+=map[i][j];
		}
	}
	img=s;
	for(int i=0;i<Size_x;++i)
		delete[] map[i];
	delete[] map;
	return s;
}

// faire coller les objets adjascents ou d'en dessous/dessus
void Scene::simplify()
{
	if(Objects.empty()) return;
	std::set<SceneObject>::iterator itr=Objects.begin();
	while(itr!=Objects.end())
	{
		std::set<SceneObject> tmp;
		for(std::set<SceneObject>::iterator itr2=Objects.begin();itr2!=Objects.end();++itr2)
		{
			if(itr2==itr)
				continue;
			bool adj=itr->isAdjascent(*itr2);
			bool under=itr->isUnder(*itr2);
			if(adj || under )
				tmp.insert(*itr2);
		}
		if(!tmp.empty() )
		{
			SceneObject tmp_Obj=*itr;
			Objects.erase(itr);
			for(std::set<SceneObject>::iterator itr2=tmp.begin();itr2!=tmp.end();++itr2)
			{
				tmp_Obj.glue(*itr2);
				Objects.erase(*itr2);
			}
			Objects.insert(tmp_Obj);
			itr=Objects.begin();
			continue;
		}
		++itr;
	}
}


void Scene::gravity()
{
	if(Objects.empty()) return;
	std::set<SceneObject>::iterator itr=Objects.begin();
	std::set<SceneObject> falling_objects;
	do
	{
		falling_objects.clear(); // clears the set of falling objects
		itr=Objects.begin();
		while(itr!=Objects.end())
		{
			if(itr->hitsTheFloor())
			{
				itr++;
				continue;
			}
			bool can_fall=true;
			for(std::set<SceneObject>::iterator itr2=Objects.begin();itr2!=Objects.end();++itr2)
			{
				if(*itr2==*itr)
					continue;
				bool under=itr2->isUnder(*itr);
				if(under )
				{
					can_fall=false;
					break;
				}
			}
			if(can_fall)
			{
				falling_objects.insert(*itr);
			}
			itr++;
		}
		for(std::set<SceneObject>::iterator itr= falling_objects.begin();itr!=falling_objects.end();++itr)
		{
			SceneObject Obj=*itr;
			Objects.erase(*itr);
			Objects.insert(Obj.simple_fall() );
		}
	}while(falling_objects.size()!=0);
	simplify();
}

unsigned int Scene::deleteLines()
{
	unsigned int lignes_supprimees=0;
	for(int i=0;i<Size_x;++i)
	{
		std::set<SceneObject>::iterator itr=Objects.begin();
		while(itr!=Objects.end())
		{
			for(itr=Objects.begin();itr!=Objects.end();++itr)
			{
				std::tuple<std::set<SceneObject>,bool> result;
				result=itr->deleteLine(i);
				if(std::get<1>(result)==false)
					continue;
				// a present la ligne doit etre supprimee
				lignes_supprimees++;
				Objects.erase(itr);
				for(std::set<SceneObject>::iterator itr2=std::get<0>(result).begin();
					itr2!=std::get<0>(result).end();++itr2)
				{
					Objects.insert(*itr2);
				}
				itr=Objects.end();
				break;
			}
		}
	}
	simplify();
	return lignes_supprimees;
}

void Scene::doPhysics()
{
	if(!need_new_tetromino && !timer.isActive())
	{
		Tetromino tmp=CurrentObject.move(To_DOWN);
		// On verifie si l'objet ne sort pas de la scene
		bool need_new_tetromino_=false;
		if(tmp.hitsTheFloor2())
			need_new_tetromino_=true;
		// On boucle sur tout les objets pour verifier les collisions
		for(std::set<SceneObject>::iterator itr=Objects.begin();
			itr!=Objects.end() && need_new_tetromino_==false;++itr)
		{
			if(tmp.collide(*itr) )
			{
				need_new_tetromino_=true;
				break;
			}
		}
		if(need_new_tetromino_)
		{
			timer.start(850,this);
		}
		else
			CurrentObject=tmp;
	}
	gravity();
}


void Scene::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer.timerId()) {
		Tetromino tmp=CurrentObject.move(To_DOWN);
		// On verifie si l'objet ne sort pas de la scene
		bool need_new_tetromino_=false;
		if(tmp.hitsTheFloor2())
			need_new_tetromino_=true;
		// On boucle sur tout les objets pour verifier les collisions
		for(std::set<SceneObject>::iterator itr=Objects.begin();
			itr!=Objects.end() && need_new_tetromino_==false;++itr)
		{
			if(tmp.collide(*itr) )
			{
				need_new_tetromino_=true;
				break;
			}
		}
		if(need_new_tetromino_)
		{
			Objects.insert(CurrentObject);
			if(CurrentObject.hitsTheCeil() )
				gameOver=true;
			gravity();
			need_new_tetromino=true;
		}
		timer.stop();
	}
	else {
		QWidget::timerEvent(event);
	}
}

void Scene::new_Teromino(const TetrominoType& type,int rotation,int couleur)
{
	CurrentObject=Tetromino(type,rotation,couleur);
	need_new_tetromino=false;
}

void Scene::rotate()
{
	int i=0;
	Tetromino tmp[3];
	bool is_valid[3];
	tmp[0]=CurrentObject.rotate();
	tmp[1]=tmp[0].move(To_LEFT);
	tmp[2]=tmp[0].move(To_RIGHT);
	for(int j=0;j<3;j++)
		is_valid[j]=!(tmp[j].hitsTheWall() || tmp[j].hitsTheFloor2());

	// On verifie si l'objet ne sort pas de la scene
	i=0;
	if(!is_valid[0])
	{
		i=1;
		if(!is_valid[1])
		{
			i=2;
			if(!is_valid[2])
				return;
		}
	}
	// On boucle sur tout les objets pour verifier les collisions
	while(i<3)
	{
		if(is_valid[i])
		{
			for(std::set<SceneObject>::iterator itr=Objects.begin();itr!=Objects.end();++itr)
			{
				if(tmp[i].collide(*itr) )
				{
					is_valid[i]=false;
				}
			}
			if(is_valid[i])
				break;
		}
		i++;
	}
	if(i>2)
		return;
	CurrentObject=tmp[i];
}

void Scene::makeMove(const Movement& commande)
{
	Tetromino tmp=CurrentObject.move(commande);
	// On verifie si l'objet ne sort pas de la scene
	if(tmp.hitsTheWall() || tmp.hitsTheFloor2())
		return;
	// On boucle sur tout les objets pour verifier les collisions
	for(std::set<SceneObject>::iterator itr=Objects.begin();itr!=Objects.end();++itr)
	{
		if(tmp.collide(*itr) )
			return;
	}
	CurrentObject=tmp;
}
