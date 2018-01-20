/****************************************************
*	文件名:  IEDcfgCodeThread.cpp
*	版本:  version 1.0
*	Copyright (C) 2013 上海积成电子系统有限公司.
*	作者:  陈理明
*	创建时间:  2013-09-24
*	描述:  代码生成线程类
*	修改信息：
*****************************************************/

#include "XmlCodeThread.h"


CXmlCodeThread::CXmlCodeThread(CAbstractXmlCode* handle)
{
	m_handle = handle;
}


CXmlCodeThread::~CXmlCodeThread()
{
}

void CXmlCodeThread::run()
{
	if (m_handle == NULL)
		return ;

	m_isSuccess = m_handle->build();
}
