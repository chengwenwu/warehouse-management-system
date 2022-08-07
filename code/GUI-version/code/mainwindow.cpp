#include "mainwindow.h"

#include <QMessageBox>

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox messageBox(QMessageBox::Warning, "waring", "Exit the system?", QMessageBox::Yes | QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_addGoods_clicked()
{
    this->Clear();
    ui_->id->setEnabled(true);
    ui_->godnm->setEnabled(true);
    ui_->godnum->setEnabled(true);
    ui_->textBrowser->clear();
    this->commod_ = '1';
}

void MainWindow::on_delGoods_clicked()
{
    this->Clear();
    ui_->id->setEnabled(true);
    ui_->godnm->setEnabled(false);
    ui_->godnum->setEnabled(true);
    ui_->textBrowser->clear();
    this->commod_ = '2';
    try {
        wre_.ShowGoods();
    } catch (QString str) {
        this->ui_->textBrowser->setText(str);
    }
}

void MainWindow::on_showGoods_clicked()
{
    this->Clear();
    ui_->id->setEnabled(false);
    ui_->godnm->setEnabled(false);
    ui_->godnum->setEnabled(false);
    ui_->textBrowser->clear();
    try {
        wre_.ShowGoods();
    } catch (QString str) {
        this->ui_->textBrowser->setText(str);
    }

    this->commod_ = '3';
}

void MainWindow::on_search_clicked()
{
    this->Clear();
    ui_->id->setEnabled(true);
    ui_->godnm->setEnabled(true);
    ui_->godnum->setEnabled(false);
    ui_->textBrowser->clear();
    this->commod_ = '4';
}

void MainWindow::on_empty_clicked()
{
    this->Clear();
    ui_->id->setEnabled(false);
    ui_->godnm->setEnabled(false);
    ui_->godnum->setEnabled(false);
    ui_->textBrowser->clear();
    QMessageBox massagebox(QMessageBox::Warning, "waring", "Empty warehouse?", QMessageBox::Yes | QMessageBox::No);
    if (massagebox.exec() == QMessageBox::Yes) {
        try {
            wre_.Empty();
        } catch (QString str) {
            this->ui_->textBrowser->setText(str);
        }
    }
}

void MainWindow::on_ok_clicked()
{
    switch (this->commod_) //开关实现各功能分块选择
    {
        case '1': //进货
        {
            try {
                wre_.AddGoods(ui_->id->text(), ui_->godnm->text(), ui_->godnum->text());
                break;
            } catch (QString str) {
                this->ui_->textBrowser->setText(str);
                break;
            }
        }
        case '2': //出货
        {
            try {
                wre_.DeleteGoods(ui_->id->text(), ui_->godnum->text());
                break;
            } catch (QString str) {
                this->ui_->textBrowser->setText(str);
                break;
            }
        }

        case '4': //实现查询
        {
            try {
                wre_.FindGoods(ui_->id->text(), ui_->godnm->text());
                break;
            } catch (QString str) {
                this->ui_->textBrowser->setText(str);
                break;
            }
        }
        case '5': //清空仓库
        {
            try {
                wre_.Empty();
            } catch (QString str) {
                this->ui_->textBrowser->setText(str);
            }
        }
    }
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::Clear()
{
    ui_->godnm->clear();
    ui_->godnum->clear();
    ui_->id->clear();
}

void MainWindow::on_ClearButton_clicked()
{
    Clear();
}
