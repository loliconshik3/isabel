#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "mainwindow.h"
#include <QTextEdit>
#include <QKeyEvent>

#include <string>
#include <fstream>
#include <iostream>

class MainWindow::Textbox : public QTextEdit
{
    Q_OBJECT
public:
    MainWindow *root;
    Textbox(MainWindow *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) {

        if (event->key() == Qt::Key_Tab) {
            root->changeMain();
            return;
        }
        QTextEdit::keyPressEvent(event);
        if (event->key() == Qt::Key_Return and root->writeMod == root->LIST_WRITE_MOD) {
            insertPlainText("• ");
        }
    }
};

#endif // TEXTBOX_H
