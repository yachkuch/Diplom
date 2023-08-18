#include "mainwindow.h"
#include <QLoggingCategory>
#include <QApplication>

#include "logger.h"

QScopedPointer <QFile> log_file;

void messageHendler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream str(log_file.data());
    if(log_file!=nullptr){
        str<<QDateTime::currentDateTime().toString()<<"";
        str<<type<<" "<<context.category<<" "<<msg<<"\n";
        str.flush();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    log_file.reset(new QFile ("./log.txt"));
    log_file.data()->remove();
    log_file.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHendler);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
