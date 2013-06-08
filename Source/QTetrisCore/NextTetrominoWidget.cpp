#include "NextTetrominoWidget.h"

NextTetrominoWidget::NextTetrominoWidget(QWidget *parent) :
	QGraphicsView(parent),
	scene(new QGraphicsScene(0, 0, 160, 160))
{
	setFixedSize(180,180);
	setScene(scene);
}


NextTetrominoWidget::~NextTetrominoWidget()
{
}

void NextTetrominoWidget::display(int type, int rotationPosition,int couleur)
{
	scene->clear();
	extern int tetrominoDatabase[7][4][5][5];
	QBrush brush;

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;++j)
			if(tetrominoDatabase[type][rotationPosition][i][j]==1)
			{
				brush=renderCube(colorTab[couleur],30*i,30*j);
				scene->addRect(j*30,i*30,30,30,QPen(QColor(0,0,0)),brush);
			}
	}
	update();
}
