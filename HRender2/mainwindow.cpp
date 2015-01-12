#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    ui->textEdit->append("hello... again!!!");

    HScene scene;
    scene.polygons = HScene::loadObj("/Users/Alexander/Desktop/chips.obj");
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
//    scene.polygons.removeFirst();
    scene.lamps.append(QVector3D(5, 10, 5));
//    scene.lamps.append(QVector3D(4, 4, 0));

    QMatrix4x4 m;
    m.translate(0, 0, -10);
    m.rotate(30, 1, 0, 0);
    m.rotate(70, 0, 1, 0);

    scene.transform(m);

    int lines = 720;
    HTracer2 tracer;
    tracer.setScene(scene);
    tracer.setImageSize(QSize(lines * 16 / 9, lines));
    tracer.setCameraFrustum(HFrustum(-0.5 * 16 / 9, 0.5 * 16 / 9, -0.5, 0.5, 1, 100));
    tracer.setTileSize(QSize(64, 64));

    connect(&tracer, SIGNAL(imageUpdate(QImage)), this, SLOT(onPictureUpdate(QImage)));

    tracer.render();
}

void MainWindow::onPictureUpdate(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    QCoreApplication::processEvents();
}
