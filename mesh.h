#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include<QString>
#include<QVector>
#include<QOpenGLFunctions>
#include<QOpenGLShaderProgram>
#include<QOpenGLVertexArrayObject>
#include<QOpenGLBuffer>

struct Vertex
{
    // position
    QVector3D Position;
    // normal
    QVector3D Normal;
    // texCoords
    QVector3D TexCoords;
    // tangent
    QVector3D Tangent;
    // bitangent
    QVector3D Bitangent;
};

class Mesh :protected QOpenGLFunctions
{
public:
    QVector<Vertex>       vertices;
    QVector<unsigned int> indices;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer EBO;
public:
    Mesh(QVector<Vertex> vertices, QVector<unsigned int> indices);
    void Draw(QOpenGLShaderProgram& shader);
    ~Mesh();
private:
    QOpenGLBuffer VBO;
private:
    void setupMesh();
};

#endif // MESH_H
