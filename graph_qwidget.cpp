#include "graph_qwidget.h"
#include "mainwindow.h"
#include <cstdlib>

graph_qWidget::graph_qWidget(QWidget *parent) : QWidget(parent)
{
    ker = 24;
    brushColorIdx = 0;    
    initiateGame();
}
int graph_qWidget::linearSearch(int x,int y){    
    for(int i=points.size()-1;i>-1;i--){
        QPair<QPair<int,int>, int>  it = points[i];
        if(it.first.first == x && it.first.second == y)
            return it.second;
    }
    return -1;
}
bool graph_qWidget::linearSearchDest(int x,int y){
    for(int i=destination.size()-1;i>-1;i--){
        QPair<int,int>  it = destination[i];
        if(it.first == x && it.second == y)
            return true;
    }
    return false;
}
bool graph_qWidget::linearSearchTarget(int x,int y){
    for(QPair<int,int>  it : target){
        if(it.first == x && it.second == y)
            return true;
    }
    return false;
}

void graph_qWidget::generateTarget(int i, int j){
    if(j<-6 && !linearSearchDest(i,j) && !linearSearchTarget(i,j) && i>-9 && i<11){
        target.push_back(qMakePair(i,j));
        generateTarget(i-1,j);
        generateTarget(i,j+1);
        generateTarget(i+1,j);
    }
}

void graph_qWidget::initiateGame(){
    QPair<int, int > t;
    srand(time(0));
    static int randTemp = rand()%15-5;
    for(int i = -9;i<11;i++){
        if(i != randTemp) destination.push_back(qMakePair(i,-9));
        destination.push_back(qMakePair(i,-10));
    }
    for(int j = -8 ; j <-6;j++){
        for(int i = -9;i<11;i++){
            if(!linearSearchDest(i,j-1)){
                srand(i*j);
                switch (rand()%3) {
                case 0:
                    i+=2;
                    break;
                case 1:
                    destination.pop_back();
                    i+=1;
                    break;
                case 2:
                    destination.pop_back();
                    i += 1;
                    break;
                }
            }
            else{
                destination.push_back(qMakePair(i,j));
            }
        }
    }
    generateTarget(randTemp,-9);
    QVector<QPair<int,int>>::iterator it;

    srand(time(0));
    int randTempX = -randTemp;
    int randTempY = 18;
    for(it =  target.begin(); it != target.end() ; ++it){
        it->first += randTempX;
        it->second += randTempY;
    }
}

void graph_qWidget::paintEvent(QPaintEvent *pe) {
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
    int size = this->width();
    int half = size/2;
    QVector<QPair<QPair<int,int>, int> >::iterator it;
    QColor brushColor;
    for(it =  points.begin(); it != points.end() ; ++it){
        switch (it->second) {
        case 0:
            brushColor = Qt::yellow;
            break;
        case 1:
            brushColor = Qt::red;
            break;
        case 2:
            brushColor = Qt::black;
            break;
        case 3:
            brushColor = Qt::blue;
            break;
        case 4:
            brushColor = Qt::white;
            break;
        }
        painter.setPen(QPen(brushColor, ker, Qt::SolidLine));
        painter.drawPoint(ker*it->first.first + width()/2-ker/2,height()/2 -  ker*it->first.second-ker/2);
    }
    QVector<QPair<int,int>>::iterator it2;
    for(it2 =  destination.begin(); it2 != destination.end() ; ++it2){
        switch (3) {
        case 0:
            brushColor = Qt::yellow;
            break;
        case 1:
            brushColor = Qt::red;
            break;
        case 2:
            brushColor = Qt::black;
            break;
        case 3:
            brushColor = Qt::blue;
            break;
        case 4:
            brushColor = Qt::white;
            break;
        }
        painter.setPen(QPen(brushColor, ker, Qt::SolidLine));
        painter.drawPoint(ker*it2->first + width()/2-ker/2,height()/2 -  ker*it2->second-ker/2);
    }
    QVector<QPair<int,int>>::iterator it3;
    for(it3 =  target.begin(); it3 != target.end() ; ++it3){
        switch (2) {
        case 0:
            brushColor = Qt::yellow;
            break;
        case 1:
            brushColor = Qt::red;
            break;
        case 2:
            brushColor = Qt::black;
            break;
        case 3:
            brushColor = Qt::blue;
            break;
        case 4:
            brushColor = Qt::white;
            break;
        }
        painter.setPen(QPen(brushColor, ker, Qt::SolidLine));
        painter.drawPoint(ker*it3->first + width()/2-ker/2,height()/2 -  ker*(it3->second)-ker/2);
    }
    if ( ker==1 ){
        painter.setPen(QPen(Qt::green, ker, Qt::DotLine));
        painter.drawLine(half,0,half,size);
        painter.drawLine(0,half,size,half);
    }
    else {
        for(int i = -1*half; i<=half; i+=1){
            if (abs(i)%ker!=0)
                continue;
            painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
            painter.drawLine(i+half,0,i+half,size);
            painter.drawLine(0,i+half,size,i+half);
        }
    }
}
