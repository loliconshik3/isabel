#include "notelist.h"
#include "textbox.h"
#include "namebox.h"

#include <QShortcut>

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace fs = std::filesystem;

MainWindow::NoteList::NoteList(MainWindow *parent) :
    QListWidget(parent)
{
    root = parent;
    setGeometry(0, 30, parent->WIDTH, parent->HEIGHT-45);
    setStyleSheet("QListWidget { border: none; font-size: 16px; background: #3b4252; }");
    LoadNotes();
}

void MainWindow::NoteList::LoadNotes() {
    std::ifstream myfile;
    std::string line;

    std::string homedir;

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    std::string path = homedir + "/.isabel";
        for (const auto & entry : fs::directory_iterator(path)){
            myfile.open(entry.path());

            if ( myfile.is_open() ) { // always check whether the file is open
                std::string noteText;
                std::string filename;

                filename = entry.path().filename();
                while (getline(myfile, line)) {
                    noteText += line + "\n";
                }

                notes[filename] = noteText;
                addItem(filename.c_str());
            }

            myfile.close();
        }

    sortItems();
    setCurrentItem(item(0));
}

void MainWindow::NoteList::openNote() {
    if (count() > 0) {
        root->textbox->setText(notes[currentItem()->text().toUtf8().toStdString()].c_str());
        root->changeMain();
        root->namebox->setText(currentItem()->text());
        root->textbox->setFocus();
        QTextCursor cursor = root->textbox->textCursor();
        cursor.movePosition(QTextCursor::End);
        root->textbox->setTextCursor(cursor);
        root->readMod(true);
    }
    else {
        root->changeMain();
    }
}

void MainWindow::NoteList::removeNote() {
    std::string homedir;
    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    std::string path = homedir + "/.isabel/";

    if (count() > 0) {
        std::string filename = currentItem()->text().toStdString();
        notes.erase(filename);
        system(("rm '" + path + filename + "'").c_str());
        redrawNotes();
    }
    else {
        root->changeMain();
    }
}

void MainWindow::NoteList::redrawNotes() {
    clear();

    for (const auto & file : notes) {
        std::string fileName = QString(file.first.c_str()).toLower().toUtf8().constData();
        std::string searchQuery = root->namebox->text().toLower().toUtf8().constData();

        if ( fileName.find(searchQuery) != std::string::npos ) {
            addItem(QString(file.first.c_str()));
        }
    }

    sortItems();
    setCurrentItem(item(0));
}
