#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QTranslator>

#include <iostream>
using namespace std;

#include "common_str.h"
#include "MainWindow.h"
#include "SenderSetWdg.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QApplication::addLibraryPath(QDir::current().absolutePath()+QDir::separator()+"plugins");
	QApplication::addLibraryPath(QDir::current().absolutePath()+QDir::separator()+"plugins"+QDir::separator()+"platforms");
	cout << QString(QDir::current().absolutePath()+QDir::separator()+"plugins").toStdString() << endl;

	// �������
	int id = QFontDatabase::addApplicationFont("../data/msyh.ttf");
	if (id >= 0)
	{
		QStringList yh = QFontDatabase::applicationFontFamilies(id);
		app.setFont(QFont(yh.first(), 10));
	} 
	else 
	{
		app.setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 9));
	}
	app.setWindowIcon(QIcon(":/resources/icon/SerialportAssisten.png"));



	// ����
	QTranslator translator;
	if (translator.load("../data/translate/qt_zh_CN.qm"))
		app.installTranslator(&translator);

	// ��ʽ����
// 	QFile file("../data/stype/stype.qss");
// 	if (!file.open(QIODevice::ReadOnly))
// 	{
// 		QMessageBox::critical(NULL, Q_STR("����"), Q_STR("����stype.qss����"));
// 		return 0;
// 	}
// 	QString stypes = file.readAll();
// 	qApp->setStyleSheet(stypes);

	CMainWindow win;
	win.show();
// 	CSenderSetWdg sdg(NULL);
// 	sdg.show();
	return app.exec();
}