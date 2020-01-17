#pragma once
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include "MyFFmpeg.h"
#include "MyAudio.h"
class PlayView : public QLabel
{
public:
	PlayView(QWidget* parent);
	PlayView();
	void setframe(AVFrame*f);
	~PlayView();
private:
	void paintEvent(QPaintEvent*e);
	void timerEvent(QTimerEvent *e);
private:
	AVFrame* m_frame= NULL;
};

