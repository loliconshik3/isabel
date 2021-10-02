#include "namebox.h"
#include "notelist.h"
#include "textbox.h"

#include <string>
#include <fstream>
#include <iostream>
#include <QShortcut>

MainWindow::Namebox::Namebox(MainWindow *parent) :
    QLineEdit(parent)
{
    root = parent;
    setGeometry(0, 0, parent->WIDTH-20, 30);
    setPlaceholderText("Name for your note...");
    setStyleSheet("QLineEdit { border: none; font-size: 20px; background: #2e3440; }");

    QShortcut *shortcut = new QShortcut(QKeySequence("Down"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Down()));

    shortcut = new QShortcut(QKeySequence("Up"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Up()));

    connect(this, &Namebox::textChanged, this, &Namebox::filterList);
}

void MainWindow::Namebox::nameEntered() {
    root->textbox->setFocus();
}

void MainWindow::Namebox::Up() {
    if (not root->noteList->isHidden()) {
        int itemIndex = root->noteList->currentIndex().row();
        int maxIndex = 0;

        if (itemIndex > maxIndex) {
           root->noteList->setCurrentItem(root->noteList->item(itemIndex-1));
        }
    }
}

void MainWindow::Namebox::Down() {
    if (not root->noteList->isHidden()) {
        int itemIndex = root->noteList->currentIndex().row();
        int maxIndex = root->noteList->count()-1;

        if (itemIndex < maxIndex) {
           root->noteList->setCurrentItem(root->noteList->item(itemIndex+1));
        }
    }
}

void MainWindow::Namebox::filterList() {
    if (not root->noteList->isHidden()) {
        root->noteList->redrawNotes();
    }
}
