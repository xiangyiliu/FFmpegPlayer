#pragma once
#include <qobject.h>
#include "include.h"
class worker :
	public QObject
{
 Q_OBJECT
public:
	worker();
	~worker();
public slots:
	void decode();
signals:
	void newPacket(AVPacket*);
};

