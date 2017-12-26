#include "SenderAreaWdg.h"

#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>

#include "ConverHex.h"
#include "common_str.h"

CSenderAreaWdg::CSenderAreaWdg(QSerialPort* serialport, QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("������"), parent), CSerialPortInfo(serialport)
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

	m_sendBtn = new QPushButton(Q_STR("����"), this);
	connect(m_sendBtn, SIGNAL(clicked()), this, SLOT(send()));
	m_sendBtn->setDefault(true);
	m_sendBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
	m_sendBtn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Enter));

	QPushButton* cloeBtn = new QPushButton(Q_STR("�ر�"), this);
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
	if (QMessageBox::Ok ==QMessageBox::question(this, Q_STR("��ʾ"), Q_STR("ȷ���˳���"),QMessageBox::Ok|QMessageBox::Cancel))
	{
		qApp->exit();
		return ;
	}
}

void CSenderAreaWdg::send()
{
	if (!m_serialport->isWritable())
	{
		QMessageBox::critical(this, Q_STR("����"), Q_STR("����δ�򿪻��߲���д"));
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
