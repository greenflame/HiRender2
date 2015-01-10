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

    HScene scene;
    scene.polygons = HScene::loadObj("/Users/Alexander/Desktop/simple cube.obj");
    scene.lamps.append(QVector3D(5, 5, 5));

    QMatrix4x4 m;
    m.translate(0, 0, -10);
    m.rotate(45, 1, 0, 0);
    m.rotate(30, 0, 1, 0);

    scene.transform(m);

    HTracer2 tracer;
    tracer.setScene(scene);
    int lines = 720;
    tracer.setImageSize(QSize(lines * 16 / 9, lines));
    tracer.setCameraFrustum(HFrustum(-0.5 * 16 / 9, 0.5 * 16 / 9, -0.5, 0.5, 1, 100));

    connect(&tracer, SIGNAL(imageUpdate(QImage)), this, SLOT(on_picture_update(QImage)));

    tracer.render();
}

void MainWindow::on_picture_update(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}
