#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QMap>
#include <QGridLayout>
#include <QKeyEvent>


class VirtualKeyboard : public QWidget {

    Q_OBJECT

public:

    explicit VirtualKeyboard(QWidget* parent = nullptr);
    ~VirtualKeyboard();
    void highlightTheKey(QKeyEvent* event);
    void unHightlightTheKey(QKeyEvent* event);
    void initializationOfLayouts();
    void changeLanguage();
    void setLayout();

    QVector <QString> getEnglishLayout();
    QVector <QString> getRussianLayout();

private:
    bool english;
    QMap<QString, QPushButton*> keys;
    QGridLayout* layout;
    QVector<QString> russianLayout;
    QVector<QString> englishLayout;

};

#endif // VIRTUALKEYBOARD_H
