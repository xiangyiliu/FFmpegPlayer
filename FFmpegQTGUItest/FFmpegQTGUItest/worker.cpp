#include "worker.h"
#include <windows.h>

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
		//视频流的包
		if (packet->stream_index == MyFFmpeg::getInstance()->getVideoStreamIndex())
		{
			/*AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
			if (!frame)
			{
				QThread::msleep(5);
				continue;
			}*/
			////延迟
			//auto timeforOneframe = (double)1000 / MyFFmpeg::getInstance()->getVideoFrameRate();
			//Sleep(timeforOneframe);
			//LOG << "pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getVideoTimeBase();
			//LOG << "dts:" << frame->pkt_dts / MyFFmpeg::getInstance()->getVideoTimeBase();
			//emit newFrame(frame,0);
		}
		else if (packet->stream_index == MyFFmpeg::getInstance()->getaudiostreamIndex())
		{
			AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
			if (!frame)
			{
				QThread::msleep(5);
				continue;
			}
			//延迟
			auto frameDuration = frame->pkt_pts - lastVideoFramePts;
			lastVideoFramePts = frame->pkt_pts;

			auto duration = packet->duration;

			double mduration = duration / MyFFmpeg::getInstance()->getAudioTimeBase() * 1000;
			Sleep(mduration+1);
			LOG << "pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getAudioTimeBase();
			LOG << "dts:" << frame->pkt_dts / MyFFmpeg::getInstance()->getAudioTimeBase();
			emit newFrame(frame, 1);
		}
		av_packet_free(&packet);
	}
}