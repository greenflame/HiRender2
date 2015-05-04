#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isSceneLoaded = false;
    isPreviewRendered = false;
    xRot = 0;
    yRot = 0;

    resultSize = QSize(1280, 720) / 2;
    previewScale = 0.1;
    distanceFromCenter = 10;

    QTimer *previewUpdateTimer = new QTimer(this);
    connect(previewUpdateTimer, SIGNAL(timeout()), this, SLOT(previewUpdate()));
    previewUpdateTimer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_loadScene_clicked()
{
    SScene scene;
    scene.clear();
    QString fileName = QFileDialog::getOpenFileName(this);
    scene.loadObj(fileName);
    scene.lights.append(QVector3D(2, -1, 5));

    scene.copyToTracer(tracer);

    float k = 16.0 / 9.0;
    tracer.setCameraFrustum(HFrustum(-0.5 * k, 0.5 * k, -0.5, 0.5, 4, 100));

    isSceneLoaded = true;
}

void MainWindow::on_pushButton_render_clicked()
{
    // Defenition
    tracer.setImageSize(resultSize);
    tracer.setTileSize(QSize(128, 128));

    QMatrix4x4 m;
    m.translate(0, 0, -distanceFromCenter);
    m.rotate(yRot, 1, 0, 0);
    m.rotate(xRot, 0, 1, 0);
    tracer.setCameraMatrix(m);

    connect(&tracer, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    connect(&tracer, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));

    ui->textEdit_output->clear();
    QImage result = tracer.render();

    ui->label_renderOutput->setPixmap(QPixmap::fromImage(result));

    disconnect(&tracer, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    disconnect(&tracer, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));
}

void MainWindow::on_pushButton_test_clicked()
{
    HTracer3 tracer3;

    // Frustum
    tracer3.setCameraFrustum(HFrustum(-1, 1, -0.5, 0.5, 4, 1000));
    tracer3.setImageSize(QSize(1920, 1080) / 2);

    // Geometry
    SScene s;
    QString fileName = QFileDialog::getOpenFileName(this);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);


    QMatrix4x4 m;
    m.translate(0, 0, -7);
//    m.rotate(30, 1, 0, 0);
//    m.rotate(30, 0, 1, 0);

    tracer3.addPointLight(QVector3D(4, 6, 4));
    tracer3.setCameraMatrix(m);

    tracer3.setRayLifeTime(8);

    tracer3.addTexture("skyTexture", QImage("/Users/Alexander/Desktop/pano1.jpg"));

    tracer3.addPhongShader("ps", Qt::red);
    tracer3.addAmbientOcclusionShader("ao", 4, Qt::gray);
    tracer3.addMirrorShader("ms", 0, 1);

    tracer3.addRefractionShader("rs", 1.44);

    tracer3.addMixShader("ms1", "rs", "ps", 1, 1);
    tracer3.addMixShader("ms2", "ms1", "ms", 1, 2);

    s.loadObj(fileName);
    s.copyToTracer(tracer3, "rs");


    connect(&tracer3, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    connect(&tracer3, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));

    ui->textEdit_output->clear();
    QImage result = tracer3.render();
    ui->label_renderOutput->setPixmap(QPixmap::fromImage(result));
    result.save("result.png");
}

void MainWindow::onTemporaryImageUpdated(QImage image)
{
    ui->label_renderOutput->setPixmap(QPixmap::fromImage(image));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::onRenderMessage(QString message)
{
    ui->textEdit_output->append(message);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::previewUpdate()
{
    if (!isSceneLoaded)
    {
        xRot = 0;
        yRot = 0;
        return;
    }

    if (isPreviewRendered == false)
    {
        tracer.setImageSize(resultSize * previewScale);
        tracer.setTileSize(QSize(10000, 10000));

        QMatrix4x4 m;
        m.translate(0, 0, -distanceFromCenter);
        m.rotate(yRot, 1, 0, 0);
        m.rotate(xRot, 0, 1, 0);
        tracer.setCameraMatrix(m);

        QImage result = tracer.render();
        result = result.scaled(resultSize);
        ui->label_renderOutput->setPixmap(QPixmap::fromImage(result));

        isPreviewRendered = true;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    xPrev = event->x();
    yPrev = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    xRot += event->x() - xPrev;
    yRot += event->y() - yPrev;

    xPrev = event->x();
    yPrev = event->y();

    isPreviewRendered = false;
}
