#ifndef ANYTAG_H__
#define ANYTAG_H__

#include <QString>
#include <QList>

class CAnyAttr;

class CAnyElement
{
public:
	~CAnyElement();
	static CAnyElement* createAnyElement(const QString& name);

	const QString& elementName();

	QList<CAnyElement*> children() const;
	void addChild(CAnyElement* anyTag);

	QList<CAnyAttr*> attributes() const;
	void addAttribute(CAnyAttr* attr);

	QString content() const;
	void setContent(const QString& c);

protected:
	CAnyElement(const QString& name);

private:
	QString m_elementName;		// ��ǩ��
	QList<CAnyElement*> m_children;	// �Ӷ���
	QList<CAnyAttr*> m_attrs;		// ����
	QString m_content;		// �ı�
};

#endif // ANYTAG_H__
