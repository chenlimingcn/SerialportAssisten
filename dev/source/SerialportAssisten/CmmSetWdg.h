#ifndef CMMSETWDG_H__
#define CMMSETWDG_H__

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

#include "SerialPortInfo.h"

// 通信设置类
class CCmmSetWdg :
	public QGroupBox, public CSerialPortInfo
{
	Q_OBJECT
public:
	CCmmSetWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CCmmSetWdg();

protected:
	void  createWidgets();
	void init();

	void openPort();
	void closePort();

	void setWidgetEnble(bool flag= 0);

protected Q_SLOTS:
	void switchPort();
	void setPortName(const QString& name);
	void setData();

private:
	QComboBox* m_serialportBox;		// 串口选择
	QComboBox* m_baudrateBox;	// 波特率
	QComboBox* m_verifyBox;		// 校验位
	QComboBox* m_dataBitBox;		// 数据位
	QComboBox* m_stopBitBox;	// 停止位
	QLabel* m_switchLabel;		// 打开关闭串口
	QPushButton* m_switchBtn;	// 
	QLineEdit* m_saveMsgLocEdit;	// 保存报文位置 

};

#endif // CMMSETWDG_H__
