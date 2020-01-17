#pragma once
#include <QMutex>
extern "C"
{
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libswresample/version.h"
}

class MyFFmpeg
{
private:
	MyFFmpeg();
	~MyFFmpeg();
	QMutex mut;
	AVFormatContext* m_afc;			//解码器信息上下文
	int m_vidioStream;				//视频序号
	int m_audioStream;				//音频序号
	SwsContext *m_cCtx = NULL; //视频转换器
	SwrContext *m_aCtx = NULL; //音频转换器
private:
	void init();
public:
	bool m_Isplay;					//控制播放
	qint64 getVideoDuration();
	qint64 getAudioDuration();
	double getVideoTimeBase();
	double getAudioTimeBase();
	double getVideoFrameRate();
	double getAudioFrameRate();
	//获取编解码器上下文
	AVFormatContext* getFormatContext();	
	//
	static MyFFmpeg* getInstance();
	//音频流序号
	int getaudiostreamIndex();
	//视频流序号
	int getVideoStreamIndex();
	bool openVidio(const char* fileName);
	AVFrame* decodeFrame(const AVPacket* pack); //解码压缩的帧
	AVPacket* readFrame();					//从解码器中读取帧
	bool YuvToRGB(char *out, int outweight, int outheight,AVFrame* frame);//像素转换，为显示做准备 转码处理后的视频是YUV, RGB和色度的四通道, 我们需要把它转化成RGB进行显示。
	int ToPCM(char *out, AVFrame* frame); //音频解码
};

