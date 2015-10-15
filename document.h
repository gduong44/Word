#ifndef DOCUMENT_H
#define DOCUMENT_H

//#include <QWidget>
#include <QTextEdit>

class Document: public QTextEdit
{
    Q_OBJECT

public:
    Document(QWidget *parent = 0);
};

#endif // DOCUMENT_H
