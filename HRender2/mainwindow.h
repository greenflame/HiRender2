#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include <QMatrix4x4>
#include <QImage>

#include <QTime>
#include <QTimer>
#include <QColor>
#include <QFileInfo>
#include <QFileDialog>
#include <QDir>
#include <QTimer>

#include "htracer3.h"
#include "colliders/hcolliders.h"

#include "sscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pushButton_loadScene_clicked();
    void on_pushButton_render_clicked();

    void on_pushButton_test_clicked();

    void onTemporaryImageUpdated(QImage image);
    void onRenderMessage(QString message);

    void previewUpdate();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    bool loadObj(HTracer3 &tracer, const QString &fileName);
    bool loadMtl(HTracer3 &tracer, const QString &fileName);

    HTracer3 tracer;
    bool isSceneLoaded;
    int xRot, yRot;
    int xPrev, yPrev;
    bool isPreviewRendered;

    QSize resultSize;
    float previewScale;
    float distanceFromCenter;
};

#endif // MAINWINDOW_H
