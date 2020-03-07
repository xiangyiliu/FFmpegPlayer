#include "MyFFmpeg.h"
#include "include.h"
#include "MyAudio.h"

MyFFmpeg::MyFFmpeg()
{
	init();
}


MyFFmpeg::~MyFFmpeg()
{
}

void MyFFmpeg::init()
{
	m_afc = NULL;
	m_vidioStream = -1;
	m_audioStream = -1;
	m_Isplay = false;
}

qint64 MyFFmpeg::getVideoDuration()
{
	Q_ASSERT(m_afc && m_vidioStream != -1);
	return m_afc->streams[m_vidioStream]->duration;
}

qint64 MyFFmpeg::getAudioDuration()
{
	Q_ASSERT(m_afc && m_audioStream != -1);
	return m_afc->streams[m_audioStream]->duration;
}

double MyFFmpeg::getVideoTimeBase()
{
	Q_ASSERT(m_afc && m_vidioStream != -1);
	double den = (double)m_afc->streams[m_vidioStream]->time_base.den;
	double num = (double)m_afc->streams[m_vidioStream]->time_base.num;
	return den/num;
}
double MyFFmpeg::getAudioTimeBase()
{
	Q_ASSERT(m_afc && m_audioStream != -1);
	double den = (double)m_afc->streams[m_audioStream]->time_base.den;
	double num = (double)m_afc->streams[m_audioStream]->time_base.num;
	return den / num;
}

double MyFFmpeg::getVideoFrameRate()
{
	Q_ASSERT(m_afc && m_vidioStream != -1);
	double den = (double)m_afc->streams[m_vidioStream]->avg_frame_rate.den;
	double num = (double)m_afc->streams[m_vidioStream]->avg_frame_rate.num;
	return num / den;
}

double MyFFmpeg::getAudioFrameRate()
{
	Q_ASSERT(m_afc && m_audioStream != -1);
	double den = (double)m_afc->streams[m_audioStream]->avg_frame_rate.den;
	double num = (double)m_afc->streams[m_audioStream]->avg_frame_rate.num;
	return num / den;
}

AVFormatContext* MyFFmpeg::getFormatContext()
{
	return m_afc;
}

MyFFmpeg* MyFFmpeg::getInstance()
{
	static MyFFmpeg m_FFmpeg;
	return &m_FFmpeg;
}

int MyFFmpeg::getaudiostreamIndex()
{
	return m_audioStream;
}

int MyFFmpeg::getVideoStreamIndex()
{
	return m_vidioStream;
}

bool MyFFmpeg::openVidio(const char* fileName)
{
	QMutexLocker locker(&mut);
	int ret = avformat_open_input(&m_afc, fileName, NULL, NULL);
	LOG <<"streams count:"<< m_afc->nb_streams;
	LOG << "file name:" << m_afc->filename;
	LOG << "duration:" << m_afc->duration;
	LOG << "bit_rate:" << m_afc->bit_rate;
	LOG << "AVInputFormat 信息:";
	AVInputFormat* iformat = m_afc->iformat;
	LOG << "封装格式的长名称:"<< iformat->long_name;
	LOG << "封装格式的扩展名:" << iformat->extensions;
	LOG << "封装格式ID:" << iformat->raw_codec_id;
	
	for (int i=0;i< m_afc->nb_streams;i++)
	{
		AVCodecContext* acc = m_afc->streams[i]->codec;
		LOG << "stream信息：";
		LOG << "时间基准:" << m_afc->streams[i]->time_base.num << "/" << m_afc->streams[i]->time_base.den;
		LOG << "时间长度:" << m_afc->streams[i]->duration;
		LOG << "帧率:" << m_afc->streams[i]->avg_frame_rate.num<<"/"<< m_afc->streams[i]->avg_frame_rate.den;

		LOG << "stream"<<i<<"的编解码器上下文信息：";
		LOG << "图像的宽高（只针对视频）:" << acc->width << "," << acc->height;
		LOG << "像素格式（只针对视频）:" << acc->pix_fmt;
		LOG << "采样率（只针对音频）:" << acc->sample_rate;
		LOG << "采样格式（只针对音频）:" << acc->sample_fmt;
		LOG << "声道数（只针对音频）:" << acc->channels;
		
		if (acc->codec_type == AVMEDIA_TYPE_VIDEO)//视频
		{
			m_vidioStream = i;
			AVCodec* codec = avcodec_find_decoder(acc->codec_id);
			LOG << "解码器信息：";
			LOG << "编解码器名称:" << codec->name;
			LOG << "编解码器长名称:" << codec->long_name;
			LOG << "编解码器类型:" << codec->type;
			LOG << "编解码器ID:" << codec->id;
			if (!codec)
			{
				LOG << "查找解码器失败";
				return false;
			}
			int ret = avcodec_open2(acc,codec,NULL);//打开解码器
			if (ret != 0)
			{
				LOG << "打开解码器失败";
				return false;
			}
		}else if (acc->codec_type == AVMEDIA_TYPE_AUDIO)//音频
		{
			m_audioStream = i;
			AVCodec* codec = avcodec_find_decoder(acc->codec_id);
			if (!codec)
			{
				LOG << "查找解码器失败";
				return false;
			}

			int ret = avcodec_open2(acc, codec, NULL);//打开解码器
			if (ret != 0)
			{
				LOG << "打开解码器失败";
				return false;
			}
			MyAudio::getInstance()->sampleRate = acc->sample_rate;
			MyAudio::getInstance()->sampleSize = acc->bits_per_coded_sample;
			MyAudio::getInstance()->channel = acc->channels;
		}
	}
	return true;
}

