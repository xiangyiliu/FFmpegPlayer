/*
**                      自定义音频解码类
**int sampleRate = 48000;   采样率，每秒采样次数
**int sampleSize = 16;		采样大小，每次采样的数据所占位大小
**int channel	 = 2;		通道数，常见的单声道和立体声（双声道）
*/
#pragma once
#include <QAudioOutput>
#include <QMutex>
class MyAudio
{
protected:
	MyAudio();
public:
	static MyAudio* getInstance()
	{
		static MyAudio m_Audio;
		return &m_Audio;
	}
	~MyAudio();

	void Stop();
	bool Start();
	void Play(bool isPlay);
	bool Write(const char *data, int datasize);
	int GetFree();

	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;

public:
	QAudioOutput *output = NULL;			//音频输出
	QIODevice *io = NULL;					//本地IO设备
	QMutex mutex;
};

