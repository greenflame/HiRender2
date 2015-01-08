#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->append("hello... again!!!");

    HModel model = HModel::loadObj("/Users/Alexander/Desktop/simple cube.obj");

    QMatrix4x4 m;
    m.translate(0, 0, -20);
    m.rotate(45, 1, 0, 0);
    m.rotate(30, 0, 1, 0);

    model.transform(m);

    HTracer tracer;
    tracer.polygons = model.polygons;

    QImage img = tracer.traceRays(600, 600, -0.5, 0.5, -0.5, 0.5, 1);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
