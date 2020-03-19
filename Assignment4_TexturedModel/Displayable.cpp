#include <QtGui>
#include <QtOpenGL>
#include "Displayable.h"

Displayable::Displayable() : vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), texture_(QOpenGLTexture::Target2D), idxCount(0), vertexSize_(5) { }

Displayable::~Displayable() {
	if (texture_.isCreated()) {
		texture_.destroy();
	}
	if (vbo_.isCreated()) {
		vbo_.destroy();
	}
	if (ibo_.isCreated()) {
		ibo_.destroy();
	}
	if (vao_.isCreated()) {
		vao_.destroy();
	}
}

void Displayable::createShaders() {
	QString vertexFilename = "../../vert.glsl";//messy, both here and two lines down. Is there a more dynamic way to handles this?
	shader_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
	QString fragmentFilename = "../../frag.glsl";
	shader_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
	shader_.link();
}

void Displayable::init(const QVector<QVector3D>& positions, const QVector<QVector2D>& texCoords, const QVector<unsigned int>& indexes, const QString& textureFile) {
	modelMatrix_.setToIdentity();//Set our model matrix to identity
	if (textureFile != "") {//Load texture, and flip it. (Thanks, Piazza!)
		texture_.setData(QImage(textureFile).mirrored(true, true));
	}
	idxCount = indexes.size();//setting count of indices
	int numVBOEntries = positions.size() * vertexSize_;
	createShaders();//setup our shader
	
	vao_.create();//next few lines handle vertex buffers
	vao_.bind();
	vbo_.create();
	vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);//nothing is changing in the scene right now. But maybe this should be DynamicDraw if I were doing anything else.
	vbo_.bind();
	float* tempVert = new float[numVBOEntries];//create array to be inserted into vbo	
	for (int i = 0; i < positions.size(); ++i) {
		tempVert[i * vertexSize_ + 0] = positions.at(i).x();
		tempVert[i * vertexSize_ + 1] = positions.at(i).y();
		tempVert[i * vertexSize_ + 2] = positions.at(i).z();
		tempVert[i * vertexSize_ + 3] = texCoords.at(i).x();
		tempVert[i * vertexSize_ + 4] = texCoords.at(i).y();
	}
	vbo_.allocate(tempVert, numVBOEntries * sizeof(float));
	delete[] tempVert;//delete temp array
	
	ibo_.create();//create index buffer
	ibo_.bind();
	ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	unsigned int* tempIdx = new unsigned int[indexes.size()];//create array to be inserted into ibo
	for (int i = 0; i < indexes.size(); ++i) {
		tempIdx[i] = indexes.at(i);
	}
	ibo_.allocate(tempIdx, indexes.size() * sizeof(unsigned int));
	delete[] tempIdx;//delete temp array
	
	shader_.enableAttributeArray(0);//wet up shaders
	shader_.setAttributeBuffer(0, GL_FLOAT, 0, 3, vertexSize_ * sizeof(float));
	shader_.enableAttributeArray(1);
	shader_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2, vertexSize_ * sizeof(float));
	
	vao_.release();//release buffers
	vbo_.release();
	ibo_.release();
}

void Displayable::draw(const QMatrix4x4& view, const QMatrix4x4& projection) {
	shader_.bind();
	QMatrix4x4 id;
	id.setToIdentity();
	shader_.setUniformValue("modelMatrix", modelMatrix_);
	shader_.setUniformValue("viewMatrix", view);
	shader_.setUniformValue("projectionMatrix", projection);

	vao_.bind();
	texture_.bind();

	glDrawElements(GL_TRIANGLES, idxCount, GL_UNSIGNED_INT, 0);
	
	texture_.release();
	vao_.release();
	shader_.release();
}