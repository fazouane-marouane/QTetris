#include "Login.h"
#include "ui_Login.h"
#include <QMessageBox>
#include <QSignalMapper>
#include "../MenuManager/menumanager.h"

Login::Login(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Login)
{
	ui->setupUi(this);
	ui->loginBtn->setDefault(true);
	QSignalMapper *m = new QSignalMapper(this);
	connect(this, SIGNAL(logged()),m, SLOT(map()));
	m->setMapping(this, "QTetris");
	connect(m, SIGNAL(mapped(QString)), MenuManager::menuInstance, SLOT(showMenu(QString)));
}

Login::~Login()
{
	delete ui;
}

QString Login::getUserName()
{
	return userNameString;
}

void Login::on_loginBtn_clicked()
{
	if(ui->userLineEdit->text()!=tr(""))
	{
		userNameString=ui->userLineEdit->text();
		emit logged();
		emit userNameChanged(userNameString);
	}
	else
		QMessageBox::warning(this,tr("Warning"),tr("Lack user name!"),QMessageBox::Yes);
}
