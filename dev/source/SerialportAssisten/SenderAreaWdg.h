#ifndef SENDERAREAWDG_H__
#define SENDERAREAWDG_H__

#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>

#include "SerialPortInfo.h"

class CSenderAreaWdg :
	public QGroupBox, public CSerialPortInfo
{
	Q_OBJECT
public:
	CSenderAreaWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CSenderAreaWdg();

protected:
	void init();
	void creatWidgets();

protected Q_SLOTS:
	void close();
	void send();
	void slotClearData();
	void slotSendByHex(bool flag);

private:
	QPlainTextEdit* m_plainText;
	QPushButton* m_sendBtn;

	// 数据区，以后改为配置文件
	bool m_isSendByHex;
};

#endif // SENDERAREAWDG_H__
