#include "ReciverSetWdg.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "common_str.h"

CReciverSetWdg::CReciverSetWdg(QSerialPort* serialport, QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("��������"), parent), CSerialPortInfo(serialport)
{
	createWidgets();
}


CReciverSetWdg::~CReciverSetWdg()
{
}

void CReciverSetWdg::init()
{
	m_isAddTimeStamp = false;
	m_isShowByHex = false;
	m_isRecive = true;
}

void CReciverSetWdg::createWidgets()
{
	m_addTimeStampBox = new QCheckBox(Q_STR("����ʱ���"), this);
	connect(m_addTimeStampBox, SIGNAL(stateChanged(int)), this, SLOT(slotAddTimeStamp(int)));
	m_showByHexBox = new QCheckBox(Q_STR("��ʮ��������ʾ"), this);
	connect(m_showByHexBox, SIGNAL(stateChanged(int)), this, SLOT(slotShowByHex(int)));
	QPushButton* saveAsBtn = new QPushButton(Q_STR("���Ϊ..."), this);
	connect(saveAsBtn, SIGNAL(clicked()), this, SIGNAL(emitSaveAs()));
	QPushButton* clearBtn = new QPushButton(Q_STR("��ս�����"), this);
	connect(clearBtn, SIGNAL(clicked()), this, SIGNAL(emitClearData()));
	m_reciveSwitchBtn = new QPushButton(Q_STR("��ͣ����"), this);
	connect(m_reciveSwitchBtn, SIGNAL(clicked()), this, SLOT(slotRecive()));
	QHBoxLayout* btnLayout = new QHBoxLayout;
	btnLayout->addWidget(saveAsBtn);
	btnLayout->addWidget(clearBtn);
	btnLayout->addWidget(m_reciveSwitchBtn);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_addTimeStampBox);
	mainLayout->addWidget(m_showByHexBox);
// 	mainLayout->addWidget(m_autoEndlBox);
	mainLayout->addLayout(btnLayout);
	setLayout(mainLayout);
}

void CReciverSetWdg::slotAddTimeStamp(int state)
{
	if (state == Qt::Checked)
		m_isAddTimeStamp = true;
	else
		m_isAddTimeStamp = false;
	emitAddTimeStamp(m_isAddTimeStamp);
}

void CReciverSetWdg::slotShowByHex(int state)
{
	m_isShowByHex = (state == Qt::Checked);
	
	emitShowByHex(m_isShowByHex);
}

void CReciverSetWdg::slotRecive()
{
	m_isRecive = !m_isRecive;
	emitRecive(m_isRecive);
	if (false == m_isRecive)
	{
		m_reciveSwitchBtn->setText(Q_STR("��������"));
	}
	else
	{
		m_reciveSwitchBtn->setText(Q_STR("��ͣ����"));
	}
}