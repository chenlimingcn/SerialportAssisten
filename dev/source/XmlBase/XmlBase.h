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

	//���Ԫ��XmlBase�Ķ��󼯺� 
	QList<CXmlBase*> getXmlBases () const;

	//���Ԫ��XmlBase�Ķ��󼯺��е�һ��Ԫ��
	CXmlBase* getFirstXmlBase () const;

	//���һ��XmlBaseԪ�ض���
	bool addXmlBase( CXmlBase* pObj);

	//ɾ��һ��XmlBaseԪ�ض���
	bool removeXmlBase( CXmlBase* pObj);

	//ɾ�����е�$(ELEMENTNAME)Ԫ�ض���
	bool removeAllXmlBases( bool bAlsoDelete = true);


	//�ƶ�һ�����󵽶��е�ָ��λ�ã����idxΪ-1���ƶ������е�ĩβ��
	//���������ƶ����λ��
	int moveXmlBase(CXmlBase* pObj, int idx = -1);

	//���XmlBaseԪ�صĸ���
	uint countXmlBase();

	//���XmlBaseԪ�ض����ڶ����е����,���û���ҵ����򷵻�-1
	int getXmlBaseIndex(CXmlBase* pObj);

	QList<CAnyAttr*> attributes() const;
	void addAttribute(CAnyAttr* attr);

	QString content() const;
	void setContent(const QString& c);

	// ��������
	virtual bool loadAttribute(const QXmlStreamAttribute& attribute);

	//��������
	virtual bool saveAttribute( QXmlStreamWriter& writer ) const;

	//����Ԫ��
	virtual bool saveElement(QXmlStreamWriter& writer) const;
protected:
	CXmlBase(const QString& name);

private:
	QString m_elementName;		// ��ǩ��
	QList<CXmlBase*> m_xmlbases;	// �Ӷ���
	QList<CAnyAttr*> m_attrs;		// ����
	QString m_content;		// �ı�
};

#endif // XMLBASE_H__
