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
	//format 0 =  ”∆µ£¨1= “Ù∆µ
	void newFrame(AVFrame*,int format); //
private:
	int lastVideoFramePts = 0;
};

