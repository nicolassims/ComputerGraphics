#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <Vector>

#include "FileReader.h"//INCLUDED HERE ONLY FOR TESTING PURPOSES. //FIX THIS

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:
	bool wireframe = false;
	FileReader fr = FileReader("../../objects/cube.obj");//INCLUDED HERE ONLY FOR TESTING PURPOSES. //FIX THIS

protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
