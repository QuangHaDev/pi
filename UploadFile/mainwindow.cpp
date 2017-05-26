#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->uploadBtn, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));
    connect(ui->chooseBtn, SIGNAL(clicked(bool)), this, SLOT(chooseImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseImage(){
    QPixmap image("D:/avatar.png");
    ui->label->setPixmap(image);
}

void MainWindow::on_pushButton_clicked()
{
//    http = new QHttp(this); // http declared as a member of MainWindow class
//    connect(http, SIGNAL(requestFinished(int,bool)), SLOT(httpRequestFinished(int, bool)));

//    QString boundary = "---------------------------723690991551375881941828858";

//    // action
//    QByteArray data(QString("--" + boundary + "\r\n").toAscii());
//    data += "Content-Disposition: form-data; name=\"action\"\r\n\r\n";
//    data += "file_upload\r\n";

//    // file
//    data += QString("--" + boundary + "\r\n").toAscii();
//    data += "Content-Disposition: form-data; name=\"sfile\"; filename=\"avatar.png\"\r\n";
//    data += "Content-Type: image/jpeg\r\n\r\n";

//    QFile file("D:/avatar.png");
//    if (!file.open(QIODevice::ReadOnly))
//        return;

//    data += file.readAll();
//    data += "\r\n";

//    // password
//    data += QString("--" + boundary + "\r\n").toAscii();
//    data += "Content-Disposition: form-data; name=\"password\"\r\n\r\n";
//    //data += "password\r\n"; // put password if needed
//    data += "\r\n";

//    // description
//    data += QString("--" + boundary + "\r\n").toAscii();
//    data += "Content-Disposition: form-data; name=\"description\"\r\n\r\n";
//    //data += "description\r\n"; // put description if needed
//    data += "\r\n";

//    // agree
//    data += QString("--" + boundary + "\r\n").toAscii();
//    data += "Content-Disposition: form-data; name=\"agree\"\r\n\r\n";
//    data += "1\r\n";

//    data += QString("--" + boundary + "--\r\n").toAscii();

//    QHttpRequestHeader header("POST", "/upload");
//    header.setValue("Host", "192.168.1.141:8080");
//    header.setValue("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.1.9) Gecko/20100401 Ubuntu/9.10 (karmic) Firefox/3.5.9");
//    header.setValue("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
//    header.setValue("Accept-Language", "en-us,en;q=0.5");
//    header.setValue("Accept-Encoding", "gzip,deflate");
//    header.setValue("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
//    header.setValue("Keep-Alive", "300");
//    header.setValue("Connection", "keep-alive");
//    header.setValue("Referer", "192.168.1.141:8080");

//    //multipart/form-data; boundary=---------------------------723690991551375881941828858

//    header.setValue("Content-Type", "multipart/form-data; boundary=" + boundary);
//    header.setValue("Content-Length", QString::number(data.length()));

//    http->setHost("192.168.1.141:8080");
//    http->request(header, data);

//    file.close();

    sendfile();
}

void MainWindow::sendfile()
{

    QFile file("D:/avatar.png"); //lets get the file by filename
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))             //accessibility controll for file
    {
        qDebug() << "file open failure";   //send message if file cant open
    }
    QByteArray line;   //a qbytearray object for read file line by line
    while (!file.atEnd())
    {
        line.append(file.readLine());
    }
       //we read file line by line with no error handling for reading time!!

    file.close();
    QByteArray boundary;  //actually i cant understand that why we are using a second byte array for file sending.
// if someone know this trick please write below. I write this code like the other examples.

    QByteArray datas(QString("--" + boundary + "\r\n").toLatin1());
    datas += "Content-Disposition: form-data; name=\"file\"; filename=\""+file.fileName()+"\"\r\n";
//here is the http header for manuplate a normal http form and form file object

    datas += "Content-Type: image/jpeg\r\n\r\n"; //file type is here
    datas += line; //and our file is giving to form object
    datas += "\r\n";
    datas += QString("--" + boundary + "\r\n\r\n").toLatin1();
    datas += "Content-Disposition: form-data; name=\"upload\"\r\n\r\n";
    datas += "Uploader\r\n";
    datas += QString("--" + boundary + "--\r\n").toLatin1();

    QNetworkRequest req;
    req.setUrl(QUrl("http://192.168.1.141:8080/upload"));    //my virtual servers' ip address and tiny php page url is here
    req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + boundary);  // we must set the first header like this. its tell the server, current object is a form

    QNetworkAccessManager *manager = new QNetworkAccessManager;     //using qnetwork access manager for post data

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(erroron_filesend(QNetworkReply*)));    //connecting manager object for errors here
    manager->post(req,datas); //send all data

}

void MainWindow::erroron_filesend(QNetworkReply *replye)
{
    if (replye->error() !=0)
        {
            ui->label_2->setText(replye->errorString());
            return;
        }
        else
        {
            ui->label_2->setText(QString(replye->read(2048)));
            return;
        }
}

//void MainWindow::httpRequestFinished(int, bool)
//{
//    QHttpResponseHeader responce = http->lastResponse();
//    if (responce.statusCode()==302)
//    {
//        qDebug() << "file accepted; get it from:";
//        qDebug() << "data.cod.ru" << responce.value("Location");
//    }
//}
