#ifndef Login_H
#define Login_H

#include <QDialog>
#include <QtWidgets>
#include <QString>

namespace Ui
{
	class Login;
}

class Login : public QDialog
{
	Q_OBJECT

public:
	explicit Login(QWidget *parent = 0);
	~Login();
	QString getUserName();

signals:
	void logged();
	void userNameChanged(QString);

public slots:
	void on_loginBtn_clicked();

public:
	Ui::Login *ui;
private:
	QString userNameString;
};

#endif // Login_H
