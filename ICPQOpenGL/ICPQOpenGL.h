#ifndef ICPQOPENGL_H
#define ICPQOPENGL_H

#include <QMainWindow>
#include "ICPOpenGLWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ICPQOpenGL;
}
QT_END_NAMESPACE

class ICPQOpenGL : public QMainWindow
{
    Q_OBJECT

public:
    ICPQOpenGL(QWidget *parent = nullptr);
    ~ICPQOpenGL();

private:
    Ui::ICPQOpenGL *ui;
    ICPOpenGLWidget* openGLWidget;
};
#endif // ICPQOPENGL_H
