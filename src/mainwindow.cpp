#include "mainwindow.h"
#include "infolabel.h"
#include "notelist.h"
#include "namebox.h"
#include "textbox.h"

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <QDesktopWidget>
#include <QTextStream>
#include <QShortcut>
#include <QLineEdit>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(QSize(WIDTH, HEIGHT));
    setMaximumSize(QSize(WIDTH, HEIGHT));
    setStyleSheet("QMainWindow { background: #3b4252; }");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::Popup);

    QRect rect = QDesktopWidget().availableGeometry();
    int x = (rect.width()-WIDTH)/2;
    int y = (rect.height()-HEIGHT)/2;
    move(x, y);

    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(SaveNote()));

    shortcut = new QShortcut(QKeySequence("Tab"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(changeMain()));

    shortcut = new QShortcut(QKeySequence("Return"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Return()));

    shortcut = new QShortcut(QKeySequence("Ctrl+e"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(changeFocus()));

    shortcut = new QShortcut(QKeySequence("Ctrl+w"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(changeMod()));
}

void MainWindow::changeMain() {
    if (not textbox->isHidden()) {
        textbox->hide();
        noteList->show();
        readMod(false);
        namebox->clear();
        namebox->setFocus();
        namebox->filterList();
        if (noteList->count() > 0)
            noteList->setCurrentItem(noteList->item(0));
        namebox->setPlaceholderText("Type to filter...");
    }
    else {
        textbox->show();
        noteList->hide();
        namebox->clear();
        namebox->setFocus();
        namebox->setPlaceholderText("Name for your note...");
    }

    infoLabel->updateText();
}

void MainWindow::SaveNote() {
    std::string homedir;

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    QString fileName = (homedir + "/.isabel/").c_str() + namebox->text();
    if (fileName.isEmpty()){
        return;
    }
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            std::exit(1);
        }
        QTextStream out(&file);

        auto text = textbox->toPlainText().toUtf8();//.toStdString();

        out << text;
        out.flush();
        file.close();
        noteList->LoadNotes();
        //std::exit(0);
    }
}

void MainWindow::Return() {
    if (focusWidget() == namebox) {
        if (not textbox->isHidden()) {
            namebox->nameEntered();
            if (writeMod == LIST_WRITE_MOD) {
                textbox->insertPlainText("• ");
            }
            return;
        }
    }
    if (not noteList->isHidden()) {
        if (noteMod == STANDART_NOTE_MOD) {
            noteList->openNote();
        }
        else if (noteMod == REMOVE_NOTE_MOD) {
            noteList->removeNote();
        }
    }
}

void MainWindow::changeFocus() {
    if (not textbox->isHidden()) {
        if (focusWidget() == textbox) {
            namebox->setFocus();
        }
        else {
            textbox->setFocus();
        }
    }
}

void MainWindow::readMod(bool arg) {
    if (arg) {
        writeMod = READ_WRITE_MOD;
        textbox->setReadOnly(true);
        namebox->setReadOnly(true);
    }
    else {
        writeMod = STANDART_WRITE_MOD;
        textbox->setReadOnly(false);
        namebox->setReadOnly(false);
    }
    infoLabel->updateText();
}

void MainWindow::changeMod() {
    if (not textbox->isHidden()) {
        if (writeMod == LIST_WRITE_MOD) {
            readMod(true);
        }
        else if (writeMod == STANDART_WRITE_MOD) {
            writeMod = LIST_WRITE_MOD;
        }
        else if (writeMod == READ_WRITE_MOD) {
            readMod(false);
        }
    }
    else if (not noteList->isHidden()) {
        if (noteMod == REMOVE_NOTE_MOD) {
            noteMod = STANDART_NOTE_MOD;
        }
        else if (noteMod == STANDART_NOTE_MOD) {
            noteMod = REMOVE_NOTE_MOD;
        }
    }

    infoLabel->updateText();
}

