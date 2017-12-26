#include "FrameTag.h"

#include "RequireTag.h"
#include "ResponseTag.h"

CFrameTag::~CFrameTag()
{
	delete m_requireTag;
	delete m_responseTag;
}

CFrameTag* CFrameTag::createframeTag()
{
	CFrameTag* iedcfgTag = new CFrameTag();
	return iedcfgTag;
}


CRequireTag* CFrameTag::getRequireTag()
{
	return m_requireTag;
}

void CFrameTag::setRequireTag( CRequireTag* requireTag )
{
	m_requireTag = requireTag;
}

CResponseTag* CFrameTag::getResponseTag()
{
	return m_responseTag;
}

void CFrameTag::setResponseTag( CResponseTag* responseTag )
{
	m_responseTag = responseTag;
}

CFrameTag::CFrameTag() :
	CAnyElement("Frame")
{
	m_requireTag = NULL;
	m_responseTag = NULL;
}

