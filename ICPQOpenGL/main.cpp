#include "ICPQOpenGL.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ICPQOpenGL w;
    w.show();
    return a.exec();
}
