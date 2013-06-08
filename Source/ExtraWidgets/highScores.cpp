#include "highScores.h"
#include "ui_highscores.h"

HighScores::HighScores(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::HighScores)

{
	ui->setupUi(this);
	dataBaseHighScores = QSqlDatabase::addDatabase("QSQLITE");
	dataBaseHighScores.setDatabaseName("highScores.db");
	dataBaseHighScores.open();
	QSqlQuery query;
	query.exec("CREATE TABLE matches("
			   "id int Constraint PK_MATCH PRIMARY KEY,"
			   "username char(50),"
			   "score int)");

	userName="NULL";
	score=-1;
	highScoresPerMatch();
	setFixedWidth(300);
	setFixedHeight(400);
	connect(ui->highScoresPerMatchBtn, SIGNAL(clicked()), this,SLOT(highScoresPerMatch()));
	connect(ui->highTotalScorePerUserBtn, SIGNAL(clicked()), this,SLOT(highTotalScorePerUser()));
	connect(ui->clearHighScoresBtn, SIGNAL(clicked()), this,SLOT(clearHighScores()));
}

HighScores::~HighScores()
{
	delete ui;
}

void HighScores::addScore(int score_)
{
	score=score_;
	QSqlQuery query;
	std::ostringstream oss;
	oss<<"insert into matches values((select count(*) from matches)+1,'"
	  <<userName.toStdString()<<"',"<<score<<")";
	query.exec( oss.str().c_str());
	highScoresPerMatch();
}

void HighScores::highScoresPerMatch()
{

	static QSqlQueryModel *model = new QSqlQueryModel(ui->highScoresTableView);
	model->setQuery(QString("select username,score from matches order by score desc limit 10"));
	ui->highScoresTableView->setModel(model);
}

void HighScores::highTotalScorePerUser()
{
	static QSqlQueryModel *model = new QSqlQueryModel(ui->highScoresTableView);
	model->setQuery(QString("select username,sum(score) from matches group by username order by sum(score) desc limit 10"));
	ui->highScoresTableView->setModel(model);
}

void HighScores::clearHighScores()
{
	QSqlQuery query;
	query.exec("delete from matches");
	highScoresPerMatch();
}

void HighScores::updateUserName(QString userName_)
{
	userName=userName_;
}
