#ifndef RECIVERSETWDG_H__
#define RECIVERSETWDG_H__

#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>

#include "SerialPortInfo.h"
#include "Types.h"

// 接收设置
class CReciverSetWdg :
	public QGroupBox, public CSerialPortInfo
{
	Q_OBJECT
public:
	CReciverSetWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CReciverSetWdg();

protected:
	void init();
	void createWidgets();

Q_SIGNALS:
	void emitAddTimeStamp(bool flag);
	void emitShowByHex(bool flag);
	void emitRecive(bool flag);

	void emitSaveAs();
	void emitClearData();

protected Q_SLOTS:
	void slotAddTimeStamp(int state);
	void slotShowByHex(int state);
	void slotRecive();

private:
	QCheckBox* m_addTimeStampBox;	// 时间戳
	QCheckBox* m_showByHexBox;	// 以十六进制

	QPushButton* m_reciveSwitchBtn;	// 开始/停止接收 

	// 数据区，以后改为配置文件
	bool m_isAddTimeStamp;
	bool m_isShowByHex;
	bool m_isRecive;
};

#endif // RECIVERSETWDG_H__
