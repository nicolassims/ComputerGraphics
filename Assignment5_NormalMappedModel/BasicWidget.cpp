#include "BasicWidget.h"
#include "FileReader.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent, std::string objFilename) : QOpenGLWidget(parent) {
	objFilename_ = objFilename;
	setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget() {
	for (auto renderable : displayables_) {
		delete renderable;
	}
	displayables_.clear();
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
	// Handle key events here.
	if (keyEvent->key() == Qt::Key_Q) {
		qDebug() << "q pressed. Exiting application";
		exit(0);
		update();
	} else if (keyEvent->key() == Qt::Key_W) {
		qDebug() << "w pressed. Toggling wireframe mode.";
		fillmode = !fillmode;
		update();
	} else {
		qDebug() << "You Pressed an unsupported Key!";
	}
}
void BasicWidget::initializeGL() {
	makeCurrent();
	initializeOpenGLFunctions();

	FileReader obj = FileReader(objFilename_);
	QString texFile = QString::fromStdString(obj.formattedName);
	QVector<QVector3D> pos;
	QVector<QVector2D> texCoord;
	QVector<unsigned int> idx;

	for (int i = 0; i < obj.combinedPositionData.size(); i += 3) {
		pos << QVector3D(obj.combinedPositionData[i], obj.combinedPositionData[i + 1], obj.combinedPositionData[i + 2]);
	}
	for (int i = 0; i < obj.combinedTextureData.size(); i += 2) {
		texCoord << QVector2D(obj.combinedTextureData[i], obj.combinedTextureData[i + 1]);
	}
	for (int i = 0; i < obj.combinedIndexes.size(); i++) {
		idx << obj.combinedIndexes[i];
	}

	Displayable* ren1 = new Displayable();
	ren1->init(pos, texCoord, idx, texFile);

	displayables_.push_back(ren1);
	glViewport(0, 0, width(), height());
	frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	view_.setToIdentity();
	view_.lookAt(QVector3D(5.0f, 0.0f, 2.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
	projection_.setToIdentity();
	projection_.perspective(70.f, (float)w / (float)h, 0.001, 1000.0);
	glViewport(0, 0, w, h);
}

void BasicWidget::paintGL() {
	qint64 msSinceRestart = frameTimer_.restart();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, fillmode ? GL_FILL : GL_LINE);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto displayable : displayables_) {
		displayable->draw(view_, projection_);
	}
	update();
}
