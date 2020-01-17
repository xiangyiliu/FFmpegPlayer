#include "include.h"
#include "FFmpegQTGUItest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FFmpegQTGUItest w;
	w.show();
	return a.exec();
}
