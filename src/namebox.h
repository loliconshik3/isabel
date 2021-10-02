#ifndef NAMEBOX_H
#define NAMEBOX_H

#include <QLineEdit>
#include "mainwindow.h"

class MainWindow::Namebox : public QLineEdit
{
    Q_OBJECT
public:
    MainWindow *root;
    Namebox(MainWindow *parent = nullptr);

public:
    void nameEntered();

public:
    void filterList();

private slots:
    void Down();
    void Up();
};

#endif // NAMEBOX_H
