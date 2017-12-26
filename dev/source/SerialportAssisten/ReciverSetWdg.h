#ifndef RECIVERSETWDG_H__
#define RECIVERSETWDG_H__

#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>

#include "SerialPortInfo.h"
#include "Types.h"

// ��������
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
	QCheckBox* m_addTimeStampBox;	// ʱ���
	QCheckBox* m_showByHexBox;	// ��ʮ������

	QPushButton* m_reciveSwitchBtn;	// ��ʼ/ֹͣ���� 

	// ���������Ժ��Ϊ�����ļ�
	bool m_isAddTimeStamp;
	bool m_isShowByHex;
	bool m_isRecive;
};

#endif // RECIVERSETWDG_H__
