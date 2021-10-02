#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QClipboard>
#include <QEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QApplication *app;
    const std::string STANDART_WRITE_MOD = "StandartWM";
    const std::string LIST_WRITE_MOD = "ListWM";
     const std::string READ_WRITE_MOD = "ReadWM";

    const std::string STANDART_NOTE_MOD = "StandartNM";
    const std::string REMOVE_NOTE_MOD = "RemoveNM";

    int WIDTH = 500;
    int HEIGHT = 500;
    std::string writeMod = STANDART_WRITE_MOD;
    std::string noteMod = STANDART_NOTE_MOD;

    class Textbox;
    class Namebox;
    class NoteList;
    class InfoLabel;
    Textbox *textbox;
    Namebox *namebox;
    NoteList *noteList;
    InfoLabel *infoLabel;

    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();

private slots:
    void SaveNote();
    void changeMain();
    void changeFocus();
    void changeMod();
    void readMod(bool arg);
    void Return();

protected:
    void closeEvent(QCloseEvent *event) {
        QClipboard *clipboard = this->app->clipboard();
        QEvent *clipEvent = new QEvent(QEvent::Clipboard);
        this->app->sendEvent(clipboard, clipEvent);
        std::exit(0);
    }
};
#endif // MAINWINDOW_H
