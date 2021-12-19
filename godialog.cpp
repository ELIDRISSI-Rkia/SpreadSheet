#include "godialog.h"
#include "ui_godialog.h"

goDialog::goDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goDialog)
{
    ui->setupUi(this);
    //EXO REG
    QRegExp exp{"[A-Z][1-9][0-9]{0,2}"};
    ui->lineEdit->setValidator(new QRegExpValidator(exp));

}

goDialog::~goDialog()
{
    delete ui;
}
QString goDialog::gocell() const
   {
       return ui->lineEdit->text();
   }
