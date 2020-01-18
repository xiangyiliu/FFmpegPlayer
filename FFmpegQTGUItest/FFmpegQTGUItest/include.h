#pragma once

#include <QFileDialog>

extern "C"
{
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/dict.h"
}
#pragma comment (lib,"lib/avformat.lib")
#pragma comment (lib,"lib/avutil.lib")
#pragma comment (lib,"lib/avcodec.lib")
#pragma comment (lib,"lib/swscale.lib")
#pragma comment (lib,"lib/avdevice.lib")
#pragma comment (lib,"lib/postproc.lib")
#pragma comment (lib,"lib/avfilter.lib")
#pragma comment (lib,"lib/swresample.lib")

#include <QDebug>
#pragma execution_character_set("utf-8")
#define  LOG (qDebug()<<__FUNCTION__<<__LINE__)
#include <QThread>

#include "DMessage.h"
#include "worker.h"
#include "MyFFmpeg.h"


