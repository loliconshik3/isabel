#include "mainwindow.h"
#include "infolabel.h"
#include "notelist.h"
#include "namebox.h"
#include "textbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    system("mkdir ~/.isabel");

    QApplication app(argc, argv);
    MainWindow window;
    window.app = &app;

    MainWindow::Textbox textbox(&window);
    MainWindow::Namebox namebox(&window);
    MainWindow::NoteList noteList(&window);
    MainWindow::InfoLabel infoLabel(&window);
    window.textbox = &textbox;
    window.namebox = &namebox;
    window.noteList = &noteList;
    window.infoLabel = &infoLabel;

    window.show();
    textbox.show();
    namebox.show();
    infoLabel.show();
    noteList.hide();
    namebox.setFocus();
    return app.exec();
}

/*
 * Можно будет добавить режимы записи.
    * Стандартный (ну, тут по стандарту, ничо не меняется)
    * Список (в текстбоксе при переносе строки в начала будет номер добавляться, типа список (1.; 2. итд)
    * Точечный список (также, как и список, ток вместо цифр - •)
    * и тд.
 *
 * И добавить ктрл+в чтоб можно было переключать режим удаления и обычный режим в списке заметок. надо же как-то удалять их
 *
 *
 *
 *
 *
 *
 *
 *
*/
