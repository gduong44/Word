#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "document.h"


#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QTextCursor>
#include <QDialog>
#include "finddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool modified;
    QString currentFile;
    QString fileName;

    void setCurrentFile(QString &fileName);

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    bool okToContinue();
    bool loadFile(const QString&);
    bool saveFile(const QString &);
    void setCurrentFile(const QString &);
    Document *doc;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAllAction;
    QAction *findAction;
    QAction *fontAction;
    QAction *aboutAction;
    QAction *aboutQTAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;

    QLabel *locationLabel;

    FindDialog *findDialog;
    Ui::MainWindow *ui;
private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    //void cut();
    //void copy();
    //void paste();

    //void selectAll();
    void find();

    //void font();
    //void about();
    void isModified();
};

#endif // MAINWINDOW_H
