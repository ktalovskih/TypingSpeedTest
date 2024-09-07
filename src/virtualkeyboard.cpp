#include "../hdr/virtualkeyboard.h"
#include <QPushButton>
#include <QKeyEvent>

VirtualKeyboard::VirtualKeyboard(QWidget* parent)
    : QWidget(parent), layout(new QGridLayout(this)), english(true)
{
    initializationOfLayouts();
    setLayout();
}
void VirtualKeyboard::setLayout(){
    int row = 0; int col = 0;

    english ? english = 0 : english = 1;

    QVector<QString> namesOfKeys;

    english ? namesOfKeys = getRussianLayout() : namesOfKeys = getEnglishLayout();

    for (int i = 0; i < 14; i++){
        QPushButton* button = new QPushButton(namesOfKeys[i]);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setFocusPolicy(Qt::NoFocus);
        keys[namesOfKeys[i]] = button;
        layout->addWidget(button, row, col++);
    }
    row++; col = 0;
    for (int i = 14; i < 28; i ++ ){
        QPushButton* button = new QPushButton(namesOfKeys[i]);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setFocusPolicy(Qt::NoFocus);
        keys[namesOfKeys[i]] = button;
        layout->addWidget(button, row, col++);

    }
    row++; col = 0;
    for (int i = 28; i < 41; i ++ ){
        QPushButton* button = new QPushButton(namesOfKeys[i]);
        keys[namesOfKeys[i]] = button;
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setFocusPolicy(Qt::NoFocus);
        if (i == 40){
            layout->addWidget(button, row, col++,1 , 2);
        }
        else{
            layout->addWidget(button, row, col++);
        }
    }
    row++; col = 0;
    for (int i = 41; i < 53; i ++){
        QPushButton* button = new QPushButton(namesOfKeys[i]);
        keys[namesOfKeys[i]] = button;
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setFocusPolicy(Qt::NoFocus);
        if (namesOfKeys[i] == "Shift_L" || namesOfKeys[i] == "Shift_R"){
            layout->addWidget(button, row, col++, 1 , 2);
            col++;
        }
        else{
            layout->addWidget(button, row, col++);
        }

    }
    row++; col = 4;

    QPushButton* button = new QPushButton(namesOfKeys[53]);
    keys[namesOfKeys[53]] = button;
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(button, row, col++, 1 , 6);
}
void VirtualKeyboard::highlightTheKey(QKeyEvent* event)
{
    QString keyText = event->text().toUpper();
    int key = event->key();
    switch (key)
    {
    case Qt::Key_Space:
        keyText = "Space";
        break;
    case Qt::Key_Backspace:
        keyText = "Backspace";
        break;
    case  Qt::Key_CapsLock:
        keyText = "Caps";
        break;
    case Qt::Key_Return:
        keyText = "Enter";
        break;
    case Qt::Key_Tab:
        keyText = "Tab";
        break;
    case Qt::Key_Shift:
        keyText = (event->modifiers() & Qt::ShiftModifier & Qt::ControlModifier) ? "Shift_R" : "Shift_L";
        break;
    }
    auto it = keys.find(keyText);

    if (it != keys.end()) {
        QPushButton* button = it.value();
        button->setStyleSheet("background-color: yellow");
    }
}
void VirtualKeyboard::unHightlightTheKey(QKeyEvent* event)
{
    QString keyText = event->text().toUpper();
    int key = event->key();
    switch (key)
    {
    case Qt::Key_Space:
        keyText = "Space";
        break;
    case Qt::Key_Backspace:
        keyText = "Backspace";
        break;
    case  Qt::Key_CapsLock:
        keyText = "Caps";
        break;
    case Qt::Key_Return:
        keyText = "Enter";
        break;
    case Qt::Key_Tab:
        keyText = "Tab";
        break;

    case Qt::Key_Shift:
        keyText = (event->modifiers() & Qt::ShiftModifier & Qt::ControlModifier) ? "Shift_R" : "Shift_L";
        break;
    }
    auto it = keys.find(keyText);
    if (it != keys.end()) {
        QPushButton* button = it.value();
        button->setStyleSheet("");
    }
}
VirtualKeyboard::~VirtualKeyboard()
{

}
void VirtualKeyboard::initializationOfLayouts()
{
    russianLayout = {"Ё", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
    "Tab", "Й", "Ц", "У", "К", "Е", "Н", "Г", "Ш", "Щ", "З", "Х", "Ъ", "\\",
    "Caps", "Ф", "Ы", "В", "А", "П", "Р", "О", "Л", "Д", "Ж", "Э", "Enter",
    "Shift_L", "Я", "Ч", "С", "М", "И", "Т", "Ь", "Б", "Ю", ".", "Shift_R",
    "Space"};

    englishLayout = {"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
    "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\\",
    "Caps", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter",
    "Shift_L", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Shift_R",
    "Space"};

}
QVector<QString> VirtualKeyboard::getEnglishLayout (){
    return englishLayout;
}
QVector<QString> VirtualKeyboard::getRussianLayout (){
    return russianLayout;
}
#include "moc_virtualkeyboard.cpp"
