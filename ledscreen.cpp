#include "ledscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qthread.h"
#include "qlayout.h"

#include "qmediaplayer.h"

#include "positions.h"




ledScreen::ledScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{

    resize(960,1152);

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(true);
    bgVp->show();

    connect(bgVp,SIGNAL(videoRestart()),this,SIGNAL(bgRestart()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setMute(true);
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->show();




    QTimer::singleShot(10,this,SLOT(loadPlayer()));

    int offsets[10] = {0,1,2,1,0,0,1,2,1,0};

    QString bxs,bys,bws,bhs;

    for(int i = 0;i<10;i++)
    {
        QPixmap bPix(PATH+"button/"+QString::number(i)+".png");
        bPix = bPix.scaled((double)bPix.width()*ledPixRatio,(double)bPix.height()*ledPixRatio);
        double hTotal = (double)1920*Touch2LedRatio*2;
        double delta_y = (double)(hTotal-bPix.height()*5)/4;
        double y0 = (double)(height()-hTotal)/2;
        int by = y0 +  (delta_y+bPix.height())*((i%5)) ;
        int sign = 2*(i>=5)-1;
        int bx = width()/2+sign*(1080*Touch2LedRatio+offsets[i]*bPix.width()*0.6-bPix.width()/2)-bPix.width()/2;

        QRect showG = QRect(bx,by,bPix.width(),bPix.height());
        QRect hideG = QRect(bOffsetX+(i/5)*(bSpacingX+bPix.width()/ledPixRatio),450+(i%5)*(bPix.height()/ledPixRatio+bOffsetY),bPix.width()/ledPixRatio,bPix.height()/ledPixRatio);


        powerLabel * b = new powerLabel(this,0,touch2led(hideG),showG,false,false);
        b->setPixmap(bPix);
        b->setScaledContents(true);


        buttons.push_back(b);

        bxs+=QString::number(showG.x())+",";
        bys+=QString::number(showG.y())+",";
        bws+=QString::number(showG.width())+",";
        bhs+=QString::number(showG.height())+",";
    }

    qDebug()<<bxs;
    qDebug()<<bys;
    qDebug()<<bws;
    qDebug()<<bhs;

    QLabel *touchLbl = new QLabel(this);
    touchLbl->resize(1080*Touch2LedRatio,1920*Touch2LedRatio);
    touchLbl->move((width()-touchLbl->width())/2,(height()-touchLbl->height())/2);
    touchLbl->setStyleSheet("border: 1px solid red");
    touchLbl->show();




}

void ledScreen::loadPlayer()
{
    bgVp->lower();
    bgVp->loadFilePaused(PATH+"ledBg4.mp4");
    bgVp->play();

    introVp->lower();
   introVp->loadFilePaused(PATH+"ledIntro4.mp4");
}




void ledScreen::showButtons(void)
{

    for(auto b:buttons)
        b->animateShow();


}

void ledScreen::hideButtons(void)
{

    for(auto b:buttons)
        b->animateHide();
}




void ledScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void ledScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}




QRect ledScreen::touch2led(QRect original)
{

    double offsetX = (width()-1080*Touch2LedRatio)/2;
    double offsetY = (height()-1920*Touch2LedRatio)/2;


    return QRect((double)original.x()*Touch2LedRatio+offsetX,(double)original.y()*Touch2LedRatio+offsetY,(double)original.width()*Touch2LedRatio,(double)original.height()*Touch2LedRatio);

}






void ledScreen::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == 16777216)
        exit(0);



    //qDebug()<<ev->key();
}



