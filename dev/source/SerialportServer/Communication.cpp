#include "Communication.h"

#include "DeviceTag.h"
#include "Frame.h"
#include "FrameTag.h"
#include "SerialportServerDoc.h"
#include "SerialportServerTag.h"
#include "Require.h"

CCommunication::CCommunication()
{
}


CCommunication::~CCommunication()
{
	qDeleteAll(m_frames);
}

CCommunication* CCommunication::create(CSerialportServerDoc* doc)
{
	if (NULL == doc)
		return NULL;
	CSerialportServerTag* spTag = doc->serialportServerTag();
	if (NULL == spTag)
		return NULL;

	CCommunication* cmm = new CCommunication();
	foreach (CDeviceTag* devTag, spTag->getDeviceTags())
	{
		if (NULL == devTag)
			continue;
		foreach (CFrameTag* frameTag, devTag->getFrameTags())
		{
			if (NULL == frameTag)
				continue;
			CFrame* frame = CFrame::create(frameTag);
			if (NULL == frame)
			{
				delete cmm;
				return NULL;
			}
			cmm->m_frames.append(frame);
		}
	}

	return cmm;
}

QList<CFrame*> CCommunication::getFrames()
{
	return m_frames;
}

void CCommunication::addFrame(CFrame* frame)
{
	m_frames.append(frame);;
}

CFrame* CCommunication::getFrameByContent( unsigned char* buff, int len, int& index )
{
	foreach (CFrame* frame,m_frames)
	{
		if (NULL == frame)
			continue;
		CRequire* require = frame->getRequire();
		if (NULL == require)
			continue;
		if (require->compare(buff, len, index))
			return frame;
	}

	return NULL;
}
