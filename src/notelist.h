#ifndef NOTELIST_H
#define NOTELIST_H

#include "mainwindow.h"

#include <QListWidget>

class MainWindow::NoteList : public QListWidget
{
    Q_OBJECT
public:
    MainWindow *root;
    std::map<std::string, std::string> notes;

    NoteList(MainWindow *parent=nullptr);
    void LoadNotes();
    void redrawNotes();

public:
    void openNote();
    void removeNote();
};

#endif // NOTELIST_H
