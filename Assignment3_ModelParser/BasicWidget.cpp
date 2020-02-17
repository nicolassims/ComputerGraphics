#include "BasicWidget.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
}

//////////////////////////////////////////////////////////////////////
// Privates

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
  // TODO
  // Handle key events here.
  qDebug() << "You Pressed an unsupported Key!";
  // ENDTODO
}
void BasicWidget::initializeGL() {

  makeCurrent();
  initializeOpenGLFunctions();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  //THE FOLLOWING CODE IS INCLUDED ONLY FOR TESTING PURPOSES //FIX THIS
  auto indices = fr.getIndices();
  std::cout << std::endl << "Printing indices:" << std::endl;
  for (int i = 0; i < indices.size(); i++) {
	  std::cout << indices[i] << ", ";
  }

  auto lines = fr.getLines();
  std::cout << std::endl << "Printing lines:" << std::endl;
  for (int i = 0; i < lines.size(); i++) {
	  std::cout << lines[i] << ", ";
  }

  auto normals = fr.getNormals();
  std::cout << std::endl << "Printing normals:" << std::endl;
  for (int i = 0; i < normals.size(); i++) {
	  std::cout << "(" << normals[i].x << " " << normals[i].y << " " << normals[i].z << "), ";
  }

  auto vertices = fr.getVertices();
  std::cout << std::endl << "Printing vertices:" << std::endl;
  for (int i = 0; i < vertices.size(); i++) {
	  std::cout << "(" << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << "), ";
  }
  //THE PRIOR CODE IS INCLUDED ONLY FOR TESTING PURPOSES //FIX THIS

  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TODO:  render.
}
