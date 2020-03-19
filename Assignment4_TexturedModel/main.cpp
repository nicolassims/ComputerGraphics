/**
 * Support code written by Erik W. Anderson
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include "Application.h"

int main(int argc, char** argv) {
	if (argc != 2) {//If no argument is provided, or two many are, then it defaults to displaying the house model, largely for testing purposes.
		argv[1] = "../../objects/house/house_obj.obj";
	}
	QApplication a(argc, argv);
	QString appDir = a.applicationDirPath();
	QDir::setCurrent(appDir);

	QSurfaceFormat fmt;
	fmt.setDepthBufferSize(24);
	fmt.setStencilBufferSize(8);
	fmt.setVersion(3, 3);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(fmt);

	std::string objFilename(argv[1]);
	Application app(0, objFilename);
	app.show();
	return QApplication::exec();
}
