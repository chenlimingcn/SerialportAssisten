#include "CmmSetWdg.h"

#include <QPixmap>
#include <QFormLayout>
#include <QMessageBox>
#include <QSerialPortInfo>

#include "common_str.h"

CCmmSetWdg::CCmmSetWdg(QSerialPort* serialport,QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("ͨ������"), parent),CSerialPortInfo(serialport)
{
	createWidgets();
	init();
}


CCmmSetWdg::~CCmmSetWdg()
{
}

void CCmmSetWdg::createWidgets()
{
	m_serialportBox = new QComboBox(this);
	m_serialportBox->setEditable(true);
	connect(m_serialportBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setPortName(const QString&)));

	m_baudrateBox = new QComboBox(this);
	m_baudrateBox->setEditable(true);
// 	connect(m_baudrateBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setData(const QString&)));

	m_verifyBox = new QComboBox(this);
// 	connect(m_verifyBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setData(const QString&)));

	m_dataBitBox = new QComboBox(this);
	m_dataBitBox->setEditable(true);
// 	connect(m_dataBitBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setData(const QString&)));

	m_stopBitBox = new QComboBox(this);
	m_stopBitBox->setEditable(true);
// 	connect(m_stopBitBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(setData(const QString&)));

	m_switchLabel = new QLabel(this);
	m_switchLabel->setPixmap(QPixmap(":/resources/icon/off.png"));
	m_switchBtn = new QPushButton(Q_STR("�򿪴���"),this);
	m_switchLabel->setBuddy(m_switchBtn);
	connect(m_switchBtn, SIGNAL(clicked()), this, SLOT(switchPort()));

	QHBoxLayout* switchLayout = new QHBoxLayout;
	switchLayout->setMargin(0);
	switchLayout->addWidget(m_switchLabel);
	switchLayout->addWidget(m_switchBtn);

	// ����
	QFormLayout* layout = new QFormLayout;
	layout->setMargin(0);
	layout->addRow(Q_STR("����"), m_serialportBox);
	layout->addRow(Q_STR("������"), m_baudrateBox);
	layout->addRow(Q_STR("��żУ��"), m_verifyBox);
	layout->addRow(Q_STR("����λ"), m_dataBitBox);
	layout->addRow(Q_STR("ֹͣλ"), m_stopBitBox);
	layout->addRow(switchLayout);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setMargin(0);
	mainLayout->addLayout(layout);

	setLayout(mainLayout);

}

void CCmmSetWdg::init()
{
	// ��ѯϵͳ���п�ʹ�ö˿�
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	foreach (QSerialPortInfo portInfo, ports)
	{
		m_serialportBox->addItem(portInfo.portName());
	}
	if (ports.count() > 0)
		m_serialportBox->setCurrentIndex(0);

	// ��ѡ������
	QStringList baudrateList;
	baudrateList << "300"
		<< "600" 
		<< "1200"
		<< "2400"
		<< "3600"
		<< "4800"
		<< "9600"
		<< "19200"
		<< "38400"
		<< "43000"
		<< "56000"
		<< "57600"
		<< "115200";
	m_baudrateBox->addItems(baudrateList);
	m_baudrateBox->setCurrentText("9600");

	// У��
	QStringList verifyList;
	verifyList << Q_STR("��")
		<< Q_STR("��У��")
		<< Q_STR("żУ��")
		<< Q_STR("�ո�У��")
		<< Q_STR("��־У��")
		<< Q_STR("����");
	m_verifyBox->addItems(verifyList);
	m_verifyBox->setCurrentIndex(0);

	// ����λ
	QStringList dataBitList;
	dataBitList << "8"
		<< "7"
		<< "6"
		<< "5";
	m_dataBitBox->addItems(dataBitList);
	m_dataBitBox->setCurrentIndex(0);

	// ֹͣλ
	QStringList stopBitList;
	stopBitList << Q_STR("1λ")
		<< Q_STR("1.5λ")
		<< Q_STR("2λ");
	m_stopBitBox->addItems(stopBitList);
	m_stopBitBox->setCurrentIndex(0);
}

void CCmmSetWdg::switchPort()
{
	if (NULL == m_serialport)
		return ;
	
	bool flag = m_serialport->isOpen();
	if (!flag)
	{
		openPort();
	}
	else
	{
		closePort();
	}
}

void CCmmSetWdg::setPortName(const QString& name)
{
	if (NULL == m_serialport)
		return ;

	m_serialport->setPortName(name);
}

void CCmmSetWdg::setWidgetEnble(bool flag/*=true*/)
{
	m_serialportBox->setEnabled(flag);
	m_baudrateBox->setEnabled(flag);
	m_verifyBox->setEnabled(flag);
	m_dataBitBox->setEnabled(flag);
	m_stopBitBox->setEnabled(flag);
}

void CCmmSetWdg::setData()
{
	if (NULL == m_serialport)
		return ;
	
	QString val;

	// У����������
	val = m_verifyBox->currentText();
	if (val == Q_STR("��"))
		m_serialport->setParity(QSerialPort::NoParity);
	else if (val == Q_STR("��У��"))
		m_serialport->setParity(QSerialPort::OddParity);
	else if (val == Q_STR("żУ��"))
		m_serialport->setParity(QSerialPort::EvenParity);
	else if (val == Q_STR("�ո�У��"))
		m_serialport->setParity(QSerialPort::SpaceParity);
	else if (val == Q_STR("��־У��"))
		m_serialport->setParity(QSerialPort::MarkParity);
	else
		m_serialport->setParity(QSerialPort::UnknownParity);

	// ֹͣλ
	val = m_stopBitBox->currentText();
	if (val == Q_STR("1λ"))
		m_serialport->setStopBits(QSerialPort::OneStop);
	else if (val == Q_STR("1.5λ"))
		m_serialport->setStopBits(QSerialPort::OneAndHalfStop);
	else if (val == Q_STR("2λ"))
		m_serialport->setStopBits(QSerialPort::TwoStop);
	else
		m_serialport->setStopBits(QSerialPort::UnknownStopBits);

	// ����������
	val = m_baudrateBox->currentText();
	bool suc = false;
	qint32 value = val.toInt(&suc);
	if (!suc)
		return ;

	m_serialport->setBaudRate(value);
	
	// ����λ����
	val = m_dataBitBox->currentText();
	suc = false;
	value = val.toInt(&suc);
	if (!suc)
		return ;

	QSerialPort::DataBits databit = QSerialPort::UnknownDataBits;
	switch (value)
	{
	case 8:
		databit = QSerialPort::Data8;
		break;
	case 7:
		databit = QSerialPort::Data7;
		break;
	case 6:
		databit = QSerialPort::Data6;
		break;
	case 5:
		databit = QSerialPort::Data5;
		break;
	default:
		break;
	}
	m_serialport->setDataBits(databit);	
}

void CCmmSetWdg::openPort()
{
	if (m_serialport->isOpen())
		return ;

	if (!m_serialport->open(QIODevice::ReadWrite))
	{
		m_serialport->close();
		QMessageBox::critical(this, tr("Error"), m_serialport->errorString());
		return ;
	}
	setWidgetEnble();
	setData();
	m_switchLabel->setPixmap(QPixmap(":/resources/icon/on.png"));
	m_switchBtn->setText(Q_STR("�رմ���"));

}

void CCmmSetWdg::closePort()
{
	if (m_serialport->isOpen())
	{
		setWidgetEnble(true);
		m_serialport->close();
		m_switchLabel->setPixmap(QPixmap(":/resources/icon/off.png"));
		m_switchBtn->setText(Q_STR("�򿪴���"));
	}

}
