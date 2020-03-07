#include "FFmpegQTGUItest.h"
#include "include.h"
#include <QDateTime>
#pragma execution_character_set("utf-8")

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
		ui.label_2->setframe(frame);
		ui.label_2->repaint();
	}
	//音频流的帧
	else if (format == 1) 
	{
		//读取音频
		char voice[2048*2];
		DWORD start =  ::GetTickCount();
		int size = ffmanager->ToPCM(voice, frame);
		if (size)
		{
			LOG << "ToPCM cost time:" <<::GetTickCount()-start;
			MyAudio::getInstance()->Write(voice, size);
		}
		
	}
	av_frame_free(&frame);
}

void FFmpegQTGUItest::handleDMessage()
{
	DMessage* d = new DMessage(this);
	d->setText("test11");
}