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
	//format 0 = ��Ƶ��1= ��Ƶ
	void newFrame(AVFrame*,int format); //
private:
	int lastVideoFramePts = 0;
};

