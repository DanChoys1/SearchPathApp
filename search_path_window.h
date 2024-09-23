#ifndef SEARCHPATHWINDOW_H
#define SEARCHPATHWINDOW_H

#include "search_path_gr_scene.h"

#include <QGraphicsScene>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchPathWindow; }
QT_END_NAMESPACE

class SearchPathWindow : public QWidget
{ Q_OBJECT

public:
    SearchPathWindow(QWidget *parent = nullptr);
    ~SearchPathWindow();

    void onGenerateBtnClicked();

private:
    void saveWindowPos();
    void initWindowPos();

private:
    Ui::SearchPathWindow *ui;

    SearchPathGrScene _searchPathManager;

};

#endif // SEARCHPATHWINDOW_H
