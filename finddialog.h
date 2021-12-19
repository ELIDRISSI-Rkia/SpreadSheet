#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include<QRegExpValidator>
namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
  QString find()const;
private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
