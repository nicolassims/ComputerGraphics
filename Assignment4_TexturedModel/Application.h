#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Application : public QMainWindow {//the actual application. This is where everything runs.
public:
	Application(QWidget* parent = 0, std::string objFilename = "");

private:
	void buildGui(std::string objFilename);
};
