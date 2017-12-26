#include "AnyTag.h"

#include "AnyAttr.h"

CAnyElement* CAnyElement::createAnyElement( const QString& name )
{
	CAnyElement* anyTag = new CAnyElement(name);
	return anyTag;
}

const QString& CAnyElement::elementName()
{
	return m_elementName;
}

QList<CAnyElement*> CAnyElement::children() const
{
	return m_children;
}

void CAnyElement::addChild( CAnyElement* anyTag )
{
	m_children.append(anyTag);
}

QList<CAnyAttr*> CAnyElement::attributes() const
{
	return m_attrs;
}

void CAnyElement::addAttribute( CAnyAttr* attr )
{
	m_attrs.append(attr);
}

CAnyElement::~CAnyElement()
{
	foreach (CAnyElement* anyTag, m_children)
	{
		delete anyTag;
	}
	m_children.clear();

	qDeleteAll(m_attrs);
}

CAnyElement::CAnyElement( const QString& name ) :
	m_elementName(name)
{

}

QString CAnyElement::content() const
{
	return m_content;
}

void CAnyElement::setContent( const QString& c )
{
	m_content = c;
}

