#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_process_clicked()
{
    HTracer3 tracer3;

    // Image
    tracer3.setImageSize(QSize(1280, 720) * 1);

    // Camera
    QMatrix4x4 m;
    m.translate(0, 0, -10);
    m.rotate(30, 1, 0, 0);
    m.rotate(30, 0, 1, 0);

    tracer3.setCameraMatrix(m);
    float k = 720.f / 1080.f;
    tracer3.setCameraFrustum(HFrustum(-1, 1, -k, k, 2, 1000));

    // Light
    tracer3.addPointLight(QVector3D(4, 6, 4));


    // Shaders

//    tracer3.addTexture("skyTexture", QImage("/Users/Alexander/Desktop/pano1.jpg"));
    tracer3.addPhongShader("ps", Qt::gray);
    tracer3.addAmbientOcclusionShader("ao", 4, Qt::gray);
    tracer3.addMirrorShader("ms", 0, 1);
    tracer3.addRefractionShader("rs", 1.44);

    tracer3.addMixShader("ms1", "ao", "ps", 1, 1);
    tracer3.addMixShader("ms2", "ms1", "ms", 1, 2);

    // Signals
    connect(&tracer3, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    connect(&tracer3, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));

    // Geometry
    QStringList fileQueue = ui->textEdit_queue->toPlainText().split('\n');

    for (int i = 0; i < fileQueue.count(); i++)
    {
        QString currentFile = fileQueue.at(i);

        ui->textEdit_output->append(tr("Rendering %0 / %1").arg(i + 1).arg(fileQueue.count()));

        tracer3.clearColliders();

        SScene s;
        s.loadObj(currentFile);
        s.copyToTracer(tracer3, "ms1");

        QImage result = tracer3.render();
        ui->label_renderOutput->setPixmap(QPixmap::fromImage(result));
        result.save(currentFile + ".png");
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Select files",
                                                     QDir::currentPath(),
                                                     "Wavefront (*.obj);;All files (*.*)");

    ui->textEdit_queue->append(fileNames.join('\n'));
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
