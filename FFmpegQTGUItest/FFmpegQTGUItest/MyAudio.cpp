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
	QAudioFormat format;//qt自带的音频格式类
	format.setSampleRate(this->sampleRate);
	format.setSampleSize(this->sampleSize);
	format.setChannelCount(this->channel);
	format.setCodec("audio/pcm");//音频格式
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::UnSignedInt);//样本类型

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
		output->resume();//恢复
	}
	else
	{
		output->suspend();//挂起
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
