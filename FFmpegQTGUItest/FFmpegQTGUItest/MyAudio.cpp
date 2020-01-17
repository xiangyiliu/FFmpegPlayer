#include "MyAudio.h"



MyAudio::MyAudio()
{
}


MyAudio::~MyAudio()
{
}

void MyAudio::Stop()
{
	mutex.lock();
	if (output)
	{
		//Stops the audio output, detaching from the system resource.
		output->stop();
		delete output;
		output = NULL;
		io = NULL;
	}
	mutex.unlock();
}

bool MyAudio::Start()
{
	this->Stop();
	mutex.lock();
	QAudioFormat format;//qt�Դ�����Ƶ��ʽ��
	format.setSampleRate(this->sampleRate);
	format.setSampleSize(this->sampleSize);
	format.setChannelCount(this->channel);
	format.setCodec("audio/pcm");//��Ƶ��ʽ
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::UnSignedInt);//��������

	output = new QAudioOutput(format);
	io = output->start();//Returns a pointer to the internal QIODevice being used to transfer data to the system's audio output. The device will already be open and write() can write data directly to it. Note: The pointer will become invalid after the stream is stopped or if you start another stream.
	mutex.unlock();
	return true;
}

void MyAudio::Play(bool isPlay)
{
	mutex.lock();
	if (!output)
	{
		mutex.unlock();
		return;
	}

	if (isPlay)
	{
		output->resume();//�ָ�
	}
	else
	{
		output->suspend();//����
	}
	mutex.unlock();
}

bool MyAudio::Write(const char *data, int datasize)
{
	if (!data || datasize<=0)
	{
		return false;
	}

	mutex.lock();
	if (io)
	{
		mutex.unlock();
		io->write(data, datasize);
		return true;
	}
	mutex.unlock();
	return false;
}

int MyAudio::GetFree()
{
	mutex.lock();
	if (!output)
	{
		mutex.unlock();
		return 0;
	}

	int free = output->bytesFree();
	mutex.unlock();
	return free;
}
