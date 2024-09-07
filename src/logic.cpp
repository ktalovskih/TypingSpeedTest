#include "../hdr/logic.h"

Logic::Logic() : timer(new QElapsedTimer), mistakes(0), message(new QMessageBox){

}

Logic::~Logic(){

}

void Logic::startTimer(){

    timer->start();

}
void Logic::stopTimer(int charsTyped){

    if (charsTyped == 0) {
        qDebug() << "No characters typed.";
        return;
    }

    float timeElapsed = timer->elapsed();
    float timeElapsedInMinutes = timeElapsed / 60000.0;

    float charsPerMinute = charsTyped / timeElapsedInMinutes;

    float accuracy;
    if (mistakes == 0) {
        accuracy = 100;
    } else {
        accuracy = 100 - ((float)mistakes / charsTyped) * 100;
    }

    qDebug() << "Characters Typed:" << charsTyped << "\n";
    qDebug() << "Characters Per Minute (CPM):" << charsPerMinute << "\n";
    qDebug() << "Accuracy: " << accuracy << "\n";
    qDebug() << "Mistakes: " << mistakes << "\n";


    QString results = "Characters Per Minute (CPM): " + QString::number(charsPerMinute) + "\nAccuracy: " + QString::number(accuracy);
    message->setText(results);
    message->show();
}


void Logic::userMadeMistake(){
    mistakes++;
}
