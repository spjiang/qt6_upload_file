#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videouploaddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->filesavebutton,&QPushButton::clicked,this,&MainWindow::savefile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::savefile(){
    // 上文文件
    VideoUploadDialog* w = new VideoUploadDialog(this);
    w->setDirectoryPath("D:/XNDD/workplace/video_upload_file/1");
    w->setOutputFilePath("D:/XNDD/compressDirectory/1");
    w->show();
}
