#include "ResponseTag.h"

CResponseTag::~CResponseTag()
{
}

CResponseTag* CResponseTag::createResponseTag()
{
	CResponseTag* responseTag = new CResponseTag();
	return responseTag;
}

QString CResponseTag::getValue()
{
	return m_value;
}

void CResponseTag::setValue(const QString& value)
{
	m_value = value;
}

CResponseTag::CResponseTag() :
	CAnyElement("Response")
{
}

