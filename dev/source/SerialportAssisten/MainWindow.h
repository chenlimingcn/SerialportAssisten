#ifndef MAINWINDOW_H__
#define MAINWINDOW_H__

#include <QMainWindow>

#include <QSerialPort>

#include "StatusBar.h"

class CCmmSetWdg;
class CReciverSetWdg;
class CSenderSetWdg;
class CReciverAreaWdg;
class CSenderAreaWdg;

class CMainWindow :
	public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
	~CMainWindow();

protected:
	void createWdigets();
	void init();
	void clearData();

	virtual void closeEvent(QCloseEvent * event);

protected Q_SLOTS:
	void handleError(QSerialPort::SerialPortError error);
	void readData();
	void close();

	void aboutApp();
	void aboutQt();

private:
	CCmmSetWdg* m_cmmSetWdg;
	CReciverSetWdg* m_reciverSetWdg;
	CSenderSetWdg* m_senderSetWdg;
	CReciverAreaWdg* m_reciverAreaWdg;
	CSenderAreaWdg* m_senderAreaWdg;
	CStatusBar* m_statusBar;	// 状态栏控件
	
private:
	QSerialPort* m_serialport;	// 串口信息
};

#endif // MAINWINDOW_H__
