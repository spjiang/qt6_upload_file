#include "common.h"
#include <QDebug>
#include <quazip/JlCompress.h>
#include<QMessageBox>

Common::Common() {}

bool Common::compressDirectory(const QString &directoryPath, const QString &outputFilePath) {
    return JlCompress::compressDir(outputFilePath, directoryPath);
}
void Common::errDialog(const QString text){
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox :: Critical);
    messageBox.setText(text);
    messageBox.setWindowTitle("警告");
    messageBox.setStyleSheet("QLabel{ color: red; }");
    messageBox.exec();
}

void Common::infoDialog(const QString text){
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox :: Information);
    messageBox.setText(text);
    messageBox.setWindowTitle("消息");
    messageBox.setStyleSheet("QLabel{ color: green; }");
    messageBox.exec();
}


