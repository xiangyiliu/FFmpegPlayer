#include "FFmpegQTGUItest.h"
#include "include.h"
#include <QDateTime>
#pragma execution_character_set("utf-8")

#define bufferSize 2*4096
QMutex audioLock;
QMutex videoLock;
QQueue<AVFrame*> audioframeList;	//音频帧
QQueue<AVFrame*> videoframeList;	//视频帧

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
	
	//打开线程
	//m_thread.start();
	workthread.start();
	m_worker.moveToThread(&workthread);
	QThread::create([this]() {
		
		while (true)
		{
			//int totalsize = 0;
			//char* currentPtr = voice;//当前指针 
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
				////读取音频
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
				char* currentPtr = voice;//当前指针 
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
	m_fileName = QFileDialog::getOpenFileName(NULL, "打开文件", NULL, "");
	if (m_fileName.length()<=0)
	{
		return;
	}
	ui.label->setText(m_fileName);
	MyFFmpeg::getInstance()->openVidio(m_fileName.toLocal8Bit());
	MyFFmpeg::getInstance()->m_Isplay = true;
	//打开IO
	MyAudio::getInstance()->Start();
	ui.pushButton_2->setText("暂停");
}

void FFmpegQTGUItest::OnPlay()
{
	if (ui.pushButton_2->text() == "暂停")
	{
		MyFFmpeg::getInstance()->m_Isplay = false; //线程阻塞，视频暂停
		ui.pushButton_2->setText("播放");
	}
	else
	{
		MyFFmpeg::getInstance()->m_Isplay = true;  //线程运行，视频播放
		ui.pushButton_2->setText("暂停");
	}
}

void FFmpegQTGUItest::handleAddDM()
{
	emit newDMessage();
}

void FFmpegQTGUItest::handleNewFrame(AVFrame* frame, int format)
{

	//视频流的帧
	if (format == 0)
	{
		QMutexLocker locker(&videoLock);
		videoframeList.push_back(frame);
		//ui.label_2->setframe(frame);
		//ui.label_2->repaint();
		//LOG << QTime::currentTime();
	}
	//音频流的帧
	else if (format == 1) 
	{
		QMutexLocker locker(&audioLock);
		audioframeList.push_back(frame);
		////读取音频
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