#include "FFmpegQTGUItest.h"
#include "include.h"
#include <QDateTime>
#pragma execution_character_set("utf-8")

#define bufferSize 2*4096
QMutex audioLock;
QMutex videoLock;
QQueue<AVFrame*> audioframeList;	//��Ƶ֡
QQueue<AVFrame*> videoframeList;	//��Ƶ֡

FFmpegQTGUItest::FFmpegQTGUItest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	LOG << QThread::currentThreadId();
}

void FFmpegQTGUItest::init()
{
	m_fileName = "";
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnOpenfile()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(OnPlay()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(handleAddDM()));
	connect(this, &FFmpegQTGUItest::startdecode, &m_worker, &worker::decode,Qt::QueuedConnection);
	connect(&m_worker, &worker::newFrame, this, &FFmpegQTGUItest::handleNewFrame,Qt::QueuedConnection);
	connect(this, &FFmpegQTGUItest::newDMessage,this,&FFmpegQTGUItest::handleDMessage);
	
	//���߳�
	//m_thread.start();
	workthread.start();
	m_worker.moveToThread(&workthread);
	QThread::create([this]() {
		
		while (true)
		{
			//int totalsize = 0;
			//char* currentPtr = voice;//��ǰָ�� 
			//while (totalsize < bufferSize && bufferSize-totalsize >4096+1)
			//{
			//	QMutexLocker locker(&audioLock);
			//	if (audioframes.count()<=0)
			//	{
			//		Sleep(1);
			//		continue;
			//	}
			//	auto frame = audioframes.at(0);
			//	int size = ffmanager->ToPCM(currentPtr, frame);
			//	currentPtr += size;
			//	totalsize += size;
			//	audioframes.removeAt(0);
			//}
			//QMutexLocker locker(&audioLock);
			if (!audioframeList.isEmpty())
			{
				//auto frame = audioframeList.dequeue();
				////��ȡ��Ƶ
				//char voice[2048 * 2];
				//int size = ffmanager->ToPCM(voice, frame);
				//if (size)
				//{
				//	MyAudio::getInstance()->Write(voice, size);
				//	auto frameDuration = frame->pkt_pts - lastAudioFramePts;
				//	lastAudioFramePts = frame->pkt_pts;
				//	double mduration = frameDuration / MyFFmpeg::getInstance()->getAudioTimeBase() * 1000;
				//	Sleep(mduration/*>3? mduration-3 : mduration*/);
				//	LOG << "duration:"<<mduration;
				//	LOG << "frame->pkt_pts:" << frame->pkt_pts / MyFFmpeg::getInstance()->getAudioTimeBase() * 1000;
				//}
				//av_frame_free(&frame);
				char voice[bufferSize];
				int totalsizes = 0;
				double totalduration = 0;
				char* currentPtr = voice;//��ǰָ�� 
				while (totalsizes < bufferSize && bufferSize - totalsizes >4096 + 1)
				{
		
					if (audioframeList.isEmpty())
					{
						Sleep(1);
						continue;
					}
					auto frame = audioframeList.dequeue();
					uint size = ffmanager->ToPCM(currentPtr, frame);
					auto frameDuration = 1024;//frame->pkt_pts - lastAudioFramePts;
					lastAudioFramePts = frame->pkt_pts;
					auto mduration = frameDuration / MyFFmpeg::getInstance()->getAudioTimeBase() * 1000;
					totalduration += mduration;
					currentPtr += size;
					totalsizes += size;
					av_frame_free(&frame);
				}
				MyAudio::getInstance()->Write(voice, totalsizes);
				Sleep(totalduration);
			}
			else
			{
				Sleep(1);
			}
		}
	})->start();
	emit startdecode();
}

void FFmpegQTGUItest::OnOpenfile()
{
	m_fileName = QFileDialog::getOpenFileName(NULL, "���ļ�", NULL, "");
	if (m_fileName.length()<=0)
	{
		return;
	}
	ui.label->setText(m_fileName);
	MyFFmpeg::getInstance()->openVidio(m_fileName.toLocal8Bit());
	MyFFmpeg::getInstance()->m_Isplay = true;
	//��IO
	MyAudio::getInstance()->Start();
	ui.pushButton_2->setText("��ͣ");
}

void FFmpegQTGUItest::OnPlay()
{
	if (ui.pushButton_2->text() == "��ͣ")
	{
		MyFFmpeg::getInstance()->m_Isplay = false; //�߳���������Ƶ��ͣ
		ui.pushButton_2->setText("����");
	}
	else
	{
		MyFFmpeg::getInstance()->m_Isplay = true;  //�߳����У���Ƶ����
		ui.pushButton_2->setText("��ͣ");
	}
}

void FFmpegQTGUItest::handleAddDM()
{
	emit newDMessage();
}

void FFmpegQTGUItest::handleNewFrame(AVFrame* frame, int format)
{

	//��Ƶ����֡
	if (format == 0)
	{
		QMutexLocker locker(&videoLock);
		videoframeList.push_back(frame);
		//ui.label_2->setframe(frame);
		//ui.label_2->repaint();
		//LOG << QTime::currentTime();
	}
	//��Ƶ����֡
	else if (format == 1) 
	{
		QMutexLocker locker(&audioLock);
		audioframeList.push_back(frame);
		////��ȡ��Ƶ
		//char voice[2048 * 2];
		//int size = ffmanager->ToPCM(voice, frame);
		//if (size)
		//{
		//	LOG << QTime::currentTime();
		//	MyAudio::getInstance()->Write(voice, size);
		//}
	}
	av_frame_free(&frame);
}

void FFmpegQTGUItest::handleDMessage()
{
	DMessage* d = new DMessage(this);
	d->setText("test11");
}