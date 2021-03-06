﻿#ifndef XMLCODE_H__
#define XMLCODE_H__

#include <QDomDocument>
#include <QList>

#include "XmlCodeBase.h"

class CXmlCode :public CXmlCodeBase
{
public:
	CXmlCode(void);
	~CXmlCode(void);
	
	// 读文件
	virtual bool readfile(const QString& filename);

	// 创建生成代码函数
	virtual bool build();

	virtual QString outPath() const;

protected:
	// 生成文档类
	void generateDocment(QDomNode node);

	// 生成未知节点
	void generateUnknownTag();

	// 一个节点的生成函数
	void generateCls(QDomNode node);
	
	// 生成类的代码
	bool generateClsCode(const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames);

	bool genClsCodeH(const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames);
	bool genClsCodeHAttr(const QList<QString>& attrNames,QString& attrCode,QString& attrVarCode);
	bool genClsCodeHEle(const QList<QString>& childrenNames,QString& eleCode,QString& eleVarCode);

	bool genClsCodeCpp(const QString clsName,const QList<QString> childrenNames,const QList<QString> attrNames);
	bool genClsCodeCppAttr(const QList<QString>& attrNames,QString& code);
	bool genClsCodeCppEle(const QList<QString>& childrenNames,QString& code);

	bool genClsCodeCppCreateObj(const QList<QString>& childrenNames,QString & code);

	bool genClsCodeCppSave(const QList<QString>& childrenNames,QString& code);

	bool genClsCodeCppSaveAttr(const QList<QString>& attrNames,QString& code);

	bool genClsCodeCppLoadAttr(const QList<QString>& attrNames,QString& code);

	bool genClsCodeCppClear(const QList<QString>& childrenNames,QString& code);

	bool genClsCodeCppCopy(const QList<QString> childrenNames,QString& code);

	bool genClsCodeCppCopyAttr(const QList<QString> attrNames, QString& code);

	QString templateDir();

private:
	QDomDocument* m_iedcfgDoc;

	QList<QString> m_haveCode;

};


#endif // XMLCODE_H__
