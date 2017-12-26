#ifndef REQUIRETAG_H__
#define REQUIRETAG_H__

#include "AnyTag.h"

class CRequireTag : public CAnyElement
{
public:
	~CRequireTag();

	static CRequireTag* createRequireTag();

	QString getValue();
	void setValue(const QString& value);
	
protected:
	CRequireTag();

private:
	QString m_value;
};
#endif // REQUIRETAG_H__
