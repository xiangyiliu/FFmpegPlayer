#include "FFmpegQTGUItest.h"
#include "include.h"

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
	connect(&m_worker, &worker::newPacket, this, &FFmpegQTGUItest::handleNewPacket,Qt::QueuedConnection);
	connect(this, &FFmpegQTGUItest::newDMessage,this,&FFmpegQTGUItest::handleDMessage);
	
	//打开线程
	//m_thread.start();
	workthread.start();
	m_worker.moveToThread(&workthread);
	emit startdecode();
}

void FFmpegQTGUItest::OnOpenfile()
{
	m_fileName = QFileDialog::getOpenFileName(NULL, QString::fromLocal8Bit("打开文件"), NULL, "");
	if (m_fileName.length()<=0)
	{
		return;
	}
	ui.label->setText(m_fileName);
	MyFFmpeg::getInstance()->openVidio(m_fileName.toLocal8Bit());
	MyFFmpeg::getInstance()->m_Isplay = true;

	ui.pushButton_2->setText(QString::fromLocal8Bit("暂停"));
}

void FFmpegQTGUItest::OnPlay()
{
	if (ui.pushButton_2->text() == QString::fromLocal8Bit("暂停"))
	{
		MyFFmpeg::getInstance()->m_Isplay = false; //线程阻塞，视频暂停
		ui.pushButton_2->setText(QString::fromLocal8Bit("播放"));
	}
	else
	{
		MyFFmpeg::getInstance()->m_Isplay = true;  //线程运行，视频播放
		ui.pushButton_2->setText(QString::fromLocal8Bit("暂停"));
	}
}

void FFmpegQTGUItest::handleAddDM()
{
	emit newDMessage();
}

void FFmpegQTGUItest::handleNewPacket(AVPacket* packet)
{
	Sleep(33);
	AVFrame* frame = MyFFmpeg::getInstance()->decodeFrame(packet);
	if (!frame)
	{
		return;
	}
	LOG << "pts:" << frame->pkt_pts / 44100;
	LOG << "dts:" << frame->pkt_dts / 44100;
	if (packet->stream_index == MyFFmpeg::getInstance()->getaudiostreamIndex())
	{
		ui.label_2->setframe(frame);
		ui.label_2->update();
	}
	else
	{
		//读取音频
		char voice[2048];
		int size = MyFFmpeg::getInstance()->ToPCM(voice,frame);
		if (size)
		{
			MyAudio::getInstance()->Write(voice, size);
		}
	}
	av_frame_free(&frame);
	av_packet_free(&packet);
}

void FFmpegQTGUItest::handleDMessage()
{
	DMessage* d = new DMessage(this);
	d->setText("test11");
}