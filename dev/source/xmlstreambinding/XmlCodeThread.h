/****************************************************
*	filename:  XmlCodeThread.h
*	version:  version 1.0
*	Copyright (C) 2014 Shanghai SidTeam.
*	author:  chenliming
*	create at:  2013-09-24
*	describe:  coding
*	modify£º
*****************************************************/

#ifndef XMLCODETHREAD_H__
#define XMLCODETHREAD_H__

#include <QThread>
#include "AbstractXmlCode.h"


class CXmlCodeThread :
	public QThread
{
public:
	CXmlCodeThread(CAbstractXmlCode* handle);
	~CXmlCodeThread();

	bool isSuccess(){ return m_isSuccess; }

protected:
	virtual void run();

private:
	CAbstractXmlCode* m_handle;
	bool m_isSuccess;
};
#endif // XMLCODETHREAD_H__

