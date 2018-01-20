/****************************************************
*	�ļ���:  IEDcfgCodeThread.cpp
*	�汾:  version 1.0
*	Copyright (C) 2013 �Ϻ����ɵ���ϵͳ���޹�˾.
*	����:  ������
*	����ʱ��:  2013-09-24
*	����:  ���������߳���
*	�޸���Ϣ��
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
