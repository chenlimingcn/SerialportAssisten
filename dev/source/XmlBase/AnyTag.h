#ifndef ANYTAG_H__
#define ANYTAG_H__

#include <QXmlStreamAttributes>
#include <QString>
#include <QStringList>
#include <QList>

#include "XmlBase_global.h"

class CAnyAttr;

class XMLBASE_API CAnyTag
{
public:
	CAnyTag(const QString& name);
	virtual ~CAnyTag();

	const QString& elementName();

	QList<CAnyTag*> children() const;
	void addChild(CAnyTag* anyTag);

	bool save(QXmlStreamWriter& writer);

	virtual CAnyTag* create_object(const QString& localName, const QString& uri = "");

	virtual void loadAttributes(const QXmlStreamAttributes& attributes);
	QList<CAnyAttr*> attributes() const;
	void addAttribute(CAnyAttr* attr);

	QString content() const;
	void setContent(const QString& c);

	QStringList comments() const;
	void addComment( const QString& c);

protected:
	virtual void saveAttributes(QXmlStreamWriter& writer) const;
	virtual void saveElement(QXmlStreamWriter& writer) const;

private:
	QString m_elementName;		// ��ǩ��
	QList<CAnyTag*> m_children;	// �Ӷ���
	QList<CAnyAttr*> m_attrs;		// ����
	QString m_content;		// �ı�
	QStringList m_comments;   // ע��
};
#endif // ANYTAG_H__
