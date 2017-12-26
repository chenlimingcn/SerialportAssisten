#ifndef FRAMEOUTPUT_H__
#define FRAMEOUTPUT_H__

#include <QIODevice>

class CFrameOutPut
{
public:
	CFrameOutPut();
	~CFrameOutPut();

	static void frameOuput(/*QIODevice* iodev, */unsigned char* buff, unsigned int length, int base = 16);
};

#endif // FRAMEOUTPUT_H__
