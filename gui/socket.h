#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QThread>
#include <windows.h>
#include <iostream>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;
class Socket : public QThread
{
	Q_OBJECT
public:
	explicit Socket(QObject *parent = nullptr);
	
signals:
	void toTran(QString mess);
public slots:
	void run();
	void finishedSlot(QNetworkReply *reply);
private:
	QNetworkAccessManager *manager;
	QString str;
	
	
};

#endif // SOCKET_H
