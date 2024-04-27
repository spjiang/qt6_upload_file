#include "videouploaddialog.h"
#include "./ui_videouploaddialog.h"
#include<QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "common.h"

// 自定义结构体，用于表示键值对
struct KeyValuePair {
    int key;
    QString value;
};

VideoUploadDialog::VideoUploadDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::VideoUploadDialog) {

    // *************************实例化数据*************************
    // TODO 实例化token
    QString token = Common::login();
    if(token.isNull()){
        Common::errDialog("登录失败");
        return;
    }
    m_token = token;
    qDebug()<< "VideoUploadDialog token:"<<m_token.toUtf8();

    // TODO 保存文件信息
    m_directoryPath= "D:/XNDD/workplace/video_upload_file/1";
    m_outputFilePath= "D:/XNDD/compressDirectory/1";
    qDebug()<< "m_directoryPath:"<<m_directoryPath.toUtf8()<<",m_outputFilePath:"<<m_outputFilePath;

    // 定义创建项目窗口
    m_CreateProjectDialog = new CreateProjectDialog(this);
    ui->setupUi(this);

    // *************************获取项目组列表*************************
    QJsonArray project_result = VideoUploadDialog::getProjectList();
    if(!project_result.isEmpty()){
        for (const QJsonValue &recordValue : project_result) {
            QJsonObject recordObject = recordValue.toObject();
            qDebug()<<"recordObject:"<<recordObject;
            int id = recordObject["id"].toInt();
            qDebug()<<"id:"<<id;
            QString name = recordObject["name"].toString();
            qDebug()<<"name:"<<name;
            ui->project_list->addItem(name, QVariant::fromValue(KeyValuePair{id, name}));
        }
    }

    // 设置样式
    ui->project_list->setStyleSheet(R"(
        QComboBox {
            background-color: #FFFFFF;
            border: 2px solid green;
            color:green;
        }
        QComboBox QAbstractItemView {
            background-color: white;
            selection-background-color:white;
            color:green;
        }

        QComboBox QAbstractItemView::item {
            margin: 5px 0 !important;
        }

        QComboBox::drop-down {
            background-color: white;
        }

        QComboBox::item {
            background-color: white;
            color:green;
            margin: 10px 0 !important;
        }

        QComboBox::item:selected {
            background-color: #0000FF;
        }
    )");
    ui->video_rename->setStyleSheet(R"(
        QLineEdit {
            background-color: white !important;
            color: green !important;
            border: 2px solid green !important;
            }
    )");
    ui->okcancelButtonBox->button(QDialogButtonBox::Ok)->setText(tr("上传"));
    ui->okcancelButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    connect(ui->okcancelButtonBox,&QDialogButtonBox::accepted,this,&VideoUploadDialog::uploadFile);
    connect(ui->createProjectPushButton,&QPushButton::clicked,this,&VideoUploadDialog::createProject);
    connect(m_CreateProjectDialog,&CreateProjectDialog::closeCreateProjectWindow,this, &VideoUploadDialog::refreshProject);
}

void VideoUploadDialog::setToken(QString token){
    m_token = token;
}

void VideoUploadDialog::setDirectoryPath(QString directoryPath){
    m_directoryPath = directoryPath;
}

void VideoUploadDialog::setOutputFilePath(QString outputFilePath){
    m_outputFilePath = outputFilePath;
}

QJsonArray VideoUploadDialog::getProjectList(){
    QJsonArray result;
    QNetworkRequest request;
    QString fullRequest = "http://123.249.67.68:8998/project/dict";
    request.setUrl(QUrl(fullRequest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Source", "app");
    request.setRawHeader("Authorization", m_token.toUtf8());
    qDebug()<< "getProjectList Authorization:"<<m_token.toUtf8();
    // 查看请求头
    qDebug()<<request.rawHeaderList();
    //发送请求
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"请求连接超时";
        qDebug()<< reply->error();
        return result;
    }
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<"状态码："<<statusCode.toInt();
    if (statusCode.isValid()) {
        if (statusCode.toInt() != 200) {
            // 请求失败
            qDebug()<<"请求失败";
            return result;
        }
    }
    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug()<<json_error.error<<replyData;
        return result;
    }
    QJsonObject rootObj = jsonDoc.object();
    qDebug()<<rootObj;
    QJsonValue code = rootObj.value("code");//返回的代码,因为是double类型的所以不能转换成QString
    if (code == 200) {
        QJsonObject dataObject = rootObj.value("data").toObject();
        result = dataObject.value("records").toArray();
        return result;
    }
    return result;
}

void VideoUploadDialog::refreshProject(){
    qDebug()<<"RefreshProject";
    ui->project_list->clear();
    QJsonArray project_result = VideoUploadDialog::getProjectList();
    if(!project_result.isEmpty()){
        for (const QJsonValue &recordValue : project_result) {
            QJsonObject recordObject = recordValue.toObject();
            qDebug()<<"recordObject:"<<recordObject;
            int id = recordObject["id"].toInt();
            qDebug()<<"id:"<<id;
            QString name = recordObject["name"].toString();
            qDebug()<<"name:"<<name;
            ui->project_list->addItem(name, QVariant::fromValue(KeyValuePair{id, name}));
        }
    }
    ui->project_list->update();
}

void VideoUploadDialog::uploadFile(){

    // 文件名称
    QString filename = ui->video_rename->text();
    qDebug()<< "文件名称:" << filename;
    if(filename.isEmpty())
    {
        qDebug() << "name is empty";
        Common::errDialog("双目影片名称不能为空");
        return;
    }

    // 当前所选项目ID
    // 获取当前选中的键值对
    QVariant currentData = ui->project_list->currentData();
    if(currentData.isNull()){
        qDebug() << "currentData is empty";
        Common::errDialog("请选择项目");
        return;
    }
    KeyValuePair selectedPair = currentData.value<KeyValuePair>();
    qDebug() << "当前所选项目ID:" << selectedPair.key << ", 当前所选项目名称:" << selectedPair.value;
    qDebug()<< "压缩目录:" << m_directoryPath;
    qDebug()<< "压缩文件保存目录:" << m_outputFilePath;
    QString outputFilePathName = m_outputFilePath+"/"+filename+".zip";
    qDebug()<< "压缩后zip文件:" << outputFilePathName;
    bool r = Common::compressDirectory(m_directoryPath, outputFilePathName);
    qDebug()<< "文件压缩结果："<<r;

    // TODO文件上传（进度条）

    return;
}

void VideoUploadDialog::createProject() {
    m_CreateProjectDialog->setToken(m_token);
    qDebug()<<"m_token:"<<m_token;
    m_CreateProjectDialog->show();
}

VideoUploadDialog::~VideoUploadDialog() { delete ui; }
