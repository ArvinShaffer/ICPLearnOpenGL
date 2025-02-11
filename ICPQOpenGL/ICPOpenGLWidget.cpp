#include "ICPOpenGLWidget.h"

ICPOpenGLWidget::ICPOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{}

void ICPOpenGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
}

void ICPOpenGLWidget::resizeGL(int w, int h)
{

}

void ICPOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
