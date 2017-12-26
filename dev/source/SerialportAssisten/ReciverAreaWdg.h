#ifndef RECIVERAREAWDG_H__
#define RECIVERAREAWDG_H__

#include <QGroupBox>
#include <QPlainTextEdit>

#include "SerialPortInfo.h"

// 接收
class CReciverAreaWdg :
	public QGroupBox, CSerialPortInfo
{
	Q_OBJECT
public:
	CReciverAreaWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CReciverAreaWdg();

	// 显示接收数据
	void appendData(const QByteArray& arr);

	// 是否十六进制显示
	void setShowByHex(bool flag = true);

protected:
	void init();
	void createWidgets();

public Q_SLOTS:
	void slotAddTimeStamp(bool flag);
	void slotShowByHex(bool flag);
	void slotRecive(bool flag);

	void slotSaveAs();
	void slotClearData();

private:
	QPlainTextEdit* m_plainText;

	// 数据区，以后改为配置文件
	bool m_isAddTimeStamp;
	bool m_isShowByHex;
	bool m_isRecive;
};

#endif // RECIVERAREAWDG_H__
