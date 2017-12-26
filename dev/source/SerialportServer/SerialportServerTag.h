#ifndef SERIALPORTSERVERTAG_H__
#define SERIALPORTSERVERTAG_H__

#include <QList>

#include "AnyTag.h"

class CDeviceTag;

class CSerialportServerTag : public CAnyElement
{
public:
	~CSerialportServerTag();

	static CSerialportServerTag* createSerialportServerTag();

	QList<CDeviceTag*> getDeviceTags();
	void addDeviceTag(CDeviceTag* deviceTag);

protected:
	CSerialportServerTag();

private:
	QList<CDeviceTag*> m_deviceTags;
};
#endif // SERIALPORTSERVERTAG_H__
