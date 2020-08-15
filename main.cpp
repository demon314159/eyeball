#include "eyeball.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Eyeball eyeball;
    eyeball.show();
    return app.exec();
}
