#ifndef XMLBASE_H__
#define XMLBASE_H__

#include <QString>
#include <QList>
#include <QXmlStreamWriter>

#include "XmlBase_global.h"

class CAnyAttr;

class XMLBASE_API CXmlBase
{
public:
	~CXmlBase();
	static CXmlBase* createInstance(const QString& name);

	CXmlBase& operator= (const CXmlBase& other);

	void copy_from(const CXmlBase* pOther);

	const QString& elementName();

	//获得元素XmlBase的对象集合 
	QList<CXmlBase*> getXmlBases () const;

	//获得元素XmlBase的对象集合中第一个元素
	CXmlBase* getFirstXmlBase () const;

	//添加一个XmlBase元素对象
	bool addXmlBase( CXmlBase* pObj);

	//删除一个XmlBase元素对象
	bool removeXmlBase( CXmlBase* pObj);

	//删除所有的$(ELEMENTNAME)元素对象
	bool removeAllXmlBases( bool bAlsoDelete = true);


	//移动一个对象到队列的指定位置，如果idx为-1则移动到队列的末尾。
	//函数返回移动后的位置
	int moveXmlBase(CXmlBase* pObj, int idx = -1);

	//获得XmlBase元素的个数
	uint countXmlBase();

	//获得XmlBase元素对象在队列中的序号,如果没有找到，则返回-1
	int getXmlBaseIndex(CXmlBase* pObj);

	QList<CAnyAttr*> attributes() const;
	void addAttribute(CAnyAttr* attr);

	QString content() const;
	void setContent(const QString& c);

	// 载入属性
	virtual bool loadAttribute(const QXmlStreamAttribute& attribute);

	//保存属性
	virtual bool saveAttribute( QXmlStreamWriter& writer ) const;

	//保存元素
	virtual bool saveElement(QXmlStreamWriter& writer) const;
protected:
	CXmlBase(const QString& name);

private:
	QString m_elementName;		// 标签名
	QList<CXmlBase*> m_xmlbases;	// 子对象
	QList<CAnyAttr*> m_attrs;		// 属性
	QString m_content;		// 文本
};

#endif // XMLBASE_H__
