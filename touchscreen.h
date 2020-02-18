#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"
#include "alphaVideoPlayer.h"
#include "QPropertyAnimation"
#include "powerLabel.h"
class touchScreen : public QLabel
{
    Q_OBJECT
public:
    explicit touchScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp;
    std::vector<powerLabel*>buttons;
    std::vector<powerLabel*>titles;
    std::vector<powerLabel*>contents;

    powerLabel * titleLbl,*backLbl,*achievementsLbl;
    QRect led2screen(QRect original);
    int activeContent;

private slots:
    void loadPlayer(void);
    void buttonClick(void);
    void showButtons(void);
    void hideButtons(void);
    void showContent(void);
    void goBack(void);

signals:
    void bgShouldRestart(void);
    void buttonsGo(void);
    void buttonsCome(void);
    void buttonsGone(void);


};

#endif // MAINSCREEN_H
