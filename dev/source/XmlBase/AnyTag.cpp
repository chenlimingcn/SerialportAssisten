#include "AnyTag.h"

#include "AnyAttr.h"

#include <iostream>
using namespace std;

const QString& CAnyTag::elementName()
{
	return m_elementName;
}

QList<CAnyTag*> CAnyTag::children() const
{
	return m_children;
}

bool CAnyTag::save(QXmlStreamWriter& writer)
{
	writer.writeStartElement(m_elementName);

	saveAttributes(writer);
	saveElement(writer);

	writer.writeEndElement();

	return true;
}

CAnyTag* CAnyTag::create_object(const QString& localName, const QString& uri/* = ""*/)
{
	CAnyTag* anyTag = new CAnyTag(localName);
	this->addChild(anyTag);
	return anyTag;
}

void CAnyTag::loadAttributes(const QXmlStreamAttributes& attributes)
{
	foreach (QXmlStreamAttribute attribute, attributes)
	{
		QString name = attribute.name().toString();
		QString value = attribute.value().toString();
		if (name.isEmpty())
			continue;
		CAnyAttr* attr = new CAnyAttr();
		attr->m_attrName = name;
		attr->m_attrValue = value;
		addAttribute(attr);
	}
}

void CAnyTag::addChild( CAnyTag* anyTag )
{
	m_children.append(anyTag);
}

QList<CAnyAttr*> CAnyTag::attributes() const
{
	return m_attrs;
}

void CAnyTag::addAttribute( CAnyAttr* attr )
{
	m_attrs.append(attr);
}

void CAnyTag::saveAttributes(QXmlStreamWriter& writer) const
{
	foreach (CAnyAttr* attribute, m_attrs)
	{
		if (NULL == attribute)
			continue;
		if (attribute->m_attrName.isEmpty() || attribute->m_attrValue.isEmpty())
			continue;
		writer.writeAttribute(attribute->m_attrName, attribute->m_attrValue);
	}
}

void CAnyTag::saveElement( QXmlStreamWriter& writer ) const
{
	foreach (CAnyTag* any, m_children)
	{
		any->save(writer);
	}
}

CAnyTag::~CAnyTag()
{
	foreach (CAnyTag* anyTag, m_children)
	{
		delete anyTag;
	}
	m_children.clear();

	qDeleteAll(m_attrs);
}

CAnyTag::CAnyTag( const QString& name ) :
	m_elementName(name)
{

}

QString CAnyTag::content() const
{
	return m_content;
}

void CAnyTag::setContent( const QString& c )
{
	m_content = c;
}

QStringList CAnyTag::comments() const
{
	return m_comments;
}

void CAnyTag::addComment( const QString& c )
{
	m_comments << c;
}

