#ifndef LEDSCREEN_H
#define LEDSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "alphaVideoPlayer.h"
#include "qtimer.h"
#include "yearbuttons.h"
#include "powerLabel.h"


class ledScreen : public QLabel
{
    Q_OBJECT
public:
    explicit ledScreen(QLabel *parent = nullptr, QString PATH="");

private:
    QString PATH;
    mpvWidget *bgVp;
    std::vector<powerLabel*>buttons;
    QRect touch2led(QRect original);

private slots:
    void loadPlayer(void);
    void startVideo(void);
    void stopVideo(void);
    void showButtons(void);
    void hideButtons(void);

signals:
    void bgRestart(void);

protected:
     void keyPressEvent(QKeyEvent *ev);
};

#endif // LEDSCREEN_H
