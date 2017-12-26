#ifndef REQUIRE_H__
#define REQUIRE_H__

class CRequireTag;

class CRequire
{
public:
	~CRequire();

	static CRequire* create(CRequireTag* requireTag);

	void setBuff(unsigned char* buff);

	int length() { return m_len;}

	bool compare(unsigned char* buff, int len, int& index);

protected:
	CRequire(int len);

private:
	unsigned char* m_buff;

	int m_len;
};

#endif // REQUIRE_H__
