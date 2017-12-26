#include "SenderSetWdg.h"

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>

#include "common_str.h"

CSenderSetWdg::CSenderSetWdg(QSerialPort* serialport, QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("发送设置"), parent),CSerialPortInfo(serialport)
{
	createWidgets();
}


CSenderSetWdg::~CSenderSetWdg()
{
}

void CSenderSetWdg::init()
{
	m_isSendByHex = false;
}

void CSenderSetWdg::createWidgets()
{
	m_sendByHexBox = new QCheckBox(Q_STR("以十六进制发送"), this);
	connect(m_sendByHexBox, SIGNAL(stateChanged(int)), this, SLOT(sendByHex(int)));

	m_autoSendBox = new QCheckBox(Q_STR("自动发送"), this);
	m_rateEdit = new QLineEdit(this);

	QPushButton* clearBtn = new QPushButton(Q_STR("清空发送区"), this);
	connect(clearBtn, SIGNAL(clicked()), SIGNAL(emitClearData()));

	QHBoxLayout* formLayout = new QHBoxLayout;
	formLayout->addWidget(new QLabel(Q_STR("发送周期:"), this));
	formLayout->addWidget(m_rateEdit);

	QHBoxLayout* rateLayout = new QHBoxLayout;
	rateLayout->setMargin(0);
	rateLayout->addWidget(m_autoSendBox);
	rateLayout->addLayout(formLayout);

	QVBoxLayout* setLayouts = new QVBoxLayout;
	setLayouts->setMargin(0);
	setLayouts->addWidget(m_sendByHexBox);
	setLayouts->addLayout(rateLayout);
	setLayouts->addWidget(clearBtn);

	setLayout(setLayouts);
}

void CSenderSetWdg::sendData()
{
	QString content; // = m_plainText->toPlainText();
	if (m_sendByHexBox->isChecked())	// 十六进制发送
	{
		bool flag = false;
		char resule;
		QByteArray arr;
		foreach (QString hex, content.split(" "))
		{
			resule = hex.toInt(&flag, 16);
			if (!flag)
				return ;
			arr.append(resule);
		}
		m_serialport->write(arr);
		return ;
	}
	m_serialport->write(content.toLocal8Bit());
}

void CSenderSetWdg::sendByHex(int state)
{
	m_isSendByHex = (state==Qt::Checked);
	emitSendByHex(m_isSendByHex);
}