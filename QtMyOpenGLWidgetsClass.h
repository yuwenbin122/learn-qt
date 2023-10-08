#pragma once

#include <QOpenGLWidget>
#include<qopenglfunctions_3_3_core.h>
#include "ui_QtMyOpenGLWidgetsClass.h"
#include<qopenglshaderprogram.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<qopengltexture.h>
#include"camera.h"
#include<model.h>
#include<qtimer.h>

class QtMyOpenGLWidgetsClass : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    QtMyOpenGLWidgetsClass(QWidget* parent = Q_NULLPTR);
    ~QtMyOpenGLWidgetsClass();
public slots:
    void on_timeout();
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    Ui::QtMyOpenGLWidgetsClassClass ui;
    QOpenGLShaderProgram shader;
    QOpenGLTexture* texture;
    Camera camera;
    Model *model;
    QTimer timer;
};