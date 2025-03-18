#include "ICPOpenGLWidget.h"

unsigned int VAO, VBO, EBO;

float vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

ICPOpenGLWidget::ICPOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{
    timer.setInterval(200);
    connect(&timer, &QTimer::timeout, [this](){
        makeCurrent();
        int timeValue = QTime::currentTime().msec();
        float greenValue = sin(timeValue)/2.0f + 0.5f;
        shaderProgram.setUniformValue("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
        doneCurrent();
        update();
    });
    timer.start();
}

ICPOpenGLWidget::~ICPOpenGLWidget()
{
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    doneCurrent();
}

void ICPOpenGLWidget::drawRectangle()
{
    ShapeType = GL_TRIANGLES;
    isDraw = true;
    update();
}

void ICPOpenGLWidget::clear()
{
    isDraw = false;
    update();
}

void ICPOpenGLWidget::setPolygonMode(bool isWire)
{
    makeCurrent();
    if(isWire)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    doneCurrent();
    update();
}

void ICPOpenGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();

    // shaders
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shapes.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shapes.frag");
    bool success = shaderProgram.link();
    if(!success){
        qDebug() << shaderProgram.log();
    }
    shaderProgram.bind();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 将数据传入显存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    int posLocation = shaderProgram.attributeLocation("aPos");
    cout << posLocation << endl;
    // 告知显卡如何解析
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)0);

    // 开启VAO的属性
    glEnableVertexAttribArray(posLocation);
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ICPOpenGLWidget::resizeGL(int w, int h)
{

}

void ICPOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(!isDraw) return;
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(ShapeType, 6, GL_UNSIGNED_INT, 0/*&indices*/);
    glBindVertexArray(0);
}
