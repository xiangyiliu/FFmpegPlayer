#include "worker.h"
#include <windows.h>
#include "MyAudio.h"

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
		//ÊÓÆµÁ÷µÄ°ü
		if (packet->stream_index == MyFFmpeg::getInstance()->getVideoStreamIndex())
		{
			/*AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
			if (!frame)
			{
				QThread::msleep(5);
				continue;
			}*/
			////ÑÓ³Ù
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
			//ÑÓ³Ù
			auto frameDuration = frame->pkt_pts - lastVideoFramePts;
			lastVideoFramePts = frame->pkt_pts;

			auto duration = packet->duration;

			double mduration = duration / MyFFmpeg::getInstance()->getAudioTimeBase() * 1000;
			Sleep(mduration);
			LOG << "pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getAudioTimeBase();
			LOG << "dts:" << frame->pkt_dts / MyFFmpeg::getInstance()->getAudioTimeBase();
			//emit newFrame(frame, 1);
			//¶ÁÈ¡ÒôÆµ
			char voice[2048 * 2];
			DWORD start = ::GetTickCount();
			int size = MyFFmpeg::getInstance()->ToPCM(voice, frame);
			if (size)
			{
				LOG << "ToPCM cost time:" << ::GetTickCount() - start;
				MyAudio::getInstance()->Write(voice, size);
			}
			av_frame_free(&frame);
		}
		av_packet_free(&packet);
	}
}