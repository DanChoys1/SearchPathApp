#include "search_path_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SearchPathWindow w;
    w.show();

    return a.exec();
}
