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
	QOpenGLVertexArrayObject vao_;
	bool wireframe = false;
	FileReader fr = FileReader("../../objects/cube.obj");
	QMatrix4x4 model_;
	QMatrix4x4 view_;
	QMatrix4x4 projection_;

protected:
	QString vertexShaderString() const;
	QString fragmentShaderString() const;
	QOpenGLShaderProgram shaderProgram_;
	void createShader();
	// Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  QOpenGLBuffer vbo_;
  QOpenGLBuffer ibo_;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();

  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
