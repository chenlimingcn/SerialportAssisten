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
	QString m_elementName;		// 标签名
	QList<CAnyElement*> m_children;	// 子对象
	QList<CAnyAttr*> m_attrs;		// 属性
	QString m_content;		// 文本
};

#endif // ANYTAG_H__
