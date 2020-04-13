#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include "Displayable.h"

class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions {//Basic OpenGL Widget. Gives access to OpenGL functions.
private:
	bool fillmode = true;
	std::string objFilename_;
	QMatrix4x4 model_;
	QMatrix4x4 view_;
	QMatrix4x4 projection_;
	QElapsedTimer frameTimer_;
	QVector<Displayable*> displayables_;

protected:
	QOpenGLShaderProgram shaderProgram_;

	void keyReleaseEvent(QKeyEvent* keyEvent) override;//interaction overrides
	void initializeGL() override;//QOpenGLWidget overrides 
	void resizeGL(int w, int h) override;
	void paintGL() override;

public:
	BasicWidget(QWidget* parent = nullptr, std::string objFilename = "");
	virtual ~BasicWidget();

	QSize sizeHint() const { return QSize(1280, 920); }
};
