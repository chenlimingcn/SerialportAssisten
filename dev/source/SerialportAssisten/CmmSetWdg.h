#ifndef CMMSETWDG_H__
#define CMMSETWDG_H__

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

#include "SerialPortInfo.h"

// ͨ��������
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
	QComboBox* m_serialportBox;		// ����ѡ��
	QComboBox* m_baudrateBox;	// ������
	QComboBox* m_verifyBox;		// У��λ
	QComboBox* m_dataBitBox;		// ����λ
	QComboBox* m_stopBitBox;	// ֹͣλ
	QLabel* m_switchLabel;		// �򿪹رմ���
	QPushButton* m_switchBtn;	// 
	QLineEdit* m_saveMsgLocEdit;	// ���汨��λ�� 

};

#endif // CMMSETWDG_H__
