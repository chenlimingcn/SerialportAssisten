#include "FrameOutPut.h"

#include <QDebug>
#include <stdio.h>

#include <iostream>
using namespace std;

CFrameOutPut::CFrameOutPut()
{
}


CFrameOutPut::~CFrameOutPut()
{
}

void CFrameOutPut::frameOuput( /*QIODevice* iodev, */unsigned char* buff, unsigned int length, int base /*= 16*/ )
{
	if (16 == base) for (unsigned int i=0; i < length; ++i)
	{

		char ch[4];
		sprintf(ch, "%02X ", (char*)buff[i]);
		cout << ch;
	}
	else if (0 == base)
	{
		cout << buff;
	}
	cout << endl;
}
