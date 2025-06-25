#include "Qt622.h"
#include <QtWidgets/QApplication>
#include "Date.h"
#include "PersonSet.h"

#define INFOLIBNAME "personnel.dat"
#define BAKLIBNAME "personnel.bak"

void LoadLibToSet(PersonSet& Set) {
    if (Set.ReadFromFile(INFOLIBNAME))
        qDebug() << "�ѷ��ֿ��ļ������ɹ����롣";
    else
        qDebug() << "δ���ֿ��ļ�����ļ�Ϊ�ա�";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PersonSet Set;

    Qt622 window("personnel.dat", &Set);
    window.show();
    return app.exec();
}
