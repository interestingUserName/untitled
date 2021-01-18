#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, MainWindow* mWindow = nullptr);
    ~Dialog();

private slots:
    void on_cancel_button_clicked();

    void on_ok_button_clicked();

private:
    Ui::Dialog *ui;
    MainWindow* mainWindow;
};

#endif // DIALOG_H
