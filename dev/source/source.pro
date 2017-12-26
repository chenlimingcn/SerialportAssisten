TEMPLATE = subdirs

SUBDIRS = Communication \
	Configuration \
	SerialportServer \
	XmlBase \
	XmlBinding \
	SerialportAssisten \
	esframework \
	test

# depends
Communication.depends = XmlBase
Configuration.depends = XmlBase
SerialportServer.depends = XmlBase Communication Configuration
SerialportAssisten.depends = XmlBase Communication Configuration
XmlBase.depends = esframework
XmlBinding.depends = XmlBase
test.depends = XmlBase Communication Configuration
