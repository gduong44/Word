#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);

private:
    QLineEdit *lineEdit;
    QLabel *label;
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QSpacerItem *bottomSpacer;
    QPushButton *findNextButton;
    QVBoxLayout *mainLayout;
    QPushButton *cancelButton;
signals:
    void findNext(QString &);
private slots:
    void enableFindButton(const QString &text);
    void findNextClicked();

};

#endif // FINDDIALOG_H
