#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDir>
#include "socket.h"
#include "capturescreen.h"
namespace Ui {
	class widget;
}

class widget : public QWidget
{
	Q_OBJECT
	
public:
	explicit widget(QWidget *parent = 0);
	~widget();
	
private:
	Ui::widget *ui;
	void deleteImg();
	void screen();
	QDir dir;
private slots:
	void showChin(QString mess);
	void onCompleteCature(QPixmap f);
	void reStart();
};

#endif // WIDGET_H
