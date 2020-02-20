#include "touchscreen.h"
#include "math.h"
#include "qdebug.h"

#include "positions.h"


#define TIMEOUT_DELAY 30*1000

touchScreen::touchScreen(QLabel *parent, QString PATH) : QLabel(parent),PATH(PATH)
{
    resize(1080,1920);

    timeOutTimer = new QTimer(this);
    connect(timeOutTimer,SIGNAL(timeout()),this,SLOT(goBack()));

    bgVp = new mpvWidget(this);
    bgVp->resize(size());
    bgVp->setProperty("keep-open","yes");
    bgVp->setLoop(false);
    bgVp->show();

    connect(this,SIGNAL(bgShouldRestart()),bgVp,SLOT(rewindAndPlay()));


    introVp = new mpvWidget(this);
    introVp->resize(size());
    introVp->setProperty("keep-open","yes");
    introVp->setLoop(false);
    introVp->lower();
    introVp->setMute(true);
    introVp->show();

    QTimer::singleShot(10,this,SLOT(loadPlayer()));

    QLabel *iktvaLbl = new QLabel(this);
    QImage iktva(PATH+"iktva.png");
    iktvaLbl->resize(iktva.size());
    iktvaLbl->setPixmap(QPixmap::fromImage(iktva));
    iktvaLbl->move((width()-iktvaLbl->width())/2,1920-iktvaLbl->height()/2-100);
    iktvaLbl->show();

    QPixmap title(PATH+"title.png");
    titleLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-title.width())/2,50,title.width(),title.height()));
    titleLbl->setPixmap(title);
    titleLbl->setScaledContents(true);
    titleLbl->animateShow();


    int backY = 1500;
    QPixmap pix(PATH+"back.png");
    backLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-pix.width())/2,backY,pix.width(),pix.height()),true);
    backLbl->hide();
    backLbl->setPixmap(pix);
    backLbl->setScaledContents(true);
    connect(backLbl,SIGNAL(clicked()),this,SLOT(goBack()));
    connect(backLbl,SIGNAL(hideAnimationOver()),this,SLOT(showButtons()));



    int achievementsY = 350;
    QPixmap pixA(PATH+"achievements.png");
    achievementsLbl = new powerLabel(this,0,QRect(width()/2,0,0,0),QRect((width()-pixA.width())/2,achievementsY,pixA.width(),pixA.height()),true);
    achievementsLbl->hide();
    achievementsLbl->setPixmap(pixA);
    achievementsLbl->setScaledContents(true);






    QString bufx,bufy;
    for(int i = 0;i<10;i++)
    {
        QPixmap bPix(PATH+"button/"+QString::number(i)+".png");
        QRect showG = QRect(bOffsetX+(i/5)*(bSpacingX+bPix.width()),450+(i%5)*(bPix.height()+bOffsetY),bPix.width(),bPix.height());

        QRect hideG = led2screen(QRect(buttonLedX[i],buttonLedY[i],buttonLedW[i],buttonLedH[i]));

        powerLabel * b = new powerLabel(this,i,hideG,showG);
        b->setPixmap(bPix);
        b->setScaledContents(true);
        b->animateShow();
        connect(b,SIGNAL(clicked()),this,SLOT(buttonClick()));

        bufx+=QString::number( bOffsetX+(i/5)*(bSpacingX+bPix.width()))+",";
        bufy+=QString::number(450+(i%5)*(bPix.height()+bOffsetY))+",";
        buttons.push_back(b);

    }
    connect(buttons[0],SIGNAL(hideAnimationOver()),this,SLOT(showContent()));





    int contentY = 750;

    for(int i = 0;i<10;i++)
    {
        QPixmap cPix(PATH+"contents/"+QString::number(i)+".png");
        powerLabel *c = new powerLabel(this,i,QRect(width()/2,0,0,0),QRect((width()-cPix.width())/2,(height()-cPix.height())/2,cPix.width(),cPix.height()),false);
        c->setPixmap(cPix);
        c->setScaledContents(true);
        contents.push_back(c);
    }

    int titleY = 460;

    for(int i = 0;i<10;i++)
    {
        QPixmap tPix(PATH+"titles/"+QString::number(i)+".png");
        powerLabel *t = new powerLabel(this,i,QRect(width()/2,0,0,0),QRect((width()-tPix.width())/2,titleY,tPix.width(),tPix.height()),false);
        t->setPixmap(tPix);
        t->setScaledContents(true);
        titles.push_back(t);
    }





}




void touchScreen::showButtons()
{
    emit buttonsCome();

    for(auto b:buttons)
        b->animateShow();

    titleLbl->animateShow();
}


void touchScreen::hideButtons()
{
    emit buttonsGo();

    for(auto b:buttons)
        b->animateHide();

    titleLbl->animateHide();
}

void touchScreen::goBack()
{
    backLbl->animateHide();
    achievementsLbl->animateHide();
    titles[activeContent]->animateHide();
    contents[activeContent]->animateHide();
    timeOutTimer->stop();
}


void touchScreen::buttonClick(void)
{

    hideButtons();
    activeContent = ((powerLabel*)QObject::sender())->getId();
    timeOutTimer->start(TIMEOUT_DELAY);

}


void touchScreen::showContent()
{

    backLbl->animateShow();
    achievementsLbl->animateShow();
    titles[activeContent]->animateShow();
    contents[activeContent]->animateShow();
}



void touchScreen::loadPlayer()
{
    bgVp->loadFilePaused(PATH+"touchBg4.mp4");
    bgVp->play();

    introVp->loadFilePaused(PATH+"touchIntro4.mp4");
}

void touchScreen::startIntroVideo()
{
    introVp->playAndRaise();
    introVp->raise();

}

void touchScreen::stopIntroVideo()
{
    introVp->lower();
    introVp->pause();
    introVp->rewind();
}


QRect touchScreen::led2screen(QRect original)
{
    int nuW = original.width()/Touch2LedRatio;
    int nuH = original.height()/Touch2LedRatio;

    double x2 = (double)(original.x() + original.width()/2   - ledWidth/2)/(Touch2LedRatio)  + width()/2 - nuW/2;
    double y2 = (double)(original.y() + original.height()/2 - ledHeight/2)/(Touch2LedRatio) + height()/2 - nuH/2;


    return QRect(x2,y2,nuW,nuH);
}




