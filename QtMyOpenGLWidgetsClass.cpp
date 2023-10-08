#include "QtMyOpenGLWidgetsClass.h"
#include<qtime>
float step = 2.5f;
QtMyOpenGLWidgetsClass::QtMyOpenGLWidgetsClass(QWidget* parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
    camera.Position =QVector3D(0.0f, 0.0f,3.0f);
     connect(&timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
     timer.start(1);
}

QtMyOpenGLWidgetsClass::~QtMyOpenGLWidgetsClass()
{
    makeCurrent();
    doneCurrent();
}

void QtMyOpenGLWidgetsClass::initializeGL()
{
	initializeOpenGLFunctions();   
   shader.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, "shader/v.glsl");
    shader.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, "shader/f.glsl");
    shader.link();
    model=new Model("texture/3dbuch/book.obj");
  }

void QtMyOpenGLWidgetsClass::resizeGL(int w, int h)
{
	Q_UNUSED(w); Q_UNUSED(h);
	
}

void QtMyOpenGLWidgetsClass::paintGL()
{
    unsigned int time = QTime::currentTime().msec();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //清屏
    glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);    //清除颜色缓冲
    shader.bind();
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix4x4 model1;
    model1.translate(0.0f, 0.0f, -1.0f);
    model1.rotate(90, 0.0f, 0.0f, 1.0f);
    model1.rotate(60, 1.0f, 0.0f, 0.0f);
    model1.scale(0.85f, 0.85f, 0.85f);
   // step += time/250;
   // model1.rotate(step, 0.0f, 0.0f, 1.0f);
    view = camera.GetViewMatrix();
    projection.perspective(camera.Zoom, (float)(width() / height()), 0.1, 100);
    shader.setUniformValue("view", view);
    shader.setUniformValue("model", model1);
    shader.setUniformValue("projection", projection);
    model->Draw(shader);
    
}
void QtMyOpenGLWidgetsClass::on_timeout()
{
    update();
}