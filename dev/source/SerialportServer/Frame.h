#ifndef FRAME_H__
#define FRAME_H__

class CFrameTag;
class CRequire;
class CResponse;

class CFrame
{
public:
	~CFrame();
	
	static CFrame* create(CFrameTag* frameTag);

	CRequire* getRequire();
	void setRequire(CRequire* require);

	CResponse* getResponse();
	void setResponse(CResponse* response);

protected:
	CFrame();

private:
	CRequire* m_require;
	CResponse* m_response;
};
#endif // FRAME_H__

