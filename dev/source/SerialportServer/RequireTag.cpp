#include "RequireTag.h"

CRequireTag::~CRequireTag()
{
}

CRequireTag* CRequireTag::createRequireTag()
{
	CRequireTag* requireTag = new CRequireTag();
	return requireTag;
}

QString CRequireTag::getValue()
{
	return m_value;
}

void CRequireTag::setValue(const QString& value)
{
	m_value = value;
}

CRequireTag::CRequireTag() :
	CAnyElement("Require")
{
}

