#include "finddialog.h"
#include <QtGui>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{

    lineEdit = new QLineEdit();
    lineEdit->show();

    label = new QLabel("Find What");
    label->show();
    label->setBuddy(lineEdit);

    findNextButton = new QPushButton("&Find Next");
    findNextButton->show();

    cancelButton = new QPushButton("Cancel");
    cancelButton->show();

    bottomLayout = new QHBoxLayout;
    bottomSpacer = new QSpacerItem(40, 20,
                                   QSizePolicy::Expanding,
                                   QSizePolicy::Minimum);
    bottomLayout->addItem(bottomSpacer);
    bottomLayout->addWidget(findNextButton);
    bottomLayout->addWidget(cancelButton);

    topLayout = new QHBoxLayout;
    topLayout->addWidget(label);
    topLayout->addWidget(lineEdit);


    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    connect(lineEdit, SIGNAL(textChanged(QString &)),
            this, SLOT(enableFindButton(const QString &)));
    connect(findNextButton, SIGNAL(clicked()),
            this, SLOT(findNextClicked()));
    connect(cancelButton , SIGNAL(clicked()), this,
            SLOT(close()));
}


void FindDialog::enableFindButton(const QString &text)
{
    findNextButton->setEnabled(!text.isEmpty());
}

void FindDialog::findNextClicked()
{
   QString text = lineEdit->text();
   emit findNext(text);
}
