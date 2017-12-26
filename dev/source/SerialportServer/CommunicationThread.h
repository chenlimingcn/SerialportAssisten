#ifndef COMMUNICATIONTHREAD_H__
#define COMMUNICATIONTHREAD_H__

#include <QThread>
#include <QSerialPort>

class CCommunication;
class CSerialportServerDoc;

class CCommunicationThread :
	public QThread
{
	Q_OBJECT
public:
	CCommunicationThread(const QString& portname, CSerialportServerDoc* doc, QObject* parent = 0);
	~CCommunicationThread();

	bool init();

protected:
	virtual void run();

private:
	CCommunication* m_cmm;
	QSerialPort* m_serialport;
	QString m_portname;
	CSerialportServerDoc* m_doc;

	QByteArray* m_buffArray;	// Í¨ÐÅbuff
};

#endif // COMMUNICATIONTHREAD_H__
