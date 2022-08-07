#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "warehouse.h"
#include <QCloseEvent>
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addGoods_clicked();
    void on_delGoods_clicked();
    void on_showGoods_clicked();
    void on_search_clicked();
    void on_empty_clicked();
    void on_ok_clicked();
    void on_exit_clicked();
    void on_ClearButton_clicked();

private:
    Ui::MainWindow *ui_;
    char commod_;
    Warehouse wre_;
    void Clear();
};

#endif // MAINWINDOW_H
