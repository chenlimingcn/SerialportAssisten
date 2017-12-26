#include "XmlBase.h"

#include "AnyAttr.h"

CXmlBase* CXmlBase::createInstance( const QString& name )
{
	CXmlBase* anyTag = new CXmlBase(name);
	return anyTag;
}

const QString& CXmlBase::elementName()
{
	return m_elementName;
}

QList<CXmlBase*> CXmlBase::getXmlBases() const 
{
	return m_xmlbases;
}

CXmlBase* CXmlBase::getFirstXmlBase() const
{
	if (m_xmlbases.count() > 0)
		return m_xmlbases.at(0);
	return NULL;
}

bool CXmlBase::addXmlBase(CXmlBase* pObj)
{
	if (NULL == pObj)
		return false;
	m_xmlbases.append(pObj);
	return true;
}

bool CXmlBase::removeXmlBase(CXmlBase* pObj)
{
	if (NULL == pObj)
		return false;
	return m_xmlbases.removeOne(pObj);
}

bool CXmlBase::removeAllXmlBases(bool bAlsoDelete /* = true */)
{
	if (bAlsoDelete)
	{
		foreach (CXmlBase* xmlbase, m_xmlbases)
		{
			delete xmlbase;
		}
	}
	m_xmlbases.clear();
	return true;
}

int CXmlBase::moveXmlBase(CXmlBase* pObj, int idx /* = -1 */)
{
	if (pObj == NULL || !m_xmlbases.contains(pObj))
		return -1;

	int pos = idx;
	if (pos < 0 || pos >= m_xmlbases.size())
		pos = m_xmlbases.size() -1;

	m_xmlbases.removeAll(pObj);
	m_xmlbases.insert(pos,pObj);

	return pos;
}
uint CXmlBase::countXmlBase()
{
	return m_xmlbases.count();
}

QList<CAnyAttr*> CXmlBase::attributes() const
{
	return m_attrs;
}

void CXmlBase::addAttribute( CAnyAttr* attr )
{
	m_attrs.append(attr);
}

CXmlBase::~CXmlBase()
{
	foreach (CXmlBase* anyTag, m_xmlbases)
	{
		delete anyTag;
	}
	m_xmlbases.clear();

	qDeleteAll(m_attrs);
}

CXmlBase::CXmlBase( const QString& name ) :
	m_elementName(name)
{

}

QString CXmlBase::content() const
{
	return m_content;
}

void CXmlBase::setContent( const QString& c )
{
	m_content = c;
}

bool CXmlBase::loadAttribute( const QXmlStreamAttribute& attribute )
{
	CAnyAttr* anyAttr = new CAnyAttr();
}

bool CXmlBase::saveAttribute( QXmlStreamWriter& writer ) const
{

}

bool CXmlBase::saveElement( QXmlStreamWriter& writer ) const
{

}

