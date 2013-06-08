#ifndef XmlParser_H
#define XmlParser_H

// Qt
#include <QWidget>
#include <QtXml>

class XmlParser : public QWidget
{
	Q_OBJECT

public:
	XmlParser(QWidget *parent = 0);
	~XmlParser();
	void constructMenu(QDomNode n,const QString& s);
	void constructMediaPlayer(QDomNode n);
	bool parse();

};

#endif	// XmlParser_H
