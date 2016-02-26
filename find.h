#ifndef FIND_H
#define FIND_H

#include <QDialog>

namespace Ui {
class Find;
}

class Find : public QDialog
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    ~Find();

private slots:
    //void on_findNext_clicked();



private:
    Ui::Find *ui;
signals:
    void findNext();

};

#endif // FIND_H
