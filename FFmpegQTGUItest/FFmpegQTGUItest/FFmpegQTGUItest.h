#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FFmpegQTGUItest.h"
#include "PalyThread.h"
#include "include.h"
#include <windows.h>
class FFmpegQTGUItest : public QMainWindow
{
	Q_OBJECT

public:
	FFmpegQTGUItest(QWidget *parent = Q_NULLPTR);

private:
	Ui::FFmpegQTGUItestClass ui;
	QString m_fileName;
	PalyThread m_thread;		//≤•∑≈œﬂ≥Ã
	QThread workthread;			//
	worker m_worker;			
	MyFFmpeg* ffmanager = MyFFmpeg::getInstance();
private:
	void init();
public slots:
	void OnOpenfile();
	void OnPlay();
	void handleAddDM();
	void handleNewFrame(AVFrame* frame,int format);
	void handleDMessage();
signals:
	void startdecode();
	void newDMessage();
};
