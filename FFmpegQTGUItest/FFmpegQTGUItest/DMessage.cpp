#include "DMessage.h"

DMessage::DMessage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
	ui.label->setStyleSheet("background-color:black");

	QWidget* pa = (QWidget*)this->parent();
	int H = pa->height();
	int W = pa->width();
	this->setGeometry(W, rand() % H, 200, 100);

	connect(&moveTimer, &QTimer::timeout, this, [this]() {
		QWidget* parent = (QWidget*)this->parent();
		int H = parent->height();
		int W = parent->width();
		this->move(this->x()-1, this->y());
		QRect rc =this->geometry();
		if (rc.right()<0)
		{
			this->moveTimer.stop();
			this->deleteLater();
		}
		
	});
	moveTimer.start(100);
}

DMessage::~DMessage()
{
}
void DMessage::setText(QString text)
{
	ui.label->setText(text);
}