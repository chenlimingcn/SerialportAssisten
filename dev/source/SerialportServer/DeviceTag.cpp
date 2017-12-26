#include "DeviceTag.h"

#include "FrameTag.h"

CDeviceTag::~CDeviceTag()
{
	qDeleteAll(m_frameTags);
}

CDeviceTag* CDeviceTag::createDeviceTag()
{
	CDeviceTag* iedcfgTag = new CDeviceTag();
	return iedcfgTag;
}


QList<CFrameTag*> CDeviceTag::getFrameTags()
{
	return m_frameTags;
}

void CDeviceTag::addFrameTag(CFrameTag* frameTag)
{
	m_frameTags.append(frameTag);
}

CDeviceTag::CDeviceTag() :
	CAnyElement("Device")
{
}

