#ifndef RESPONSETAG_H__
#define RESPONSETAG_H__

#include "AnyTag.h"

class CResponseTag : public CAnyElement
{
public:
	~CResponseTag();

	static CResponseTag* createResponseTag();

	QString getValue();
	void setValue(const QString& value);

protected:
	CResponseTag();

private:
	QString m_value;
};
#endif // RESPONSETAG_H__
