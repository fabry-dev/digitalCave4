#include <QApplication>
#include "qwindow.h"
#include "qscreen.h"
#include "qwidget.h"
#include "touchscreen.h"
#include "ledscreen.h"
#include "qdebug.h"
#include "QPushButton"
#include "qmessagebox.h"
#include "tcpserverlistener.h"
#include "udplistener.h"

#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/PTL/ImmersiveRoom/kiosk4/files/"



#include "alphaVideoPlayer.h"




int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QString PATH;

    QStringList params = a.arguments();
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;

    bool HIDE_CURSOR=false;
    bool DEBUG=false;

    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";

    }
    else
    {

        QTextStream in(&file);

        QString  line;
        QString paramName,paramValue;
        QStringList params;


        while(!in.atEnd()) {
            line = in.readLine();
            line = (line.split("#"))[0];
            params = line.split("=");
            if(params.size()>=2)
            {
                paramName = params[0];
                paramValue = params[1];

                if (paramName.mid(0,6)=="CURSOR")
                    HIDE_CURSOR = (paramValue=="NO");
                else if (paramName.mid(0,5)=="DEBUG")
                    DEBUG = (paramValue=="YES");
                else
                    qDebug()<<paramName<<" - "<<paramValue;
            }
        }
        file.close();

    }




    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        a.setOverrideCursor(cursor);
        a.changeOverrideCursor(cursor);
    }


    udpListener *socket = new udpListener(NULL);

    touchScreen *ts = new touchScreen(NULL,PATH);
    ts->setGeometry(a.screens()[2]->geometry().x(),a.screens()[2]->geometry().y(),1080,1920);
    ts->showFullScreen();


    ledScreen * ls = new ledScreen(NULL,PATH);
    ls->setGeometry(a.screens()[1]->geometry().x(),a.screens()[1]->geometry().y(),960,1152);
    ls->showFullScreen();

    a.connect(ls,SIGNAL(bgRestart()),ts,SIGNAL(bgShouldRestart()));

    a.connect(ts,SIGNAL(buttonsGo()),ls,SLOT(showButtons()));
    a.connect(ts,SIGNAL(buttonsCome()),ls,SLOT(hideButtons()));
    a.connect(socket,SIGNAL(startVideo()),ls,SLOT(startVideo()));
    a.connect(socket,SIGNAL(stopVideo()),ls,SLOT(stopVideo()));


    return a.exec();

}
