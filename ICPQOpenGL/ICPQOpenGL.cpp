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
