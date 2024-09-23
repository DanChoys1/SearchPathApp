#include "search_path_window.h"
#include "./ui_search_path_window.h"

#include <QSettings>

namespace
{
const QString WinPosProp { QStringLiteral("windowPosition") };
const QPoint WinPosDefautl { 0, 0 };
}

SearchPathWindow::SearchPathWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchPathWindow)
{
    ui->setupUi(this);

    ui->searchPathGrView->setScene(&_searchPathManager);
    connect(&_searchPathManager, &SearchPathGrScene::sceneRectChanged, ui->searchPathGrView, &WheelScaleGrView::fitScene);

    connect(ui->generateBtn, &QPushButton::clicked, this, &SearchPathWindow::onGenerateBtnClicked);

    initWindowPos();

    onGenerateBtnClicked();
}

SearchPathWindow::~SearchPathWindow()
{
    saveWindowPos();
    delete ui;
}

void SearchPathWindow::onGenerateBtnClicked()
{
    qreal h = ui->heightValue->value();
    qreal w = ui->widthValue->value();
    _searchPathManager.generateMap(w, h);
}

void SearchPathWindow::saveWindowPos()
{
    QSettings settings(qAppName(), qAppName());
    settings.setValue(WinPosProp, this->pos());
}

void SearchPathWindow::initWindowPos()
{
    QSettings settings(qAppName(), qAppName());
    this->move(settings.value(WinPosProp, WinPosDefautl).toPoint());
}
