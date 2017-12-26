/****************************************************
*	filename:  XmlCode.h
*	version:  version 1.0
*	Copyright (C) 2014 Shanghai SidTeam.
*	author:  
*	create at:  2014-08-03
*	describe:  coding
*	modify��
*****************************************************/

#ifndef XMLCODE_H__
#define XMLCODE_H__


#include <QDomDocument>
#include "AbstractXmlCode.h"

class CXmlCode :public CAbstractXmlCode
{
public:
	CXmlCode(QObject* parent = 0);
	~CXmlCode();
	
	// ���õ�����
	void setExportName(QString val = QString("")){ m_exportname = val; }

	// �������Ŀ¼
	void setOutPath(const QString& val = QString(".")) {  m_outpath = val; }
	// ���ļ�
	bool readfile(QString filename);

	// �������ɴ��뺯��
	virtual bool build();

protected:
	// һ���ڵ�����ɺ���
	void generateCls(QDomNode node);
	
	// ������Ĵ���
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

	QString getAbsoluteConfigPath();
private:
	QDomDocument* m_iedcfgDoc;

	QList<QString> m_haveCode;

	QString m_exportname;
	QString m_outpath;
};

#endif // XMLCODE_H__
