/**
 * The primary application code.
 */

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Application : public QMainWindow {
public:
	Application(QWidget* parent = 0, std::string objFilename = "");

private:
	void buildGui(std::string objFilename);
};