#ifndef ICPOPENGLWIDGET_H
#define ICPOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

class ICPOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit ICPOpenGLWidget(QWidget *parent = nullptr);
    ~ICPOpenGLWidget();
    void drawRectangle();
    void clear();
    void setPolygonMode(bool isWire);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    bool isDraw = false;
    int ShapeType = GL_TRIANGLES;
    QOpenGLShaderProgram shaderProgram;

signals:
};

#endif // ICPOPENGLWIDGET_H
