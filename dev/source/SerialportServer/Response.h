#ifndef RESPONSE_H__
#define RESPONSE_H__

#include <QIODevice>

class CResponseTag;

class CResponse
{
public:
	~CResponse();

	static CResponse* create(CResponseTag* responseTag);

	bool write(QIODevice* iodev);

	unsigned int lenght(){ return m_len; }

protected:
	CResponse(int len);

private:
	unsigned char* m_buff;
	int m_len;
};
#endif // RESPONSE_H__

