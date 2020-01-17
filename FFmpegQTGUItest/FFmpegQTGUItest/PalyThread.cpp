#include "PalyThread.h"
#include "include.h"

using namespace std;

static list<AVPacket> g_videos; //存放视频帧

PalyThread::PalyThread()
{
}


PalyThread::~PalyThread()
{
}

void PalyThread::run()
{
	while (1)
	{
		if (!MyFFmpeg::getInstance()->m_Isplay)
		{
			msleep(5);//无限等待
			continue;
		}
		while (g_videos.size() > 0)
		{
			AVPacket pack = g_videos.front();
			LOG << pack.stream_index;
			MyFFmpeg::getInstance()->decodeFrame(&pack);
			av_packet_unref(&pack);
			g_videos.pop_front();//解码完成的帧从list前面弹出
		}

		AVPacket* packet = MyFFmpeg::getInstance()->readFrame();

		if (packet->size <= 0)
		{
			break;
		}
		g_videos.push_back(*packet);
	}
}
