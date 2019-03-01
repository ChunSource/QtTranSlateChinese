#include "socket.h"
#include <qDebug>
Socket::Socket(QObject *parent) : QThread(parent)
{
	
}

void Socket::run()
{
	this->manager = new QNetworkAccessManager();
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
	typedef char* (*pAdd)();
	HMODULE hDLL = LoadLibraryA("baidu_dll.dll"); //加载dll文件 
	pAdd fp1 = pAdd(GetProcAddress(hDLL, "tran")); //得到dll中的第一个函数
	char* buff = fp1();
	FreeLibrary(hDLL);
	qDebug()<<"buff:"<<buff;
	QString send = QString(buff);
	
	
	//	delete[] buff;
	//	buff = NULL;
	
	//JSON处理方式
	
	QJsonDocument documentObject=QJsonDocument::fromJson(send.toLatin1());
	QJsonObject object = documentObject.object();
	
	QString buffer;
	QJsonDocument document=QJsonDocument(object.take("words_result").toArray()); 
	QJsonArray json = document.array();
	
	qDebug()<<"array size"<<json.size();
	for(int i=0;i<json.size();i++)
		{
			QJsonObject root = json.at(0).toObject();
			buffer = root.value("words").toString() + " ";
		}
	
	QNetworkRequest request;
	request.setUrl(QUrl("http://fanyi.youdao.com/translate?&doctype=json&type=AUTO&i="+buffer));
	
	manager->get(request);
	this->exec();
}

void Socket::finishedSlot(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = reply->readAll();
			QString string = QString::fromUtf8(bytes);
			qDebug()<<"string: "<<string;

			string.replace("[[","[");
			string.replace("]]","]");
			
			QJsonDocument document = QJsonDocument::fromJson(string.toUtf8());
			QJsonObject object = document.object();
			
			QJsonArray json = object.take("translateResult").toArray();
			QString result;
			for(int i=0;i<json.size();i++)
				{
					result += " ";
					result += json.at(i).toObject().take("tgt").toString();
					qDebug()<<"tgt:"<<json.at(i).toObject().take("tgt").toString();
				}
			emit toTran(result);
			manager->deleteLater();
			this->exit(0);
		}
	else
		{
			qDebug()<<"handle errors here";
			QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			//statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
			qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
			qDebug(qPrintable(reply->errorString()));
		}
	reply->deleteLater();
	this->exit(0);
}
