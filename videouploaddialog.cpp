#include "videouploaddialog.h"
#include "./ui_videouploaddialog.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "common.h"
#include <QByteArray>

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

    connect(ui->okcancelButtonBox,&QDialogButtonBox::accepted,this,&VideoUploadDialog::uploadFileEvent);

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

void VideoUploadDialog::uploadFileEvent(){

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
    bool compressDirectoryStatus = Common::compressDirectory(m_directoryPath, outputFilePathName);
    qDebug()<< "文件压缩结果："<<compressDirectoryStatus;
    if(!compressDirectoryStatus){
        Common::errDialog("文件压缩失败");
        return;
    }

    // TODO文件上传（进度条）
    bool uploadStatus = this->uploadFileRequest(m_outputFilePath,filename, selectedPair.key);
    if(!uploadStatus){
        Common::errDialog("文件上传失败");
        return;
    }
    return;
}

/**
 * 文件上传
 * @brief Common::uploadFile
 * @param path
 * @return
 */
bool VideoUploadDialog::uploadFileRequest(QString path, QString filename, int projectId){

    QString filenameZip = filename+".zip";
    QString compressFilePath = path+"/"+filenameZip;

    qDebug()<<"compressFileName:"<<compressFilePath;
    qDebug()<<"path:"<<path<<",filename:"<<filename<<",project:"<<projectId;

    // 创建一个multipart/form-data请求
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //其它参数
    // QHttpPart paramsPart;
    // const QString header = "application/json";
    // paramsPart.setHeader(QNetworkRequest::ContentTypeHeader, header);
    // QJsonObject paramsReq;
    // QJsonDocument paramsDoc;
    // QByteArray paramsData;
    // paramsReq.insert("name",filename);
    // paramsReq.insert("projectId",projectId);
    // paramsDoc = QJsonDocument(paramsReq);
    // paramsData = paramsDoc.toJson();
    // paramsPart.setBody(paramsData);

    // 添加文本参数 name
    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    namePart.setBody(filename.toUtf8());
    multiPart->append(namePart);

    // 添加整数参数 projectId
    QHttpPart projectIdPart;
    projectIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"projectId\""));
    projectIdPart.setBody(QString::number(projectId).toUtf8());
    multiPart->append(projectIdPart);


    // 添加文件
    QFile *file = new QFile(compressFilePath);
    if (!file->exists()) {
        qDebug()<<"文件读取异常:"<<compressFilePath;
        return false;
    }
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return false;
    }

    QHttpPart filePart;
    // filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/zip"));
    // filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+filenameZip+"\""));

    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + QFileInfo(*file).fileName() + "\""));
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // 设置文件对象的父对象，以便其生命周期由multiPart管理
    multiPart->append(filePart);


    //发送请求
    QNetworkRequest request;
    QString fullRequest = "http://123.249.67.68:8998/file/upload/video";

    request.setUrl(QUrl(fullRequest));
    //request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data; boundary="+multiPart->boundary()));
    //request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("multipart/form-data"));

    request.setRawHeader("Source", "app");
    request.setRawHeader("Authorization", m_token.toUtf8());

    qDebug()<< "uploadFile Authorization:"<<m_token.toUtf8();
    // 查看请求头
    qDebug()<<"查看请求头:"<<request.rawHeaderList();


    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, multiPart);

    multiPart->setParent(reply); // 设置multiPart的父对象为reply，以便其生命周期由reply管理

    // 监听上传进度
    QObject::connect(reply, &QNetworkReply::uploadProgress, [](qint64 bytesSent, qint64 bytesTotal){
        qDebug() << "Upload progress:" << bytesSent << "of" << bytesTotal;
    });

    // 处理响应
    // 开启时间循环，直到请求完成
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"请求连接超时";
        qDebug()<< reply->error();
        // 清理资源
        reply->deleteLater();
        return false;
    }



    // QObject::connect(reply, &QNetworkReply::finished, [&](){
    //     if(reply->error() == QNetworkReply::NoError) {
    //         qDebug() << "Upload successful";
    //         qDebug() << "Response:" << reply->readAll();
    //     } else {
    //         qDebug() << "Error:" << reply->errorString();
    //     }
    //     // 清理资源
    //     reply->deleteLater();
    // });


    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<"状态码："<<statusCode.toInt();
    if (statusCode.isValid()) {
        if (statusCode.toInt() != 200) {
            // 请求失败
            qDebug()<<"接口请求返回异常";
            return false;
        }
    }

    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_error.error:"<<json_error.error<<replyData;
        return false;
    }

    QJsonObject rootObj = jsonDoc.object();
    qDebug()<<rootObj;
    QJsonValue code = rootObj.value("code");
    if (code == 200) {
        qDebug() << "成功";
        emit VideoUploadDialog::uploadFileSuccess(filename);
        return true;
    }

    emit VideoUploadDialog::uploadFileError(filename);
    return false;
}


void VideoUploadDialog::createProject() {
    m_CreateProjectDialog->setToken(m_token);
    qDebug()<<"m_token:"<<m_token;
    m_CreateProjectDialog->show();
}

VideoUploadDialog::~VideoUploadDialog() { delete ui; }
