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
	AVFormatContext* m_afc;			//��������Ϣ������
	int m_vidioStream;				//��Ƶ���
	int m_audioStream;				//��Ƶ���
	SwsContext *m_cCtx = NULL; //��Ƶת����
	SwrContext *m_aCtx = NULL; //��Ƶת����
private:
	void init();
public:
	bool m_Isplay;					//���Ʋ���
	qint64 getVideoDuration();
	qint64 getAudioDuration();
	double getVideoTimeBase();
	double getAudioTimeBase();
	double getVideoFrameRate();
	double getAudioFrameRate();
	//��ȡ�������������
	AVFormatContext* getFormatContext();	
	//
	static MyFFmpeg* getInstance();
	//��Ƶ�����
	int getaudiostreamIndex();
	//��Ƶ�����
	int getVideoStreamIndex();
	bool openVidio(const char* fileName);
	AVFrame* decodeFrame(const AVPacket* pack); //����ѹ����֡
	AVPacket* readFrame();					//�ӽ������ж�ȡ֡
	bool YuvToRGB(char *out, int outweight, int outheight,AVFrame* frame);//����ת����Ϊ��ʾ��׼�� ת�봦������Ƶ��YUV, RGB��ɫ�ȵ���ͨ��, ������Ҫ����ת����RGB������ʾ��
	int ToPCM(char *out, AVFrame* frame); //��Ƶ����
};

