#ifndef XMLCODEBASE_H__
#define XMLCODEBASE_H__

#include <QString>

class CXmlCodeBase
{
public:
	CXmlCodeBase(void);
	virtual ~CXmlCodeBase(void);

	virtual bool readfile(const QString& filename) = 0;
	virtual bool build() = 0;

	// 设置库名称
	void setLibraryName(QString val){ m_libraryname = val; }
	QString libraryName() const { return m_libraryname; }

	void setOutPath(const QString& val) { m_outpath = val; }
	virtual QString outPath() const { return m_outpath; }

private:
	QString m_libraryname;
	QString m_outpath;
};

#endif // XMLCODEBASE_H__
