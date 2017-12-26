#include "SerialportServerDoc.h"


#include <QFile>
#include <QXmlStreamReader>

#include "AllTag.h"

CSerialportServerDoc::CSerialportServerDoc()
{
	m_serialportServerTag = NULL;
}

CSerialportServerDoc::~CSerialportServerDoc()
{

}

CSerialportServerDoc* CSerialportServerDoc::createDocument()
{
	CSerialportServerDoc* serialportServerDoc = new CSerialportServerDoc();

	return serialportServerDoc;
}

bool CSerialportServerDoc::parse( const QString& filename )
{
	QFile file(filename);
	if (!file.open(QIODevice::Text|QIODevice::ReadOnly))
	{
		m_error = "file can not open!";
		return false;
	}

	QXmlStreamReader xmlReader(&file);

	while (!xmlReader.atEnd())
	{
		QXmlStreamReader::TokenType tokenType = xmlReader.readNext();

		QString clsName;	// 标签名
		QXmlStreamAttributes attributes;	// 标签属性
		CAnyElement* anyTag = NULL;
		switch (tokenType)
		{
		case QXmlStreamReader::NoToken:
			break;
		case QXmlStreamReader::Invalid:	// 出错了
			m_error = xmlReader.errorString()  
				+ QString::fromLatin1("\nline:") + xmlReader.lineNumber()
				+ QString::fromLatin1(" colu:") + xmlReader.columnNumber();
			return false;
			break;
		case QXmlStreamReader::StartDocument:
			break;
		case QXmlStreamReader::EndDocument:
			break;
		case QXmlStreamReader::StartElement:
			clsName = xmlReader.name().toString();
			attributes = xmlReader.attributes();
			createElement(clsName, attributes);
			break;
		case QXmlStreamReader::EndElement:
			m_stack.pop();
			break;
		case QXmlStreamReader::Characters:
			if (!m_stack.isEmpty())
			{
				anyTag = static_cast<CAnyElement*>(m_stack.top());
				anyTag->setContent(xmlReader.text().toString());
			}
			break;
		case QXmlStreamReader::Comment:
			break;
		case QXmlStreamReader::DTD:
			break;
		case QXmlStreamReader::EntityReference:
			break;
		case QXmlStreamReader::ProcessingInstruction:
			break;
		default:
			break;
		}
	}
	file.close();
	return true;
}

CSerialportServerTag* CSerialportServerDoc::serialportServerTag() const
{
	return m_serialportServerTag;
}

QString CSerialportServerDoc::error() const
{
	return m_error;
}

void CSerialportServerDoc::createElement( const QString& name, QXmlStreamAttributes attributes )
{
	if ("SerialportServer" == name)
	{
		m_serialportServerTag = CSerialportServerTag::createSerialportServerTag();
		foreach (QXmlStreamAttribute attribute, attributes)
		{
			CAnyAttr* attr = new CAnyAttr(attribute.name().toString(),attribute.value().toString());
			m_serialportServerTag->addAttribute(attr);
		}

		m_stack.push(m_serialportServerTag);
	}
	else if ("Device" == name)
	{
		CDeviceTag* deviceTag = CDeviceTag::createDeviceTag();
		foreach (QXmlStreamAttribute attribute,attributes)
		{
			CAnyAttr* attr = new CAnyAttr(attribute.name().toString(), attribute.value().toString());
			deviceTag->addAttribute(attr);
		}
		m_serialportServerTag->addDeviceTag(deviceTag);

		m_stack.push(deviceTag);
	}

	else if ("Frame" == name)
	{
		CFrameTag* frameTag = CFrameTag::createframeTag();
		foreach (QXmlStreamAttribute attribute, attributes)
		{
			QString attrName = attribute.name().toString();
			QString val = attribute.value().toString();

			CAnyAttr* attr = new CAnyAttr(attrName, val);
			frameTag->addAttribute(attr);
		}
		CDeviceTag* devTag = static_cast<CDeviceTag*>(m_stack.top());
		devTag->addFrameTag(frameTag);
		m_stack.push(frameTag);
	}
	else if ("Response" == name)
	{
		CResponseTag* responseTag = CResponseTag::createResponseTag();
		foreach (QXmlStreamAttribute attribute, attributes)
		{
			QString attrName = attribute.name().toString();
			QString val = attribute.value().toString();

			if ("value" == attrName)
				responseTag->setValue(val);
			else
			{
				CAnyAttr* attr = new CAnyAttr(attrName, val);
				responseTag->addAttribute(attr);
			}
		}
		CFrameTag* frameTag = static_cast<CFrameTag*>(m_stack.top());
		frameTag->setResponseTag(responseTag);

		m_stack.push(responseTag);
	}
	else if ("Require" == name)
	{
		CRequireTag* requireTag = CRequireTag::createRequireTag();
		foreach (QXmlStreamAttribute attribute, attributes)
		{
			QString attrName = attribute.name().toString();
			QString val = attribute.value().toString();

			if ("value" == attrName)
				requireTag->setValue(val);
			else
			{
				CAnyAttr* attr = new CAnyAttr(attrName, val);
				requireTag->addAttribute(attr);
			}
		}
		CFrameTag* frameTag = static_cast<CFrameTag*>(m_stack.top());
		frameTag->setRequireTag(requireTag);

		m_stack.push(requireTag);
	}

	else
	{
		CAnyElement* anyTag = CAnyElement::createAnyElement(name);
		foreach (QXmlStreamAttribute attribute, attributes)
		{
			CAnyAttr* attr = new CAnyAttr(attribute.name().toString(), attribute.value().toString());
			anyTag->addAttribute(attr);
		}

		CAnyElement* parentTag = static_cast<CAnyElement*>(m_stack.top());
		parentTag->addChild(anyTag);

		m_stack.push(anyTag);
	}
}
