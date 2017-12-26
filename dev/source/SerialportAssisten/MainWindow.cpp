#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QGridLayout>
#include <QSplitter>
#include <QStatusBar>

#include "CmmSetWdg.h"
#include "ReciverAreaWdg.h"
#include "ReciverSetWdg.h"
#include "SenderAreaWdg.h"
#include "SenderSetWdg.h"

#include "common_str.h"

CMainWindow::CMainWindow(QWidget * parent/* = 0*/, Qt::WindowFlags flags/* = 0*/)
	: QMainWindow(parent,flags)
{
	init();
	createWdigets();
	resize(1000,800);
}


CMainWindow::~CMainWindow()
{
	clearData();
}

void CMainWindow::createWdigets()
{
	// 创建菜单
	QMenuBar* menuBar = new QMenuBar(this);
	setMenuBar(menuBar);

	QMenu* menu = menuBar->addMenu(QIcon(""), Q_STR("帮助(&H)"));
	menu->addAction(QIcon(""), Q_STR("关于(&A)"), this, SLOT(aboutApp()));
	menu->addAction(QIcon(""), Q_STR("关于Qt(&Q)"), this, SLOT(aboutQt()));

	// 通信设置
	m_cmmSetWdg = new CCmmSetWdg(m_serialport, this);

	// 接收设置
	m_reciverSetWdg = new CReciverSetWdg(m_serialport, this);
	setCentralWidget(m_reciverSetWdg);

	// 发送设置
	m_senderSetWdg = new CSenderSetWdg(m_serialport, this);

	// 接收区
	m_reciverAreaWdg = new CReciverAreaWdg(m_serialport, this);

	// 发送区
	m_senderAreaWdg = new CSenderAreaWdg(m_serialport, this);

	connect(m_reciverSetWdg, SIGNAL(emitAddTimeStamp(bool)), m_reciverAreaWdg, SLOT(slotAddTimeStamp(bool)));
	connect(m_reciverSetWdg, SIGNAL(emitShowByHex(bool)), m_reciverAreaWdg, SLOT(slotShowByHex(bool)));
	connect(m_reciverSetWdg, SIGNAL(emitRecive(bool)), m_reciverAreaWdg, SLOT(slotRecive(bool)));

	connect(m_reciverSetWdg, SIGNAL(emitSaveAs()), m_reciverAreaWdg, SLOT(slotSaveAs()));
	connect(m_reciverSetWdg, SIGNAL(emitClearData()), m_reciverAreaWdg, SLOT(slotClearData()));

	connect(m_senderSetWdg, SIGNAL(emitClearData()), m_senderAreaWdg, SLOT(slotClearData()));
	connect(m_senderSetWdg, SIGNAL(emitSendByHex(bool)), m_senderAreaWdg, SLOT(slotSendByHex(bool)));
	// 布局整个界面javascript:;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	QWidget* leftWdg = new QWidget(this);
	leftWdg->setFixedWidth(300);
	QSizePolicy policy = leftWdg->sizePolicy();
	policy.setHorizontalStretch(255);
	leftWdg->setSizePolicy(policy);
	leftWdg->setLayout(leftLayout);
	leftLayout->addWidget(m_cmmSetWdg);
	leftLayout->addWidget(m_reciverSetWdg);
	leftLayout->addWidget(m_senderSetWdg);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	QWidget* rightWdg = new QWidget(this);
	rightWdg->setLayout(rightLayout);
	rightLayout->addWidget(m_reciverAreaWdg);
	rightLayout->addWidget(m_senderAreaWdg);

	QSplitter* splitter = new QSplitter(this);
	splitter->addWidget(leftWdg);
	splitter->addWidget(rightWdg);
	setCentralWidget(splitter);
// 	QList<int> sizeList;
// 	sizeList << 100 << 300;
// 	splitter->setSizes(sizeList);

	// 状态栏
	m_statusBar = new CStatusBar(this);
	setStatusBar(m_statusBar);
}

void CMainWindow::init()
{
	m_serialport = new QSerialPort(this);
	connect(m_serialport, SIGNAL(error(QSerialPort::SerialPortError)), this,
		SLOT(handleError(QSerialPort::SerialPortError)));

	connect(m_serialport, SIGNAL(readyRead()), this, SLOT(readData()));

}

void CMainWindow::clearData()
{

}

void CMainWindow::closeEvent(QCloseEvent * event)
{
	if (QMessageBox::Ok ==QMessageBox::question(this, Q_STR("提示"), Q_STR("确定退出？"),QMessageBox::Ok|QMessageBox::Cancel))
	{
		event->accept();
		return ;
	}
	event->ignore();
}

void CMainWindow::handleError(QSerialPort::SerialPortError error)
{
	(void)error;
}

void CMainWindow::readData()
{
	QByteArray data;
	if (m_serialport->waitForReadyRead(500))	// 等待500ms，此时再不能读取数据，则超时
	{
		return ;
	}
	data = m_serialport->readAll();
	m_reciverAreaWdg->appendData(data);
}

void CMainWindow::close()
{
	if (QMessageBox::Ok ==QMessageBox::question(this, Q_STR("提示"), Q_STR("确定退出？"),QMessageBox::Ok|QMessageBox::Cancel))
	{
		qApp->exit();
	}
}

void CMainWindow::aboutApp()
{
	QMessageBox::about(this, Q_STR("关于"), Q_STR("版权所有"));
}

void CMainWindow::aboutQt()
{
	QMessageBox::aboutQt(this, Q_STR("关于Qt"));
}

