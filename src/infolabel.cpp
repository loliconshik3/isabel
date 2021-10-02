#include "infolabel.h"
#include "textbox.h"
#include "notelist.h"

#include <string>
#include <fstream>
#include <iostream>

MainWindow::InfoLabel::InfoLabel(MainWindow *parent) :
    QLabel(parent)
{
    root = parent;
    setGeometry(parent->WIDTH-20, 0, 20, 30);
    setStyleSheet("QLabel { border: none; font-size: 14px; background: #2e3440; color: #929499; }");
    setAlignment(Qt::AlignCenter);
    setText("S");
    //updateText();
}

void MainWindow::InfoLabel::updateText() {
    std::string text = "None";

    //std::cout << (root->textbox == NULL) << std::endl;

    if (not root->textbox->isHidden()) {
        text = root->writeMod.substr(0, 1);
    }

    else if (not root->noteList->isHidden()) {
        text = root->noteMod.substr(0, 1);
    }

    setText(text.c_str());
}
