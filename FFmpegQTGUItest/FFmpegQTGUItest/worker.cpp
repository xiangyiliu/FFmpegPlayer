#include "worker.h"


worker::worker()
{
}


worker::~worker()
{
}

void worker::decode()
{
	LOG << QThread::currentThreadId();
	while (1)
	{
		AVPacket* packet = MyFFmpeg::getInstance()->readFrame();
		if (!packet ||packet->size <= 0)
		{
			QThread::msleep(5);
			continue;
		}
		emit newPacket(packet);
	}
}