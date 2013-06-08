#ifndef HIGHSCORES_H
#define HIGHSCORES_H

// std
#include <string>
#include <iostream>
#include <sstream>
//	 Qt
#include <QWidget>
#include <QtSql>


namespace Ui
{
	class HighScores;
}

class HighScores : public QWidget
{
	Q_OBJECT

public:
	HighScores(QWidget *parent = 0);
	~HighScores();

public slots:
	void highScoresPerMatch();
	void highTotalScorePerUser();
	void clearHighScores();
	void updateUserName(QString);
	void addScore(int score);

private:
	Ui::HighScores *ui;
	QString userName;
	int score;
	QSqlDatabase dataBaseHighScores;
};

#endif // HIGHSCORES_H
