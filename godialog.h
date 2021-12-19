#ifndef GODIALOG_H
#define GODIALOG_H
#include<QRegExpValidator>
#include <QDialog>

namespace Ui {
class goDialog;
}

class goDialog : public QDialog
{
    Q_OBJECT

public:
    explicit goDialog(QWidget *parent = nullptr);
    ~goDialog();
    QString gocell()const; //getter pour le texte de line edit


private:
    Ui::goDialog *ui;
};

#endif // GODIALOG_H
