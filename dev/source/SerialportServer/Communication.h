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

	// ����buff����������
	// ���� buff����ǰ�������ݵ�buff��ָ��
	// ���� len����ǰ���յ������ݳ���
	CFrame* getFrameByContent(unsigned char* buff, int len, int& index);

protected:
	CCommunication();

private:
	QList<CFrame*> m_frames;
};

#endif // COMMUNICATION_H__
