/****************************************************
*	filename:  XmlCode.h
*	version:  version 1.0
*	Copyright (C) 2014 Shanghai SidTeam.
*	author:  
*	create at:  2014-08-03
*	describe:  coding
*	modify：
*****************************************************/

#ifndef XMLCODE_H__
#define XMLCODE_H__


#include <QDomDocument>
#include "QStringList"

#include "AbstractXmlCode.h"

class CXmlCode :public CAbstractXmlCode
{
public:
	CXmlCode(QObject* parent = 0);
	~CXmlCode();
	
	// 设置库名
	void setLibName(QString val){ m_libName = val; }

	// 设置输出目录
	void setOutPath(const QString& val = QString(".")) {  m_outpath = val; }
	// 读文件
	bool readfile(QString filename);

	// 创建生成代码函数
	virtual bool build();

protected:
	// 生成导出声明
	void generateExportfile();

	void generateDocment(QDomNode node);

	// 一个节点的生成函数
	void generateCls(QDomNode node);
	
	// 生成All.h
	void generateAllh();

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

	bool genClsCodeCppCopy(const QList<QString> childrenNames,QString code);

private:
	QString exportName();
private:
	QDomDocument* m_iedcfgDoc;

	QList<QString> m_haveCode;

	QStringList m_eleNames;

	QString m_libName;
	QString m_outpath;
};

class CXmlCodeHelper
{
public:
	static bool readCodetemplates(const QString& filename, QString& strCode);

	static bool writeCode(const QString& filename , const QString& strCode);
};

#endif // XMLCODE_H__
