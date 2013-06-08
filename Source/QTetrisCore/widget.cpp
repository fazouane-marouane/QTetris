#include "widget.h"

widget::widget(QWidget *parent) :
	QGraphicsView(parent),
	scene(new QGraphicsScene(0, 0, 30*Size_y+1, 30*Size_x+1))
{
	G=NULL;
	bool_gameover=false;
	setFixedSize(30*Size_y+1,30*Size_x+1);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	scale(qreal(0.8), qreal(0.8));
}

void widget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == timer.timerId()) {
		if(G==NULL || G->isGameOver())
		{	// Game Over
			timer.stop();
			scene->clear();
			QPainterPath painter;
			QFont font;
			font.setBold(true);
			font.setPointSize(30);
			painter.addText(20, 50, font,  "Game Over!!");
			scene->addPath(painter,QPen(Qt::black));
			update();
			emit gameOver();
			return;
		}
		static QString s;
		QString tmp=G->Show();

		if(tmp!=s)
		{	// si la scene a change on dessine les nouvelles positions
			scene->clear();
			for(int i=0;i<Size_x;i++)
			{
				int u=(i<Size_x/2?0:1);
				for(int j=0;j<Size_y/2;++j)
					if(tmp[i*Size_y+j]!=' ')
					{
						QBrush brush=renderCube(tmp.at(i*Size_y+j),i*30+u,30*j);
						scene->addRect(j*30,i*30+u,30,30,QPen(QColor(0,0,0)),brush);
					}
				for(int j=Size_y/2;j<Size_y;++j)
					if(tmp[i*Size_y+j]!=' ')
					{
						QBrush brush=renderCube(tmp.at(i*Size_y+j),i*30+u,30*j+1);
						scene->addRect(j*30+1,i*30+u,30,30,QPen(QColor(0,0,0)),brush);
					}
			}
			s=tmp;
		}
		if(tmp=="Game Over")
		{
			bool_gameover=true;
		}
		update();
	} else {
		QWidget::timerEvent(event);
	}
}

widget::~widget()
{
}

void widget::resizeEvent(QResizeEvent * event)
{
	scene->setSceneRect( QRect(QPoint(0, 0), size()) );
	fitInView(sceneRect());
}

void widget::keyPressEvent(QKeyEvent *ev)
{
	if(timer.isActive())
	{
		// passer les evenements au parent
		switch(ev->key())
		{
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
		case Qt::Key_Left:
		case Qt::Key_PageUp:
		case Qt::Key_PageDown:
			break;
		default:
			QWidget::keyPressEvent(ev);
		}
		// passer les evenements au GameManager
		if(G!=NULL)
			G->keyPressEvent(ev);
	}
	else
		QWidget::keyPressEvent(ev);
}


void widget::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);
	// Shadow
	QRectF sceneRect = this->sceneRect();
	QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
	QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
	if (rightShadow.intersects(rect) || rightShadow.contains(rect))
		painter->fillRect(rightShadow, Qt::darkGray);
	if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
		painter->fillRect(bottomShadow, Qt::darkGray);

	// Fill
	QRadialGradient gradient(100,100,20);//(sceneRect.topLeft(), sceneRect.bottomRight());
	gradient.setSpread(QGradient::ReflectSpread);
	gradient.setColorAt(0, Qt::gray);
	gradient.setColorAt(0.5, QColor(Qt::gray).darker(40));
	gradient.setColorAt(0.41, QColor(Qt::gray).darker(50));
	gradient.setColorAt(1, QColor(Qt::gray).darker(80));
	gradient.setSpread(QGradient::ReflectSpread);
	painter->fillRect(rect.intersected(sceneRect), gradient);
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(sceneRect);
}


void widget::pause()
{
	if(timer.isActive())
	{
		timer.stop();
		G->pause();
	}
	else
	{
		timer.start(10,this);
		G->pause();
	}
}

