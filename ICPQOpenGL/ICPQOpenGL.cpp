#include "ICPQOpenGL.h"
#include "./ui_ICPQOpenGL.h"

ICPQOpenGL::ICPQOpenGL(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ICPQOpenGL)
{
    ui->setupUi(this);
    openGLWidget = new ICPOpenGLWidget(parent);
    setCentralWidget(openGLWidget);
}

ICPQOpenGL::~ICPQOpenGL()
{
    delete ui;
}

void ICPQOpenGL::on_actionDrawRectangle_triggered()
{
    openGLWidget->drawRectangle();
}


void ICPQOpenGL::on_actionClear_triggered()
{
    openGLWidget->clear();
}


void ICPQOpenGL::on_actionWireframe_toggled(bool arg1)
{
    openGLWidget->setPolygonMode(arg1);
}

