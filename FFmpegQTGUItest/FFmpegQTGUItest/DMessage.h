#pragma once

#include <QWidget>
#include "ui_DMessage.h"
#include <QLabel>
#include <QTimer>

class DMessage : public QWidget
{
	Q_OBJECT

public:
	DMessage(QWidget *parent = Q_NULLPTR);
	~DMessage();
	void setText(QString text);
private:
	Ui::DMessage ui;
	QTimer moveTimer;
};
