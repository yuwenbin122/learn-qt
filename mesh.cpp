#include "mesh.h"

Mesh::Mesh(QVector<Vertex> vertices, QVector<unsigned int> indices) :
    VBO(QOpenGLBuffer::VertexBuffer),
    EBO(QOpenGLBuffer::IndexBuffer)
{
    this->initializeOpenGLFunctions();
    this->vertices = vertices;
    this->indices = indices;
    setupMesh();
}

Mesh::~Mesh()
{
    VBO.destroy();
    EBO.destroy();
    VAO.destroy();
}

void Mesh::Draw(QOpenGLShaderProgram& shader)
{
    shader.bind();
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    EBO.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.release();
}

void Mesh::setupMesh()
{
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices.data(), sizeof(Vertex) * vertices.size());

    EBO.create();
    EBO.bind();
    EBO.allocate(indices.data(), sizeof(unsigned int) * indices.size());

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    VBO.release();
}
