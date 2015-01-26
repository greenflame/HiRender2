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
    HTracer3 tracer3;

    int lines = 720 * 2;
    float k = 16.0 / 9.0;

    tracer3.setImageSize(QSize(lines * k, lines));
    tracer3.setCameraFrustum(HFrustum(-0.5 * k, 0.5 * k, -0.5, 0.5, 4, 100));

    loadMtl(tracer3, "/Users/Alexander/Desktop/planet.mtl");
    loadObj(tracer3, "/Users/Alexander/Desktop/planet.obj");

    QMatrix4x4 m;
    m.translate(0, 0, -10);
    tracer3.addPointLight(QVector3D(2, -1, 5));
    tracer3.transformScene(m);

    connect(&tracer3, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    connect(&tracer3, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));

    ui->label_2->clear();
    QImage result = tracer3.render();
    ui->label->setPixmap(QPixmap::fromImage(result));
    result.save("/Users/Alexander/Desktop/result.png");
}

void MainWindow::onTemporaryImageUpdated(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::onRenderMessage(QString message)
{
    ui->label_2->setText(ui->label_2->text() + message);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::loadObj(HTracer3 &tracer, const QString &fileName)
{
    QFile inputFile(fileName);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    QVector<QVector3D> vertexes;
    QString currentMaterialName = "default";

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(' ');

        if (list[0] == "usemtl")
        {
            currentMaterialName = list[1];
        }

        if (list[0] == "v")
        {
            float a = list[1].toFloat();
            float b = list[2].toFloat();
            float c = list[3].toFloat();
            vertexes.append(QVector3D(a, b, c));
        }

        if (list[0] == "f")
        {
            for (int i = 2; i < list.length() - 1; i++)
            {
                QVector3D p1 = vertexes[list[1].toInt() - 1];
                QVector3D p2 = vertexes[list[i].toInt() - 1];
                QVector3D p3 = vertexes[list[i + 1].toInt() - 1];
                tracer.addPolygon(p1, p2, p3, currentMaterialName);
            }
        }
    }

    inputFile.close();
}

void MainWindow::loadMtl(HTracer3 &tracer, const QString &fileName)
{
    QFile inputFile(fileName);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    bool isFirstMaterial = true;
    QString materialName;
    QColor diffuseColor;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(' ');

        if (list[0] == "newmtl")
        {
            if (!isFirstMaterial)
            {
                tracer.addMaterial(materialName, diffuseColor);
            }
            else
            {
                isFirstMaterial = false;
            }

            materialName = list[1];
        }

        if (list[0] == "Kd")
        {
            float r = list[1].toFloat();
            float g = list[2].toFloat();
            float b = list[3].toFloat();
            diffuseColor = QColor::fromRgb(255 * r, 255 * g, 255 * b);
        }
    }

    inputFile.close();}
