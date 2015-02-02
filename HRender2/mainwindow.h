#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMatrix4x4>
#include <QImage>

#include <QTime>
#include <QTimer>
#include <QColor>
#include <QFileInfo>
#include <QDir>

#include "htracer3.h"
#include "hspherecollider.h"

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
    void on_pushButton_clicked();

    void onTemporaryImageUpdated(QImage image);
    void onRenderMessage(QString message);

private:
    Ui::MainWindow *ui;

    bool loadObj(HTracer3 &tracer, const QString &fileName);
    bool loadMtl(HTracer3 &tracer, const QString &fileName);

    QTime t;
    QString objPath;
    QString resultPath;
};

#endif // MAINWINDOW_H
