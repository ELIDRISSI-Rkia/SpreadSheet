#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    QRegExp exp{"[A-Z][a-z][a-z]{0,3}"};
    ui->lineEdit->setValidator(new QRegExpValidator(exp));

}

FindDialog::~FindDialog()
{
    delete ui;

}
QString FindDialog::find() const
   {
       return ui->lineEdit->text();

   }


