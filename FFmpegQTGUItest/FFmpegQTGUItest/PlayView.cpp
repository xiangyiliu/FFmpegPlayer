#include "PlayView.h"



PlayView::PlayView()
{
	
}


PlayView::PlayView(QWidget* parent)
{
	this->setParent(parent);
	//startTimer(10);
}

PlayView::~PlayView()
{
}

void PlayView::setframe(AVFrame*f)
{
	m_frame = f;
}

void PlayView::paintEvent(QPaintEvent*e)
{
	static QImage* image;

	if (image == nullptr)
	{
		//视频是YVU四通道的类型
		uchar* buf = new uchar[width()*height() * 4];
		image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
	}

	bool ret = MyFFmpeg::getInstance()->YuvToRGB((char*)image->bits(), width(), height(),m_frame);
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), *image);
}

void PlayView::timerEvent(QTimerEvent *e)
{
	this->update();
}
