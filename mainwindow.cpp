#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph_qwidget.h"
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graph->resize(480,480);
    result = 1;
    timerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    on_transTranslateBtn_clicked(0,-1);
    checkParity();
}
void MainWindow::on_transShearBtn_clicked(float hX, float hY)
{

    QVector<QPair<int,int>>::iterator it;
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        int x = it->first;
        int y = it->second;
        it->first = x + hX*y;
        it->second = y + hY*x;
    }
    ui->graph->repaint();
}

void MainWindow::on_transScaleBtn_clicked(float sX, float sY)
{
    QVector<QPair<int,int>>::iterator it;
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        it->first *= sX;
        it->second *= sY;
    }
    ui->graph->repaint();
}

void MainWindow::on_transTranslateBtn_clicked(float tX,float tY)
{
    QVector<QPair<int,int>>::iterator it;
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        it->first += tX;
        it->second += tY;
    }
    ui->graph->repaint();
}

void MainWindow::onTimerSignal(){
    on_transTranslateBtn_clicked(0,-1);
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(result==1){
        switch (QString::number(ev->key()).toInt()) {
            case 16777236:
                //Right arrow
                on_transTranslateBtn_clicked(1,0);
                break;
            case 16777234:
                //Left arrow
                on_transTranslateBtn_clicked(-1,0);
                break;
            case 16777237:
                //Left arrow
                on_transTranslateBtn_clicked(0,-1);
                break;
            case 32:
                //space bar
                on_transRotBtn_clicked(90);
                break;
            }
        checkParity();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
//    qDebug()<<"You Release Key " + QString::number(ev->key());
}

void MainWindow::checkParity(){
    int parity[20][4];
    for(int i = 0; i < 20 ; i++)
        for(int j = 0; j < 4 ; j++)
            parity[i][j] = 0;
    // y += 10
    // x += 10
    QVector<QPair<int,int>>::iterator it;
    for(it =  ui->graph->destination.begin(); it != ui->graph->destination.end() ; ++it){
        parity[it->first+9][it->second+10]++;
    }
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        if(it->first>-8 && it->first<11 && it->second>-12 && it->second<-6)
            parity[it->first+9][it->second+10]++;
    }
    int count1 = 0;
    int count0 = 0;
    int countInv = 0;
    for(int i = 0; i < 20 ; i++)
        for(int j = 0; j < 4 ; j++)
            switch (parity[i][j]) {
                case 0:
                    count0++;
                    break;
                case 1:
                    count1++;
                    break;
                default:
                    countInv++;
            }
    if(countInv>0){
        killTimer(timerId);
        result = -1;
        QMessageBox msgBox;
        msgBox.setText("Oops! You lost");
        msgBox.exec();
    }
    if(count1+count0==20*4){
        if(count1==80){
            killTimer(timerId);
            result = 0;
            QMessageBox msgBox;
            msgBox.setText("Hurray!! You won");
            msgBox.exec();
        }
    }
}

void MainWindow::on_transRotBtn_clicked(int deg)
{
    float c = 0;
    float s = 1;
    int cx,cy;
    cx=cy=0;
    QVector<QPair<int,int>>::iterator it;
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        cx += it->first;
        cy += it->second;
    }
    cx /= ui->graph->target.size();
    cy /= ui->graph->target.size();
    for(it =  ui->graph->target.begin(); it != ui->graph->target.end() ; ++it){
        int x = it->first-cx;
        int y = it->second-cy;
        it->first = x*c - y*s + cx;
        it->second = x*s + y*c + cy;
    }
    ui->graph->repaint();
}

