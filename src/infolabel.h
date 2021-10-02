#ifndef INFOLABEL_H
#define INFOLABEL_H

#include <QLabel>
#include "mainwindow.h"

class MainWindow::InfoLabel : public QLabel
{
    Q_OBJECT
public:
    MainWindow *root;
    InfoLabel(MainWindow *parent = nullptr);
    void updateText();
};

#endif // INFOLABEl_H
