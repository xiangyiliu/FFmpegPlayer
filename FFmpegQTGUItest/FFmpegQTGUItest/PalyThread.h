#pragma once
#include <QThread>
class PalyThread : public QThread
{
public:
	PalyThread();
	~PalyThread();
	virtual void run();
};

