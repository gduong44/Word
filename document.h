#ifndef DOCUMENT_H
#define DOCUMENT_H

//#include <QWidget>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



class Document: public QTextEdit
{
    Q_OBJECT

public:

    Document(QWidget *parent = 0);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);

private:

private slots
    :
    void del();
    void findNext(QString &);
    void setCursorTop();

};

#endif // DOCUMENT_H
