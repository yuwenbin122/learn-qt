#include "model.h"
#include<QFile>

Model::Model(const QString& path)
{
    this->initializeOpenGLFunctions();
    loadModel(path);
}

Model::~Model()
{
    for (int i = 0; i < meshes.size(); i++)
        delete meshes[i];
    for (int i = 0; i < gltextures.size(); i++)
        delete gltextures[i];
}

void Model::loadModel(const QString& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toLatin1(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    int index = path.lastIndexOf('/');
    rootPath = path.left(index);
    processNode(scene->mRootNode, scene);
    processMaterials(scene);

}
void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        matrialMeshesMap[mesh->mMaterialIndex].push_back(meshes.size());
        meshes.push_back(processMesh(mesh));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
Mesh* Model::processMesh(aiMesh* mesh)
{
    QVector<Vertex> vertices;
    QVector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        QVector3D vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.setX(mesh->mNormals[i].x);
            vector.setY(mesh->mNormals[i].y);
            vector.setZ(mesh->mNormals[i].z);
            vertex.Normal = vector;
        }

        QVector2D vec;
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.TexCoords = vec;

            vector.setX(mesh->mTangents[i].x);
            vector.setY(mesh->mTangents[i].y);
            vector.setZ(mesh->mTangents[i].z);
            vertex.Tangent = vector;

            vector.setX(mesh->mBitangents[i].x);
            vector.setY(mesh->mBitangents[i].y);
            vector.setZ(mesh->mBitangents[i].z);
            vertex.Bitangent = vector;
        }
        else
        {
            vertex.TexCoords = QVector2D(0, 0);
        }
        vertices.push_back(vertex);
    }
    qDebug() << "mNumFaces=" << mesh->mNumFaces;
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return new Mesh(vertices, indices);
}

void Model::processMaterials(const aiScene* scene)
{
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        unsigned int texCount = 0;
        aiString texturePath;
        int textureId = -1;

        Material mat;
        //一类贴图只取一张
        texCount = scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE);
        if (texCount > 0)
        {
            scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
            textureId = findTextureIndex(&texturePath);
            mat.diffuseTexture = textureId;
        }

        texCount = scene->mMaterials[i]->GetTextureCount(aiTextureType_SPECULAR);
        if (texCount > 0)
        {
            scene->mMaterials[i]->GetTexture(aiTextureType_SPECULAR, 0, &texturePath);
            textureId = findTextureIndex(&texturePath);
            mat.specularTexture = textureId;
        }

        texCount = scene->mMaterials[i]->GetTextureCount(aiTextureType_HEIGHT);
        if (texCount > 0)
        {
            scene->mMaterials[i]->GetTexture(aiTextureType_HEIGHT, 0, &texturePath);
            textureId = findTextureIndex(&texturePath);
            mat.normalTexture = textureId;
        }

        texCount = scene->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT);
        if (texCount > 0)
        {
            scene->mMaterials[i]->GetTexture(aiTextureType_AMBIENT, 0, &texturePath);
            qDebug() << "texturePath=" << texturePath.C_Str();
            textureId = findTextureIndex(&texturePath);
            mat.heightTexture = textureId;
        }

        aiColor3D color;
        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color);
        mat.ambientColor = QVector3D(color.r, color.g, color.b);

        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        mat.diffuseColor = QVector3D(color.r, color.g, color.b);

        scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color);
        mat.specularColor = QVector3D(color.r, color.g, color.b);

        scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, mat.shininess);

        materials.push_back(mat);
    }
}

int Model::findTextureIndex(const aiString* texturePath)
{
    int texId = -1;
    QString texPath = QString("%1/%2").arg(rootPath).arg(texturePath->C_Str());
    for (int i = 0; i < textures.size(); i++)
    {
        if (textures[i] == texPath) {
            texId = i;
            break;
        }
    }
    if (texId == -1)
    {
        texId = static_cast<int>(textures.size());
        gltextures.push_back(loadTexture(texPath));
        textures.push_back(texPath);
    }
    return texId;
}

QOpenGLTexture* Model::loadTexture(const QString& path)
{
    QImage image = QImage(path).mirrored(false, false);
    if (image.isNull())
    {
        qDebug() << "Failed to load texture" << path;
        return nullptr;
    }
    QOpenGLTexture* texture = new QOpenGLTexture(image, QOpenGLTexture::GenerateMipMaps); //直接生成绑定一个2d纹理, 并生成多级纹理MipMaps
    if (!texture->isCreated()) {
        qDebug() << "Failed to load texture";
        return nullptr;
    }
    // set the texture wrapping parameters
    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);// 等于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    texture->setMinificationFilter(QOpenGLTexture::Linear);   //等价于glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    return texture;
}

void Model::Draw(QOpenGLShaderProgram& shader)
{
    shader.bind();
    for (QMap<int, QVector<int>>::iterator itr = matrialMeshesMap.begin(); itr != matrialMeshesMap.end(); itr++)
    {
        int matId = itr.key();
        if (materials[matId].diffuseTexture > -1)
        {
            glActiveTexture(GL_TEXTURE0);
            gltextures[materials[matId].diffuseTexture]->bind();
            shader.setUniformValue("texture_diffuse", 0);
        }
        if (materials[matId].specularTexture > -1)
        {
            glActiveTexture(GL_TEXTURE1);
            gltextures[materials[matId].specularTexture]->bind();
            shader.setUniformValue("texture_specular", 1);
        }
        if (materials[matId].heightTexture > -1)
        {
            glActiveTexture(GL_TEXTURE2);
            gltextures[materials[matId].heightTexture]->bind();
            shader.setUniformValue("texture_height", 2);
        }
        if (materials[matId].normalTexture > -1)
        {
            glActiveTexture(GL_TEXTURE3);
            gltextures[materials[matId].normalTexture]->bind();
            shader.setUniformValue("texture_normal", 3);
        }
        shader.setUniformValue("color_ambient", materials[matId].ambientColor);
        shader.setUniformValue("color_diffuse", materials[matId].diffuseColor);
        shader.setUniformValue("color_specular", materials[matId].specularColor);
        shader.setUniformValue("shininess", materials[matId].shininess);

        for (int i = 0; i < itr.value().size(); i++)
        {
            meshes[itr.value()[i]]->Draw(shader);
        }
        shader.release();
    }
}
