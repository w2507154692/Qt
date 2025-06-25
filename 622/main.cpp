#include "Qt622.h"
#include <QtWidgets/QApplication>
#include "Date.h"
#include "PersonSet.h"

#define INFOLIBNAME "personnel.dat"
#define BAKLIBNAME "personnel.bak"

void LoadLibToSet(PersonSet& Set) {
    if (Set.ReadFromFile(INFOLIBNAME))
        qDebug() << "已发现库文件，并成功读入。";
    else
        qDebug() << "未发现库文件或库文件为空。";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PersonSet Set;

    Qt622 window("personnel.dat", &Set);
    window.show();
    return app.exec();
}
