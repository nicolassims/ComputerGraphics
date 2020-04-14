#include "Application.h"
#include "BasicWidget.h"

Application::Application(QWidget* parent, std::string objFilename) : QMainWindow(parent) {
	buildGui(objFilename);
}

void Application::buildGui(std::string objFilename) {
	BasicWidget* widget = new BasicWidget(this, objFilename);//basic widget.
	setCentralWidget(widget);
}