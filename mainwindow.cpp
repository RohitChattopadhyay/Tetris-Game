#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph_qwidget.h"
#include <QThread>
#define insertPoint(x,y) ui->graph->points.push_back(QPair<QPair<int , int>,int >(QPair< int , int >(x,y),ui->graph->brushColorIdx))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graph->resize(480,480);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    qDebug()<<"You Pressed Key " + QString::number(ev->key());
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
        //down arrow
        on_transTranslateBtn_clicked(0,-1);
        break;
    case 32:
        //down arrow
        on_transRotBtn_clicked(90);
        break;
    default:
        on_transTranslateBtn_clicked(0,1);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug()<<"You Release Key " + QString::number(ev->key());
}

void MainWindow::on_transRotBtn_clicked(int deg)
{
//    float rad = deg*0.0174533;
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
