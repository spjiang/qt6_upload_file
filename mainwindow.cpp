#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videouploaddialog.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 登录
    QString token = Common::login();
    token ="1111";
    if(token.isNull()){
        Common::errDialog("登录失败");
        return;
    }

    m_VideoUploadDialog = new VideoUploadDialog(this);
    // TODO 点击保存并上传
    // 目录压缩地址
    m_VideoUploadDialog->setDirectoryPath("D:/XNDD/workplace/video_upload_file/1");
    // 压缩后zip保存地址
    m_VideoUploadDialog->setOutputFilePath("D:/XNDD/compressDirectory/1");
    // 登录TOKEN
    m_VideoUploadDialog->setToken(token);

    ui->setupUi(this);
    connect(ui->filesavebutton,&QPushButton::clicked,this,&MainWindow::savefile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::savefile(){
    m_VideoUploadDialog->show();
}
