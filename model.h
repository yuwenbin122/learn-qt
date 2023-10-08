#ifndef MODEL_H
#define MODEL_H

#include<QMap>
#include<QOpenGLTexture>
#include<QOpenGLFunctions>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "mesh.h"
struct Material
{
    QVector3D diffuseColor;
    QVector3D ambientColor;
    QVector3D specularColor;

    //贴图索引，-1表示没有此类贴图
    int diffuseTexture = -1;
    int specularTexture = -1;
    int normalTexture = -1;
    int heightTexture = -1;
    float shininess;
    //不考虑透明
};

class Model :QOpenGLFunctions
{
public:
    QVector<QString> textures; //记录模型中所有的贴图路径
    QVector<Material> materials; //记录模型中所有的材质信息
    QVector<Mesh*> meshes; //记录模型中所有的三角网格信息
    QMap<int, QVector<int>> matrialMeshesMap;//材质-三角网格索引字典
    Model(const QString& path);
    void Draw(QOpenGLShaderProgram& shader);
    ~Model();
private:
    QString rootPath;
    void loadModel(const QString& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh);
    void processMaterials(const aiScene* scene);
    int findTextureIndex(const aiString* texturePath);
    QVector<QOpenGLTexture*> gltextures;
    QOpenGLTexture* loadTexture(const QString& path);
};

#endif // MODEL_H
