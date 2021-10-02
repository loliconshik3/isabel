#include "textbox.h"
#include "notelist.h"

#include <string>
#include <fstream>
#include <iostream>

MainWindow::Textbox::Textbox(MainWindow *parent) :
    QTextEdit(parent)
{
    root = parent;
    setGeometry(0, 30, parent->WIDTH, parent->HEIGHT-30);
    setPlaceholderText("Your note...");
    setStyleSheet("QTextEdit { border: none; font-size: 18px; background: #3b4252; }");
}
