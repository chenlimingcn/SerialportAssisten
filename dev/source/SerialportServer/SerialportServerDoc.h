#ifndef SERIALPORTSERVERDOC_H__
#define SERIALPORTSERVERDOC_H__

#include <QString>
#include <QStack>
#include <QXmlStreamAttributes>

class CAnyElement;
class CSerialportServerTag;

class CSerialportServerDoc
{
public:
	CSerialportServerDoc();
	~CSerialportServerDoc();

	static CSerialportServerDoc* createDocument();

	bool parse(const QString& filename);

	CSerialportServerTag* serialportServerTag() const;

	QString error() const;

protected:
	void createElement(const QString& name, QXmlStreamAttributes attributes);

private:
	CSerialportServerTag* m_serialportServerTag;
	QStack<CAnyElement*> m_stack;
	QString m_error;
};

#endif // SERIALPORTSERVERDOC_H__
