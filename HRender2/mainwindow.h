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
    void on_pushButton_process_clicked();
    void on_pushButton_add_clicked();

    void onTemporaryImageUpdated(QImage image);
    void onRenderMessage(QString message);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
