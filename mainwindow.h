#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_prevImage_clicked();

    void on_clearImages_clicked();

    void on_nextImage_clicked();

private:
    Ui::MainWindow *ui;
    void displayImage(int count);
    int currentIndex;
    QPixmap* image;
    QStringList imagesList;
    QDir* imagesDir;
};

#endif // MAINWINDOW_H
