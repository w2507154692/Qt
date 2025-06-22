#include "Qt622.h"
#include <QtWidgets/QApplication>
#include "Date.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Qt622 window;
    window.show();
    return app.exec();
}
