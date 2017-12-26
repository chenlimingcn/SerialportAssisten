#include "Frame.h"
#include <time.h>

#include "FrameTag.h"
#include "Response.h"
#include "ResponseTag.h"
#include "Require.h"
#include "RequireTag.h"

CFrame::CFrame()
{
	m_require = NULL;
	m_response = NULL;
}


CFrame::~CFrame()
{
}

CFrame* CFrame::create( CFrameTag* frameTag )
{
	if (NULL == frameTag)
		return NULL;
	CRequireTag* requireTag = frameTag->getRequireTag();
	if (NULL == requireTag)
		return NULL;
	
	CResponseTag* responseTag = frameTag->getResponseTag();
	if (NULL == responseTag)
		return NULL;

	CFrame* frame = new CFrame();
	
	CRequire* require = CRequire::create(requireTag);
	frame->m_require = require;

	CResponse* response = CResponse::create(responseTag);
	frame->m_response = response;

	return frame;
}

CRequire* CFrame::getRequire()
{
	return m_require;
}

void CFrame::setRequire( CRequire* require )
{
	m_require = require;
}

CResponse* CFrame::getResponse()
{
	return m_response;
}

void CFrame::setResponse( CResponse* response )
{
	m_response = response;
}
