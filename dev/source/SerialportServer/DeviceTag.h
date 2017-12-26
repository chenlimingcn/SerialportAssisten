#ifndef DEVICETAG_H__
#define DEVICETAG_H__

#include "AnyTag.h"

class CFrameTag;

class CDeviceTag : public CAnyElement
{
public:
	~CDeviceTag();

	static CDeviceTag* createDeviceTag();

	QList<CFrameTag*> getFrameTags();
	void addFrameTag(CFrameTag* frameTag);

protected:
	CDeviceTag();

private:
	QList<CFrameTag*> m_frameTags;
};

#endif // DEVICETAG_H__
