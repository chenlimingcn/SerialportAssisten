#ifndef SENDERSETWDG_H__
#define SENDERSETWDG_H__

#include <QCheckBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QGroupBox>

#include "SerialPortInfo.h"

// ��������
class CSenderSetWdg :
	public QGroupBox, public CSerialPortInfo
{
	Q_OBJECT
public:
	CSenderSetWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CSenderSetWdg();

Q_SIGNALS:
	void emitClearData();
	void emitSendByHex(bool flag);

protected:
	void init();
	void createWidgets();

protected Q_SLOTS:
	void sendData();
	void sendByHex(int state);

private:
	QCheckBox* m_sendByHexBox;
	QCheckBox* m_autoSendBox;
	QLineEdit* m_rateEdit;

	// ���������Ժ��Ϊ�����ļ�
	bool m_isSendByHex;
};

#endif // SENDERSETWDG_H__
