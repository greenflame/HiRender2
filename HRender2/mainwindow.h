#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMatrix4x4>
#include <QImage>

#include <QTime>

#include "htracer2.h"
#include "hscene.h"

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
    void onPictureUpdate(QImage image);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
