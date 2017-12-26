#include "CmmSetWdg.h"

#include <QPixmap>
#include <QFormLayout>
#include <QMessageBox>
#include <QSerialPortInfo>

#include "common_str.h"

CCmmSetWdg::CCmmSetWdg(QSerialPort* serialport,QWidget * parent/* = 0*/)
	: QGroupBox(Q_STR("通信设置"), parent),CSerialPortInfo(serialport)
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
	m_switchBtn = new QPushButton(Q_STR("打开串口"),this);
	m_switchLabel->setBuddy(m_switchBtn);
	connect(m_switchBtn, SIGNAL(clicked()), this, SLOT(switchPort()));

	QHBoxLayout* switchLayout = new QHBoxLayout;
	switchLayout->setMargin(0);
	switchLayout->addWidget(m_switchLabel);
	switchLayout->addWidget(m_switchBtn);

	// 布局
	QFormLayout* layout = new QFormLayout;
	layout->setMargin(0);
	layout->addRow(Q_STR("串口"), m_serialportBox);
	layout->addRow(Q_STR("波特率"), m_baudrateBox);
	layout->addRow(Q_STR("奇偶校验"), m_verifyBox);
	layout->addRow(Q_STR("数据位"), m_dataBitBox);
	layout->addRow(Q_STR("停止位"), m_stopBitBox);
	layout->addRow(switchLayout);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setMargin(0);
	mainLayout->addLayout(layout);

	setLayout(mainLayout);

}

void CCmmSetWdg::init()
{
	// 查询系统所有可使用端口
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	foreach (QSerialPortInfo portInfo, ports)
	{
		m_serialportBox->addItem(portInfo.portName());
	}
	if (ports.count() > 0)
		m_serialportBox->setCurrentIndex(0);

	// 可选波特率
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

	// 校验
	QStringList verifyList;
	verifyList << Q_STR("无")
		<< Q_STR("奇校验")
		<< Q_STR("偶校验")
		<< Q_STR("空格校验")
		<< Q_STR("标志校验")
		<< Q_STR("其它");
	m_verifyBox->addItems(verifyList);
	m_verifyBox->setCurrentIndex(0);

	// 数据位
	QStringList dataBitList;
	dataBitList << "8"
		<< "7"
		<< "6"
		<< "5";
	m_dataBitBox->addItems(dataBitList);
	m_dataBitBox->setCurrentIndex(0);

	// 停止位
	QStringList stopBitList;
	stopBitList << Q_STR("1位")
		<< Q_STR("1.5位")
		<< Q_STR("2位");
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

	// 校验数据设置
	val = m_verifyBox->currentText();
	if (val == Q_STR("无"))
		m_serialport->setParity(QSerialPort::NoParity);
	else if (val == Q_STR("奇校验"))
		m_serialport->setParity(QSerialPort::OddParity);
	else if (val == Q_STR("偶校验"))
		m_serialport->setParity(QSerialPort::EvenParity);
	else if (val == Q_STR("空格校验"))
		m_serialport->setParity(QSerialPort::SpaceParity);
	else if (val == Q_STR("标志校验"))
		m_serialport->setParity(QSerialPort::MarkParity);
	else
		m_serialport->setParity(QSerialPort::UnknownParity);

	// 停止位
	val = m_stopBitBox->currentText();
	if (val == Q_STR("1位"))
		m_serialport->setStopBits(QSerialPort::OneStop);
	else if (val == Q_STR("1.5位"))
		m_serialport->setStopBits(QSerialPort::OneAndHalfStop);
	else if (val == Q_STR("2位"))
		m_serialport->setStopBits(QSerialPort::TwoStop);
	else
		m_serialport->setStopBits(QSerialPort::UnknownStopBits);

	// 波特率设置
	val = m_baudrateBox->currentText();
	bool suc = false;
	qint32 value = val.toInt(&suc);
	if (!suc)
		return ;

	m_serialport->setBaudRate(value);
	
	// 数据位设置
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
	m_switchBtn->setText(Q_STR("关闭串口"));

}

void CCmmSetWdg::closePort()
{
	if (m_serialport->isOpen())
	{
		setWidgetEnble(true);
		m_serialport->close();
		m_switchLabel->setPixmap(QPixmap(":/resources/icon/off.png"));
		m_switchBtn->setText(Q_STR("打开串口"));
	}

}
