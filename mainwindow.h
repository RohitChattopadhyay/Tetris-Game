#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QtCore/qmath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_transShearBtn_clicked(float,float);
    void on_transScaleBtn_clicked(float,float);
    void on_transTranslateBtn_clicked(float,float);
    void on_transRotBtn_clicked(int);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void checkParity();
    int result; // 1 game on, 0 won, -1 lost

public slots:
    void onTimerSignal();
private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    int timerId;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
