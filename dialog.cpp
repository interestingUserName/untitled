#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "logic.h"

Dialog::Dialog(QWidget *parent, MainWindow* mWindow) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    mainWindow = mWindow;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_cancel_button_clicked()
{
    close();
}

void Dialog::on_ok_button_clicked()
{
    QString text = ui->coordinates_input->toPlainText();
    int validPoints = Logic::CheckText(text);
    if (validPoints != -1)
    {
        mainWindow->setCoordinatesText(mainWindow->getPointsText() + text + '\n');
        mainWindow->InitializePoints();
        mainWindow->setPoints(Logic::normalizePoints(mainWindow->getPoints()));
        mainWindow->writePoints();
        mainWindow->setPointsCount(mainWindow->getPoints().length());
        if (mainWindow->drawing->isVisible())
        {
            mainWindow->drawing->close();
            mainWindow->openDrawing();
        }
        close();
    }
    else
    {
        QMessageBox::warning(this, "error", "invalid text");
    }
}
