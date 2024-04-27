#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"
#include<QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "common.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProjectDialog)
{
    // *************************实例化数据*************************
    // TODO 实例化token
    QString token = Common::login();
    if(token.isNull()){
        Common::errDialog("登录失败");
        return;
    }
    m_token = token;
    qDebug()<< "CreateProjectDialog token:"<<m_token.toUtf8();

    // 定义新建成功信息提示窗口
    m_succQMessageBox = new QMessageBox(this);

    ui->setupUi(this);
    ui->okcancelButtonBox->button(QDialogButtonBox::Ok)->setText(tr("保存"));
    ui->okcancelButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    connect(ui->okcancelButtonBox,&QDialogButtonBox::accepted,this,&CreateProjectDialog::createProjectRequest);
    // MessageBox 按钮点击
    connect(m_succQMessageBox, &QMessageBox::buttonClicked,this,&CreateProjectDialog::messageClose);
    // MessageBox 窗口关闭
    connect(m_succQMessageBox, &QMessageBox::finished,this,&CreateProjectDialog::messageClose);

}

void CreateProjectDialog::setToken(QString token){
    m_token = token;
}

void CreateProjectDialog::messageClose(){
    qDebug()<<"messageClose event";
    emit CreateProjectDialog::closeCreateProjectWindow();
    this->close();
}

void CreateProjectDialog::createProjectRequest(){
    qDebug() << "createProjectRequest is start";
    QString project_name = ui->project_name->text();
    if(project_name.isEmpty())
    {
        qDebug() << "project_name is empty";
        Common::errDialog("项目名称不能为空");
        return;
    }
    // *********************请求***********************
    QNetworkRequest request;
    QString fullRequest = "http://123.249.67.68:8998/project/add";
    request.setUrl(QUrl(fullRequest));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//因为QT和java的请求头不一致
    request.setRawHeader(QByteArray("Source"), "app");//这里是设置非标准的请求头
    request.setRawHeader("Source", "app");
    request.setRawHeader("Authorization", m_token.toUtf8());
    // 查看请求头
    qDebug()<<request.rawHeaderList();
    //传入josn
    QJsonObject object;
    object.insert("name",project_name);
    QJsonDocument document;
    document.setObject( object );
    QByteArray array = document.toJson( QJsonDocument::Compact);
    qDebug()<<object;
    //发送请求
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request,array);
    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"请求连接超时";
        qDebug()<< reply->error();
        Common::errDialog("请求连接超时");
        return;
    }
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<"状态码："<<statusCode.toInt();
    if (statusCode.isValid()) {
        if (statusCode.toInt() >= 200 && statusCode.toInt() < 300) {
            // 请求成功
        } else {
            // 请求失败
            qDebug()<<"接口请求返回异常";
            Common::errDialog("接口请求返回异常");
            return;
        }
    }
    //解析返回的Json结果
    QByteArray replyData = reply->readAll();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug()<<json_error.error<<replyData;
        Common::errDialog("接口解析异常");
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    qDebug()<<rootObj;
    QJsonValue code = rootObj.value("code");//返回的代码,因为是double类型的所以不能转换成QString
    if (code == 200) {
        qDebug() << "新建成功";
        //TODO刷新videouploaddialog对话框，重新调用接口
        m_succQMessageBox->setParent(0);
        m_succQMessageBox->setIcon(QMessageBox :: Information);
        m_succQMessageBox->setText("新建成功");
        m_succQMessageBox->setWindowTitle("消息");
        m_succQMessageBox->setStyleSheet(R"(
        QLabel
        {
            color: green;
            background: rgbda(85,174,255,100%);
        }
        )");
        m_succQMessageBox->exec();
        return;
    }
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}
