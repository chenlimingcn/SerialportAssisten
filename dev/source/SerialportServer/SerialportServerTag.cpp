#include "SerialportServerTag.h"

#include "DeviceTag.h"

CSerialportServerTag::~CSerialportServerTag()
{
	qDeleteAll(m_deviceTags);
}

CSerialportServerTag* CSerialportServerTag::createSerialportServerTag()
{
	CSerialportServerTag* serialportServerTag = new CSerialportServerTag();
	return serialportServerTag;
}

QList<CDeviceTag*> CSerialportServerTag::getDeviceTags()
{
	return m_deviceTags;
}

void CSerialportServerTag::addDeviceTag(CDeviceTag* deviceTag)
{
	m_deviceTags.append(deviceTag);
}

CSerialportServerTag::CSerialportServerTag() :
	CAnyElement("SerialportServer")
{
}

