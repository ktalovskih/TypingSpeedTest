#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QKeyEvent>
#include <iostream>
#include <QMainWindow>
#include "ui_window.h"
#include <QVector>
#include <QCloseEvent>
#include "virtualkeyboard.h"
#include "logic.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void addingText();
    void showRandomText();
    void showPressedKey();
    std::string getText();

protected:

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:

    QPushButton* reloadButton;
    Ui::MainWindow* ui;
    VirtualKeyboard* keyboard;
    QVector<QString> texts;
    bool failed;
    Logic* logic;
    size_t i;
    int counter;
    bool altPressed;
    bool shiftPressed;

};

#endif // MAINWINDOW_H
