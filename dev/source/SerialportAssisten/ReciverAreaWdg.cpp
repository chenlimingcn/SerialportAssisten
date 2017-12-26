#include "ReciverAreaWdg.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

#include "ConverHex.h"
#include "common_str.h"

CReciverAreaWdg::CReciverAreaWdg(QSerialPort* serialport, QWidget * parent/* = 0*/)
	: QGroupBox( Q_STR("接收区"), parent),CSerialPortInfo(serialport)
{
	init();
	createWidgets();
}


CReciverAreaWdg::~CReciverAreaWdg()
{
}

void CReciverAreaWdg::appendData(const QByteArray& arr)
{
	if (false == m_isRecive)
		return ;

	if (true == m_isAddTimeStamp)
	{
		QDateTime dt = QDateTime::currentDateTime();
		m_plainText->appendPlainText(dt.toString("yyyy-MM-dd HH:mm:ss.zzz"));
	}

	QString txt;
	if (m_isShowByHex)
	{
		txt = CConverHex::toHexString(arr);
		m_plainText->appendPlainText(txt);
	}
	else
	{
		txt = arr;
		m_plainText->appendPlainText(txt);
	}
	m_plainText->appendPlainText("");
}

void CReciverAreaWdg::setShowByHex(bool flag /* = true */)
{
	m_isShowByHex = flag;
}

void CReciverAreaWdg::init()
{
	m_isAddTimeStamp = false;
	m_isShowByHex = false;
	m_isRecive = true;
}

void CReciverAreaWdg::createWidgets()
{
	m_plainText = new QPlainTextEdit(this);
	m_plainText->setReadOnly(true);
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_plainText);

	setLayout(mainLayout);
}

void CReciverAreaWdg::slotAddTimeStamp(bool flag)
{
	m_isAddTimeStamp = flag;
}

void CReciverAreaWdg::slotShowByHex(bool flag)
{
	m_isShowByHex = flag;
}

void CReciverAreaWdg::slotRecive(bool flag)
{
	m_isRecive = flag;
}

void CReciverAreaWdg::slotSaveAs()
{
	QString filename = QFileDialog::getSaveFileName(this, Q_STR("保存报文"), QDir::homePath(), Q_STR("报文文件(*.vsp);;文本文件(*.txt);;所有文件(*.*)"));
	if (filename.isEmpty())
		return ;

	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(this, Q_STR("错误"), Q_STR("保存文件出错，请确认位置是否存在\n以及是否有写权限。"));
		return ;
	}
	QTextStream out(&file);
	out << m_plainText->toPlainText();
	out.flush();

	file.close();
}

void CReciverAreaWdg::slotClearData()
{
	m_plainText->clear();
}
