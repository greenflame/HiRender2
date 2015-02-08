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
    objPath = "/Users/Alexander/Desktop/head.obj";
    resultPath = "/Users/Alexander/Desktop/sphere.png";

//    objPath = "planet.obj";
//    resultPath = "planet.png";

    HTracer3 tracer3;

    tracer3.addTexture("skyTexture", QImage("/Users/Alexander/Desktop/pano1.jpg"));

    int lines = 720 * 2;
    float k = 16.0 / 9.0;

    tracer3.setImageSize(QSize(lines * k, lines));
    tracer3.setCameraFrustum(HFrustum(-0.5 * k, 0.5 * k, -0.5, 0.5, 0.5, 100));

//    loadObj(tracer3, objPath);
    tracer3.addSphere(QVector3D(0, 0, 0), 1, "mirrorShader");

    QMatrix4x4 m;
//    m.translate(-0.35, 0.5, -20);
    m.translate(0, 0, -2);
//    m.rotate(30, QVector3D(0, 1, 0));
    tracer3.transformScene(m);
        tracer3.addPointLight(QVector3D(2, -1, 5));
//        tracer3.addPointLight(QVector3D(0, 0, 0));
//    tracer3.setTileSize(QSize(25, 25));

    connect(&tracer3, SIGNAL(onRenderMessage(QString)), this, SLOT(onRenderMessage(QString)));
    connect(&tracer3, SIGNAL(onTemporaryImageUpdated(QImage)), this, SLOT(onTemporaryImageUpdated(QImage)));

    ui->label_2->clear();
    t.start();
    QImage result = tracer3.render();
    result = result.scaled(result.width() / 2, result.height() / 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(result));
    result.save(resultPath);
}

void MainWindow::onTemporaryImageUpdated(QImage image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));

    if (t.elapsed() > 10000)
    {
        image.save(resultPath);
        t.start();
    }
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::onRenderMessage(QString message)
{
    ui->label_2->setText(ui->label_2->text() + message);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool MainWindow::loadObj(HTracer3 &tracer, const QString &fileName)
{
    QFile inputFile(fileName);
    bool isFileOpened = inputFile.open(QIODevice::ReadOnly);
    if (!isFileOpened)
        return false;

    QTextStream in(&inputFile);

    QVector<QVector3D> vertexCoordinates;
    QVector<QVector3D> textureCoordinates;
    QVector<QVector3D> normals;

    QString currentMaterialName = "default";
//    QString currentMaterialName = "mirrorShader";

    while (!in.atEnd())
    {
        QString line = in.readLine();
        line.replace("  ", " ");
        QStringList params = line.split(' ');

        // Loading material library
        if (params[0] == "mtllib")
        {
            if (!loadMtl(tracer, QFileInfo(fileName).path() + "/" + params[1]))
                return false;
        }

        // Use material
        if (params[0] == "usemtl")
        {
            currentMaterialName = params[1];
        }

        // Vertex coordinates
        if (params[0] == "v")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();
            float c = params[3].toFloat();
            vertexCoordinates.append(QVector3D(a, b, c));
        }

        // Texture coordinates
        if (params[0] == "vt")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();

            // Third coordinate is optional
            float c = 0;
            if (params.length() > 3)
                c = params[3].toFloat();

            textureCoordinates.append(QVector3D(a, b, c));
        }

        // Vertex coordinates
        if (params[0] == "vn")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();
            float c = params[3].toFloat();
            normals.append(QVector3D(a, b, c).normalized());
        }

        // Face
        if (params[0] == "f")
        {
            for (int i = 2; i < params.length() - 1; i++)
            {
                QStringList p1 = params[1].split('/');
                QStringList p2 = params[i].split('/');
                QStringList p3 = params[i + 1].split('/');

                int v1, v2, v3, t1, t2, t3, n1, n2, n3;
                bool isTextureSet = false;
                bool isNormalsSet = false;

                v1 = p1[0].toInt();
                v2 = p2[0].toInt();
                v3 = p3[0].toInt();

                if (p1.length() > 1 && p1.at(1).length() != 0)
                {
                    t1 = p1[1].toInt();
                    t2 = p2[1].toInt();
                    t3 = p3[1].toInt();
                    isTextureSet = true;
                }

                if (p1.length() > 2)
                {
                    n1 = p1[2].toInt();
                    n2 = p2[2].toInt();
                    n3 = p3[2].toInt();
                    isNormalsSet = true;
                }

                if (isNormalsSet)
                {
                    tracer.addPolygon(
                            vertexCoordinates[v1 - 1],
                            vertexCoordinates[v2 - 1],
                            vertexCoordinates[v3 - 1],

                            normals[n1 - 1],
                            normals[n2 - 1],
                            normals[n3 - 1],

                            currentMaterialName);
                }
                else
                {
                    tracer.addPolygon(
                            vertexCoordinates[v1 - 1],
                            vertexCoordinates[v2 - 1],
                            vertexCoordinates[v3 - 1],

                            currentMaterialName);
                }

            }
        }   //f



    }

    inputFile.close();
    return true;
}

bool MainWindow::loadMtl(HTracer3 &tracer, const QString &fileName)
{
    QFile inputFile(fileName);
    bool isFileOpened = inputFile.open(QIODevice::ReadOnly);
    if (!isFileOpened)
        return false;

    QTextStream in(&inputFile);

    bool isFirstMaterial = true;
    QString materialName;
    QColor diffuseColor;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList params = line.split(' ');

        if (params[0] == "newmtl")
        {
            if (!isFirstMaterial)
            {
                tracer.addPhongShader(materialName, diffuseColor);
            }
            else
            {
                isFirstMaterial = false;
            }

            materialName = params[1];
        }

        if (params[0] == "Kd")
        {
            float r = params[1].toFloat();
            float g = params[2].toFloat();
            float b = params[3].toFloat();
            diffuseColor = QColor::fromRgb(255 * r, 255 * g, 255 * b);
        }
    }

    inputFile.close();
    return true;
}
