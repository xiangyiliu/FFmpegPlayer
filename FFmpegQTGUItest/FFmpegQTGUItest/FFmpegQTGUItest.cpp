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
	
	//���߳�
	//m_thread.start();
	workthread.start();
	m_worker.moveToThread(&workthread);
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
		ui.label_2->setframe(frame);
		ui.label_2->repaint();
	}
	//��Ƶ����֡
	else if (format == 1) 
	{
		//��ȡ��Ƶ
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