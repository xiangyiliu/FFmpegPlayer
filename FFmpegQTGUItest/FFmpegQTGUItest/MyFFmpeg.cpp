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
	LOG << "AVInputFormat ��Ϣ:";
	AVInputFormat* iformat = m_afc->iformat;
	LOG << "��װ��ʽ�ĳ�����:"<< iformat->long_name;
	LOG << "��װ��ʽ����չ��:" << iformat->extensions;
	LOG << "��װ��ʽID:" << iformat->raw_codec_id;
	
	for (int i=0;i< m_afc->nb_streams;i++)
	{
		AVCodecContext* acc = m_afc->streams[i]->codec;
		LOG << "stream��Ϣ��";
		LOG << "ʱ���׼:" << m_afc->streams[i]->time_base.num << "/" << m_afc->streams[i]->time_base.den;
		LOG << "ʱ�䳤��:" << m_afc->streams[i]->duration;
		LOG << "֡��:" << m_afc->streams[i]->avg_frame_rate.num<<"/"<< m_afc->streams[i]->avg_frame_rate.den;

		LOG << "stream"<<i<<"�ı��������������Ϣ��";
		LOG << "ͼ��Ŀ�ߣ�ֻ�����Ƶ��:" << acc->width << "," << acc->height;
		LOG << "���ظ�ʽ��ֻ�����Ƶ��:" << acc->pix_fmt;
		LOG << "�����ʣ�ֻ�����Ƶ��:" << acc->sample_rate;
		LOG << "������ʽ��ֻ�����Ƶ��:" << acc->sample_fmt;
		LOG << "��������ֻ�����Ƶ��:" << acc->channels;
		
		if (acc->codec_type == AVMEDIA_TYPE_VIDEO)//��Ƶ
		{
			m_vidioStream = i;
			AVCodec* codec = avcodec_find_decoder(acc->codec_id);
			LOG << "��������Ϣ��";
			LOG << "�����������:" << codec->name;
			LOG << "�������������:" << codec->long_name;
			LOG << "�����������:" << codec->type;
			LOG << "�������ID:" << codec->id;
			if (!codec)
			{
				LOG << "���ҽ�����ʧ��";
				return false;
			}
			int ret = avcodec_open2(acc,codec,NULL);//�򿪽�����
			if (ret != 0)
			{
				LOG << "�򿪽�����ʧ��";
				return false;
			}
		}else if (acc->codec_type == AVMEDIA_TYPE_AUDIO)//��Ƶ
		{
			m_audioStream = i;
			AVCodec* codec = avcodec_find_decoder(acc->codec_id);
			if (!codec)
			{
				LOG << "���ҽ�����ʧ��";
				return false;
			}

			int ret = avcodec_open2(acc, codec, NULL);//�򿪽�����
			if (ret != 0)
			{
				LOG << "�򿪽�����ʧ��";
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
		LOG << "�����������Ϊ��";
		return NULL;
	}
	AVFrame*frame = av_frame_alloc();
	if (pack->stream_index == m_audioStream)
	{
	}
	int ret = avcodec_send_packet(m_afc->streams[pack->stream_index]->codec, pack);
	if (ret != 0)
	{
		LOG << "����֡ʧ��";
		return NULL;
	}
	ret = avcodec_receive_frame(m_afc->streams[pack->stream_index]->codec, frame);
	if (ret != 0)
	{
		LOG << "����֡ʧ��";
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
		//LOG << "������Ϊ��";
		return packet;
	}

	int ret = av_read_frame(m_afc, packet);
	if (ret != 0)
	{
		//LOG << "��ȡѹ��֡ʧ��";
	}
	return packet;
}

bool MyFFmpeg::YuvToRGB(char *out, int outwidth, int outheight, AVFrame* frame)
{
	QMutexLocker locker(&mut);
	if (!m_afc||!frame) //ת��ǰ��Ƶһ���Ǵ򿪵�
	{
		return false;
	}

	AVCodecContext* acc = m_afc->streams[m_vidioStream]->codec;
	m_cCtx = sws_getCachedContext(m_cCtx,acc->width, acc->height,acc->pix_fmt,
										outwidth, outheight,AV_PIX_FMT_BGRA,SWS_BICUBIC,NULL, NULL, NULL);
	if (m_cCtx)
	{
		//�ɹ�
	}

	uint8_t* data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t*)out;//ָ�봫ֵ���βε�ֵ�ᱻ�ı�
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;// ÿ��ת��Ŀ��

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
