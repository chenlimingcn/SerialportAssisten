#ifndef COMMUNICATION_H__
#define COMMUNICATION_H__

#include <QList>

class CFrame;
class CFrameTag;
class CSerialportServerDoc;

class CCommunication
{
public:
	~CCommunication();

	static CCommunication* create(CSerialportServerDoc* doc);

	QList<CFrame*> getFrames();
	void addFrame(CFrame* frame);

	// 根据buff查找子数据
	// 参数 buff：当前接收数据的buff的指针
	// 长度 len：当前接收到的数据长度
	CFrame* getFrameByContent(unsigned char* buff, int len, int& index);

protected:
	CCommunication();

private:
	QList<CFrame*> m_frames;
};

#endif // COMMUNICATION_H__
