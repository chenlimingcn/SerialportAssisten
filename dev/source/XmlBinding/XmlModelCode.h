#ifndef XMLMODELCODE_H__
#define XMLMODELCODE_H__

#include <QDomDocument>
#include <QList>
#include "XmlCodeBase.h"

class CXmlModelCode : public CXmlCodeBase
{
public:
	CXmlModelCode();
	~CXmlModelCode();

	virtual bool readfile(const QString& filename);

	// 创建生成代码函数
	virtual bool build();

	virtual QString outPath() const;

protected:
	// 递归节点的代码生成
	void generateModelCls(QDomNode node, QDomNode  parentNode = QDomNode());

	bool generateClsCode( const QString clsName,
		const QList<QString> childrenNames,
		const QList<QString> attrNames,
		const QString& parentName = QString() );

	bool genClsCodeH( const QString clsName, 
		const QList<QString> childrenNames, 
		const QList<QString> attrNames, 
		const QString& parentName = QString() );

	bool genClsCodeCpp( const QString clsName, 
		const QList<QString> childrenNames, 
		const QList<QString> attrNames, 
		const QString& parentName = QString() );

	QString templateDir();

private:
	QDomDocument* m_iedcfgDoc;

	QList<QString> m_haveCode;
};

#endif // XMLMODELCODE_H__
