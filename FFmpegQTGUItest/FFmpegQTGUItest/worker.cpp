#include "worker.h"
#include <windows.h>
#include <QQueue>

extern QMutex audioLock;
extern QMutex videoLock;
extern QQueue<AVFrame*> audioframeList;	//“Ù∆µ÷°
extern QQueue<AVFrame*> videoframeList;	// ”∆µ÷°
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
		// ”∆µ¡˜µƒ∞¸
		if (packet->stream_index == MyFFmpeg::getInstance()->getVideoStreamIndex())
		{
			AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
			if (!frame)
			{
				QThread::msleep(1);
				continue;
			}
			//—”≥Ÿ
			/*auto frameDuration = frame->pkt_pts - lastVideoFramePts;
			lastVideoFramePts = frame->pkt_pts;
			double mduration = frameDuration / MyFFmpeg::getInstance()->getVideoTimeBase() * 1000;
			Sleep(mduration);*/

			//LOG << "pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getVideoTimeBase();
			//LOG << "dts:" << frame->pkt_dts / MyFFmpeg::getInstance()->getVideoTimeBase();
			//emit newFrame(frame,0);
			//Sleep(5);
			//QMutexLocker locker(&videoLock);
			//videoframeList.enqueue(frame);
			av_frame_free(&frame);
		}
		else if (packet->stream_index == MyFFmpeg::getInstance()->getaudiostreamIndex())
		{
			QMutexLocker locker(&audioLock);
			if (audioframeList.count() >= 100)
			{
				QThread::msleep(1);
				continue;
			}
			AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
			if (!frame)
			{
				QThread::msleep(1);
				continue;
			}
			//—”≥Ÿ
			//auto timeforOneframe = (double)1000 / MyFFmpeg::getInstance()->getAudioFrameRate();
			//auto frameDuration  = frame->pkt_pts - lastAudioFramePts;
			//lastAudioFramePts = frame->pkt_pts;
			//double mduration = frameDuration /MyFFmpeg::getInstance()->getAudioTimeBase()*1000;
			//Sleep(mduration/*>3? mduration-3 : mduration*/);
			//LOG << "pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getAudioTimeBase();
			//LOG << "dts:" << frame->pkt_dts / MyFFmpeg::getInstance()->getAudioTimeBase();
			//emit newFrame(frame, 1);
			//Sleep(1);
			audioframeList.enqueue(frame);
		}
		av_packet_free(&packet);
	}
}