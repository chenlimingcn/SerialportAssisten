#include "SenderAreaWdg.h"

#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>

#include "ConverHex.h"
#include "common_str.h"

CSenderAreaWdg::CSenderAreaWdg(QSerialPort* serialport, QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("发送区"), parent), CSerialPortInfo(serialport)
{
	creatWidgets();
}


CSenderAreaWdg::~CSenderAreaWdg()
{
}

void CSenderAreaWdg::init()
{
	m_isSendByHex = false;
}

void CSenderAreaWdg::creatWidgets()
{
	m_plainText = new QPlainTextEdit(this);

	m_sendBtn = new QPushButton(Q_STR("发送"), this);
	connect(m_sendBtn, SIGNAL(clicked()), this, SLOT(send()));
	m_sendBtn->setDefault(true);
	m_sendBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
	m_sendBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Enter));

	QPushButton* cloeBtn = new QPushButton(Q_STR("关闭"), this);
	connect(cloeBtn, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->addWidget(cloeBtn);
	btnLayout->addWidget(m_sendBtn);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_plainText);
	mainLayout->addLayout(btnLayout);
	setLayout(mainLayout);

}

void CSenderAreaWdg::close()
{
	if (QMessageBox::Ok ==QMessageBox::question(this, Q_STR("提示"), Q_STR("确定退出？"),QMessageBox::Ok|QMessageBox::Cancel))
	{
		qApp->exit();
		return ;
	}
}

void CSenderAreaWdg::send()
{
	if (!m_serialport->isWritable())
	{
		QMessageBox::critical(this, Q_STR("错误"), Q_STR("串口未打开或者不可写"));
		return ;
	}

	QByteArray contents;
	if (m_isSendByHex)
	{
		contents = CConverHex::toHex(m_plainText->toPlainText());
	}
	else 
	{
		contents = m_plainText->toPlainText().toLocal8Bit();
	}
	m_serialport->write(contents);
	
}

void CSenderAreaWdg::slotClearData()
{
	m_plainText->clear();
}

void CSenderAreaWdg::slotSendByHex( bool flag )
{
	m_isSendByHex = flag;
}
