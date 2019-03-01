#include "capturescreen.h"
#include <QApplication>
#include "widget.h"
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QFile file;
	file.copy(":/baidu_dll.dll","./baidu_dll.dll");
	file.copy(":/libcrypto-1_1.dll","./libcrypto-1_1.dll");
	file.copy(":/libcurl.dll","./libcurl.dll");
	file.copy(":/libeay32.dll","./libeay32.dll");
	file.copy(":/ssleay32.dll","./ssleay32.dll");
	widget w;
	w.show();
	return a.exec();
}
