/*
**                      �Զ�����Ƶ������
**int sampleRate = 48000;   �����ʣ�ÿ���������
**int sampleSize = 16;		������С��ÿ�β�����������ռλ��С
**int channel	 = 2;		ͨ�����������ĵ���������������˫������
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
	QAudioOutput *output = NULL;			//��Ƶ���
	QIODevice *io = NULL;					//����IO�豸
	QMutex mutex;
};

