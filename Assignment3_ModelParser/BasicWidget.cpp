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
	if (keyEvent->key() == Qt::Key_Left) {
		qDebug() << "Left Arrow Pressed";
		update();  // We call update after we handle a key press to trigger a redraw when we are ready
	} else if (keyEvent->key() == Qt::Key_Right) {
		qDebug() << "Right Arrow Pressed";
		update();  // We call update after we handle a key press to trigger a redraw when we are ready
	} else if (keyEvent->key() == Qt::Key_W) {
		qDebug() << "W Pressed";
		wireframe = !wireframe;
		update();  // We call update after we handle a key press to trigger a redraw when we are ready
	} else {
		qDebug() << "You Pressed an unsupported Key!";
	}
  // ENDTODO
}
void BasicWidget::initializeGL() {

  makeCurrent();
  initializeOpenGLFunctions();

  // All of our matrices should be set to identity for now.
  model_.setToIdentity();
  view_.setToIdentity();
  projection_.setToIdentity();

  QOpenGLContext* curContext = this->context();
  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  // Set up our shaders.
  createShader();

  //Array of vertices
  static GLfloat verts[fr.getVertices().size()] = fr.getVertices();

  //Array of indices
  static GLuint idx[fr.getIndices().size()] = fr.getIndices();

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
	  std::cout << normals[i] << ", ";
  }

  auto vertices = fr.getVertices();
  std::cout << std::endl << "Printing vertices:" << std::endl;
  for (int i = 0; i < vertices.size(); i++) {
	  std::cout << vertices[i] << ", ";
  }
  //THE PRIOR CODE IS INCLUDED ONLY FOR TESTING PURPOSES //FIX THIS

  shaderProgram_.bind();

// Note - use the vbo_ member provided
vbo_.create();
vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
vbo_.bind();
vbo_.allocate(verts_colors, (3 * 3 * sizeof(GL_FLOAT)) + (4 * 3 * sizeof(GL_FLOAT)));

ibo_.create();
ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
ibo_.bind();
ibo_.allocate(idx, 3 * sizeof(GL_UNSIGNED_INT));

// Create a VAO to keep track of things for us.
vao_.create();
vao_.bind();
vbo_.bind();

shaderProgram_.enableAttributeArray(0);
shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 7 * sizeof(GL_FLOAT));

shaderProgram_.enableAttributeArray(1);
shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GL_FLOAT), 4, 7 * sizeof(GL_FLOAT));

ibo_.bind();
// Release the vao THEN the vbo
vao_.release();
shaderProgram_.release();

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

  glPolygonMode(GL_FRONT_AND_BACK, !wireframe ? GL_FILL : GL_LINE);

  // TODO:  render.
  shaderProgram_.bind();
  vao_.bind();
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  vao_.release();
  shaderProgram_.release();
}
