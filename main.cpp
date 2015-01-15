#include <QApplication>

#include "mainWindow.h"
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();

	return app.exec();
}