AVFrame* MyFFmpeg::decodeFrame(const AVPacket* pack)
{
	QMutexLocker locker(&mut);
	if (!m_afc)
	{
		LOG << "编解码上下文为空";
		return NULL;
	}
	AVFrame*frame = av_frame_alloc();
	if (pack->stream_index == m_audioStream)
	{
	}
	int ret = avcodec_send_packet(m_afc->streams[pack->stream_index]->codec, pack);
	if (ret != 0)
	{
		LOG << "解码帧失败";
		return NULL;
	}
	ret = avcodec_receive_frame(m_afc->streams[pack->stream_index]->codec, frame);
	if (ret != 0)
	{
		LOG << "解码帧失败";
		return NULL;
	}
	return frame;
}

AVPacket* MyFFmpeg::readFrame()
{
	QMutexLocker locker(&mut);
	AVPacket* packet = av_packet_alloc();
	memset(packet, 0, sizeof(AVPacket));
	if (!m_afc)
	{
		//LOG << "上下文为空";
		return packet;
	}

	int ret = av_read_frame(m_afc, packet);
	if (ret != 0)
	{
		//LOG << "读取压缩帧失败";
	}
	return packet;
}

bool MyFFmpeg::YuvToRGB(char *out, int outwidth, int outheight, AVFrame* frame)
{
	QMutexLocker locker(&mut);
	if (!m_afc||!frame) //转换前视频一定是打开的
	{
		return false;
	}

	AVCodecContext* acc = m_afc->streams[m_vidioStream]->codec;
	m_cCtx = sws_getCachedContext(m_cCtx,acc->width, acc->height,acc->pix_fmt,
										outwidth, outheight,AV_PIX_FMT_BGRA,SWS_BICUBIC,NULL, NULL, NULL);
	if (m_cCtx)
	{
		//成功
	}

	uint8_t* data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t*)out;//指针传值，形参的值会被改变
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;// 每行转码的宽度

	int h = sws_scale(m_cCtx, frame->data, frame->linesize, 0, acc->height,
		data, linesize);
}

int MyFFmpeg::ToPCM(char *out, AVFrame* frame)
{
	QMutexLocker locker(&mut);
	if (!m_afc || !out || !frame)
	{
		return 0;
	}
	AVCodecContext* acc = m_afc->streams[m_audioStream]->codec;
	if (m_aCtx == NULL)
	{
		m_aCtx = swr_alloc();
		swr_alloc_set_opts(m_aCtx,
			acc->channel_layout,AV_SAMPLE_FMT_S16,acc->sample_rate,
			acc->channels,acc->sample_fmt,acc->sample_rate,
			0, 0);
		swr_init(m_aCtx);
	}

	uint8_t * data[1];
	data[0] = (uint8_t *)out;
	int len = swr_convert(m_aCtx, data, frame->nb_samples, (const uint8_t**)frame->data, frame->nb_samples);
	if (len <= 0)
	{
		return 0;
	}

	int outsize = av_samples_get_buffer_size(frame->linesize, acc->channels, frame->nb_samples, AV_SAMPLE_FMT_S16, 0);

	//swr_free(&m_aCtx);
	return outsize;
}
