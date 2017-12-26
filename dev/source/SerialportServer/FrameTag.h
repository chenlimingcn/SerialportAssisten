#ifndef FRAMETAG_H__
#define FRAMETAG_H__

#include "AnyTag.h"

class CRequireTag;
class CResponseTag;

class CFrameTag : public CAnyElement
{
public:
	~CFrameTag();

	static CFrameTag* createframeTag();

	CRequireTag* getRequireTag();
	void setRequireTag(CRequireTag* requireTag);

	CResponseTag* getResponseTag();
	void setResponseTag(CResponseTag* responseTag);
	
protected:
	CFrameTag();

private:
	CRequireTag* m_requireTag;
	CResponseTag* m_responseTag;
};
#endif // FRAMETAG_H__
