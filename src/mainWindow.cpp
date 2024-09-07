#include "../hdr/mainWindow.h"
#include "../hdr/virtualkeyboard.h"
#include <QPushButton>
#include <QVector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <QRandomGenerator>
#include <QTimer>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), failed(false),
                                        i(0), keyboard(new VirtualKeyboard), reloadButton(new QPushButton),
                                        logic(new Logic)
{

    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout(this);
    ui->centralwidget->setLayout(layout);
    ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(reloadButton, 0, 0, Qt::AlignLeft);
    std::filesystem::path icon = std::filesystem::current_path() / "src" / "icons.png";
    reloadButton->setIcon(QIcon(QString::fromStdString(icon.string())));
    reloadButton->setIconSize(QSize(24, 24));
    layout->addWidget(ui->label);


    ui->centralwidget->layout()->addWidget(keyboard);

    connect(reloadButton, &QPushButton::pressed, this, &MainWindow::showRandomText);

    reloadButton->setFocusPolicy(Qt::NoFocus);
    addingText();
    showRandomText();


}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if (i == 0)logic->startTimer();

    int key = event->key();
    QString text = ui->label->text();
    QString openingTagRed = "<font color='red'>";
    QString openingTagGreen = "<font color='green'>";
    QString cursor = "|";
    QString closingTag = "</font>";
    text.remove(cursor);
   
    if (i < text.length() && (key != Qt::Key_Escape && key != Qt::Key_Shift && key && key != Qt::Key_Return))
    {
        if (event->text() == text[i])
        {
            if (failed){
                text.replace("<font color='red'>", openingTagGreen);
                failed = false;
                logic->userMadeMistake();
                i += 3 + closingTag.length();
            }
            else{
                text.insert(i, openingTagGreen);
                text.insert(i + openingTagGreen.length() + 1, closingTag);
                i += openingTagGreen.length() + closingTag.length() + 1;
            }
        }
        else if (!failed)
        {
            text.insert(i, openingTagRed);
            text.insert(i + openingTagRed.length() + 1, closingTag);
            i += openingTagGreen.length() - 2;
            failed = true;
        }

    }
    if (i <= text.length()) {
        text.insert(i, cursor);

    } else {
        text.append(cursor);
    }
    if (key == Qt::Key_Shift) {
        shiftPressed = 1;
        if (altPressed){
            keyboard->setLayout();
        }
    }
    if (key == Qt::Key_Alt) {
        altPressed = 1;
        if (shiftPressed){
            keyboard->setLayout();
        }
    }

    qDebug() << event->text() << "\n";
    ui->label->setText(text);
    keyboard->highlightTheKey(event);
    QMainWindow::keyPressEvent(event);
    counter++;
    if (i == text.length() - 1) logic->stopTimer(counter);



}

void MainWindow::addingText()
{
    std::filesystem::path folder = std::filesystem::current_path();
    folder += "/texts/";

    if (!std::filesystem::exists(folder) || !std::filesystem::is_directory(folder))
    {
        std::cerr << "The specified path is not a valid directory." << std::endl;
    }

    for (const auto &file : std::filesystem::directory_iterator(folder))
    {
        std::ifstream text(file.path());
        if (!file.exists())
        {
            qDebug() << "!!";
        }
        std::string t;
        QString buffer;
        while (std::getline(text, t))
        {
            buffer += t;
        }
        texts.emplace_back(buffer);
    }
    for (const auto &t : texts)
    {
        qDebug() << t << " ";
    }
}
void MainWindow::showPressedKey()
{

}

void MainWindow::keyReleaseEvent (QKeyEvent* event){
    keyboard->unHightlightTheKey(event);
    if (event->key() == Qt::Key_Shift) shiftPressed = 0;
    if (event->key() == Qt::Key_Alt) altPressed = 0;

}
void MainWindow::showRandomText()
{
    ui->label->setText(texts[QRandomGenerator::global()->bounded(0, texts.size())]);
    i = 0;
}

std::string MainWindow::getText(){
    return ui->label->text().toStdString();
}

#include "moc_mainWindow.cpp"
