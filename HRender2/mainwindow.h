#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMatrix4x4>
#include <QImage>

#include <QTime>
#include <QTimer>
#include <QColor>

#include "htracer3.h"
#include "hscene.h"
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

    void loadObj(HTracer3 &tracer, const QString &fileName);
    void loadMtl(HTracer3 &tracer, const QString &fileName);
};

#endif // MAINWINDOW_H
