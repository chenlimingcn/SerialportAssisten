#pragma once
#include <QStatusBar>
class CStatusBar :
	public QStatusBar
{
	Q_OBJECT
public:
	CStatusBar(QWidget * parent = 0);
	~CStatusBar();
};

