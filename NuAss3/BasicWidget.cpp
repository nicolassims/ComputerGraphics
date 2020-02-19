#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), logger_(this)
{
  setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
  vbo_.release();
  vbo_.destroy();
  ibo_.release();
  ibo_.destroy();
  vao_.release();
  vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
  QString str =
    "#version 330\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec4 color;\n"

    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 projectionMatrix;\n"

    "out vec4 vertColor;\n"

    "void main()\n"
    "{\n"
    "  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);\n"
    "  vertColor = color;\n"
    "}\n";
  return str;
}

QString BasicWidget::fragmentShaderString() const
{
  QString str =
	"#version 330\n"
    "in vec4 vertColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"  color = vertColor;\n"
	"}\n";
  return str;
}

void BasicWidget::createShader()
{
  QOpenGLShader vert(QOpenGLShader::Vertex);
  vert.compileSourceCode(vertexShaderString());
  QOpenGLShader frag(QOpenGLShader::Fragment);
  frag.compileSourceCode(fragmentShaderString());
  bool ok = shaderProgram_.addShader(&vert);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.addShader(&frag);
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
  ok = shaderProgram_.link();
  if(!ok) {
	qDebug() << shaderProgram_.log();
  }
}
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent) {
	// Handle key events here.
	if (keyEvent->key() == Qt::Key_1) {
		qDebug() << "1 was pressed";
		fr = FileReader("../../objects/bunny.obj");
		auto vertices = fr.getVertices();
		auto indices = fr.getIndices();

		vbo_.bind();
		vbo_.allocate(&vertices[0], vertices.size() * sizeof(GL_FLOAT));

		ibo_.bind();
		ibo_.allocate(&indices[0], indices.size() * sizeof(GL_UNSIGNED_INT));
		update();

	} else if (keyEvent->key() == Qt::Key_2) {
		qDebug() << "2 was pressed";
		fr = FileReader("../../objects/monkey.obj");

		auto vertices = fr.getVertices();
		auto indices = fr.getIndices();

		vbo_.bind();
		vbo_.allocate(&vertices[0], vertices.size() * sizeof(GL_FLOAT));

		ibo_.bind();
		ibo_.allocate(&indices[0], indices.size() * sizeof(GL_UNSIGNED_INT));

		update();
		
	} else if (keyEvent->key() == Qt::Key_W) {
		 qDebug() << (!wireframe ? "Wireframe off" : "Wireframe on");
		 wireframe = !wireframe;
		 update();  // We call update after we handle a key press to trigger a redraw when we are ready
	} else if (keyEvent->key() == Qt::Key_Q) {
		exit(1);
	} else {
		qDebug() << "You Pressed an unsupported Key!";
	}
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

  createShader();

  auto vertices = fr.getVertices();
  auto indices = fr.getIndices();

  shaderProgram_.bind();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.create();

  vbo_.bind();
  vbo_.allocate(&vertices[0], vertices.size() * sizeof(GL_FLOAT));

  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  ibo_.create();
  ibo_.bind();
  ibo_.allocate(&indices[0], indices.size() * sizeof(GL_UNSIGNED_INT));

  vao_.create();
  vao_.bind();
  vbo_.bind();

  shaderProgram_.enableAttributeArray(0);
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
  ibo_.bind();
  vao_.release();
  shaderProgram_.release();

  glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);

  model_ = QMatrix4x4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

  view_.lookAt(QVector3D(0, 0.5f, 3), // Camera is at (0,0.5,3), in World Space
	QVector3D(0, 0.5f, 0), // and looks at a point three units away
	QVector3D(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );

  projection_.perspective(45.0f, (float)w / h, 0.1f, 100.0f);

  shaderProgram_.bind();

  shaderProgram_.setUniformValue("modelMatrix", model_);
  shaderProgram_.setUniformValue("viewMatrix", view_);
  shaderProgram_.setUniformValue("projectionMatrix", projection_);

  shaderProgram_.release();
}

void BasicWidget::paintGL() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaderProgram_.bind();
  vao_.bind();

  if (!wireframe) {//Ternary operator didn't work here
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glDrawElements(GL_TRIANGLES, fr.getIndices().size() * 3, GL_UNSIGNED_INT, 0);
  vao_.release();
  shaderProgram_.release();
}
