#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;
VideoCapture cap(0);
Mat frame;
Mat result;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
char text[100];
vector<Mat> light(3);
int erod;
QImage Mat2QImage(const cv::Mat3b &src) {
        QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
        for (int y = 0; y < src.rows; ++y) {
                const cv::Vec3b *srcrow = src[y];
                QRgb *destrow = (QRgb*)dest.scanLine(y);
                for (int x = 0; x < src.cols; ++x) {
                        destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
                }
        }
        return dest;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(videoUpdate()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(changeEroded()));
    timer->setInterval(100);
    timer->start();
}
void MainWindow::videoUpdate(){
    cap>>frame;
    split(frame,light);
    threshold(light[0],light[0],200,255,THRESH_BINARY);
    threshold(light[1],light[1],200,255,THRESH_BINARY);
    threshold(light[2],light[2],200,255,THRESH_BINARY);
    bitwise_and(light[0],light[1],result);
    bitwise_and(result,light[2],result);
    erode(result, result,Mat(),Point(-1,-1),erod);
    blur(result,result,Size(9,9),Point(-1,-1));
    cvtColor(result, result, CV_GRAY2BGR);
    QImage image= Mat2QImage(result);
    ui->label->setPixmap(QPixmap::fromImage(image));
    cvtColor(result,result,CV_RGB2GRAY);
    findContours( result, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    /// Get the moments
    vector<Moments> mu(contours.size() );
    for( unsigned int i = 0; i < contours.size(); i++ )
    { mu[i] = moments( contours[i], false ); }
    ///  Get the mass centers:
    vector<Point2f> mc( contours.size() );
    for( unsigned int i = 0; i < contours.size(); i++ )
    { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
    /// Draw contours;
    for( unsigned int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( 255,0,255 );
        if(( contours[i].size() > 70 )&&(contourArea(contours[i])>700)){
            sprintf(text, "x=%d,y=%d",(int)mc[i].y,(int)mc[i].x );
            putText(frame, text, mc[i], FONT_HERSHEY_PLAIN, 1.0, Scalar(255,0,0));
            circle(frame, mc[i], 4, Scalar(255,0,0),1,8);
            ellipse(frame, fitEllipse(contours[i]), color, 2, 8);
        }
    }
    QImage image2= Mat2QImage(frame);
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
}
void MainWindow::changeEroded(){
    erod=ui->horizontalSlider->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}
