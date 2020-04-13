#pragma once

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

class Displayable {
protected:
	QMatrix4x4 modelMatrix_;//The matrix used to keep track of the displayable's model
	QOpenGLShaderProgram shader_;//the displayable's shader
	QOpenGLTexture texture_;//the displayable's texture
	QOpenGLBuffer vbo_;//vertex buffer
	QOpenGLBuffer ibo_;//index  buffer
	QOpenGLVertexArrayObject vao_;//used during the draw call
	unsigned int idxCount;//Do you _really_ need documentation for this one?
	int vertexSize_;//position + texCoord
	void createShaders();//create shader

public:
	Displayable();
	virtual ~Displayable();
	virtual void init(const QVector<QVector3D>& positions, const QVector<QVector2D>& texCoords, const QVector<unsigned int>& indexes, const QString& textureFile);
	virtual void draw(const QMatrix4x4& view, const QMatrix4x4& projection);
};