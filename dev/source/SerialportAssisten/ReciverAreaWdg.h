#ifndef RECIVERAREAWDG_H__
#define RECIVERAREAWDG_H__

#include <QGroupBox>
#include <QPlainTextEdit>

#include "SerialPortInfo.h"

// ����
class CReciverAreaWdg :
	public QGroupBox, CSerialPortInfo
{
	Q_OBJECT
public:
	CReciverAreaWdg(QSerialPort* serialport, QWidget * parent = 0);
	~CReciverAreaWdg();

	// ��ʾ��������
	void appendData(const QByteArray& arr);

	// �Ƿ�ʮ��������ʾ
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

	// ���������Ժ��Ϊ�����ļ�
	bool m_isAddTimeStamp;
	bool m_isShowByHex;
	bool m_isRecive;
};

#endif // RECIVERAREAWDG_H__
