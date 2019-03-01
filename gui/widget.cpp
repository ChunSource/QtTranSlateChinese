#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
widget::widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::widget)
{
	ui->setupUi(this);
	this->setWindowTitle("ChunSource");
	setWindowFlags(Qt::WindowStaysOnTopHint);
	connect(ui->ButtonScreen,&QPushButton::clicked,this,&widget::screen);
	connect(ui->ButtonDelete,&QPushButton::clicked,this,&widget::deleteImg);
	connect(ui->ButtonRestart,&QPushButton::clicked,this,&widget::reStart);
}

widget::~widget()
{
	delete ui;

}

void widget::deleteImg()
{
	qDebug()<<"delete";
	system("del \"d:/tran.jpg\"");
}

void widget::screen()
{
	qDebug()<<"screen";
	CaptureScreen* captureHelper = new CaptureScreen();
	connect(captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
	captureHelper->show();
}

void widget::showChin(QString mess)
{
	ui->label->setText(mess);
}

void widget::onCompleteCature(QPixmap f)
{
	ui->label->setPixmap(f);
	
	system("del \"d:/tran.jpg\"");
	
	f.save("d:/tran.jpg");
	qDebug()<<"onComp";
	QThread::msleep(100);
	Socket *s = new Socket();
	connect(s,&Socket::toTran,this,&widget::showChin);
	s->start();
	
}

void widget::reStart()
{
	QThread::msleep(100);
	Socket *s = new Socket();
	connect(s,&Socket::toTran,this,&widget::showChin);
	s->start();
}


