#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    modified = false;
    doc = new Document;
   // Document *newDocument;
    setCentralWidget(doc);
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    findDialog = 0;

    connect (doc, SIGNAL(textChanged()), this , SLOT(isModified()));
    // Move cursor to beginning of document when find dialog pops up
    connect (findAction, SIGNAL(triggered()), doc, SLOT(setCursorTop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new document file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"),this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"),this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), this , SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"),this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("E&xit"),this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Closes the program"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    cutAction = new QAction(tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Remove text to clipboard"));
    cutAction->setIcon(QIcon(":/images/cut.png"));
    connect(cutAction, SIGNAL(triggered()), doc, SLOT(cut()));

    copyAction = new QAction(tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setToolTip(tr("Copy text to clip board"));
    connect(copyAction, SIGNAL(triggered()), doc, SLOT(copy()));

    pasteAction = new QAction(tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setToolTip(tr("Paste text from clipboard"));
    connect(pasteAction, SIGNAL(triggered()), doc, SLOT(paste()));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setToolTip(tr("delete the following text"));
    connect(deleteAction, SIGNAL(triggered()), doc, SLOT(del()));

    selectAllAction = new QAction(tr("Select ALL"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setToolTip(tr("Select all"));
    connect(selectAllAction, SIGNAL(triggered()), doc, SLOT(selectAll()));

    findAction = new QAction(tr("Find"), this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setToolTip(tr("Find text"));
    connect (findAction,SIGNAL(triggered()), this, SLOT(find()) );

    fontAction = new QAction(tr("Font"), this);
    fontAction->setToolTip(tr("Font selection"));
   // connect (fontAction, SIGNAL(triggered()), this, SLOT(font()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip((tr("Shows application help box")));
    //connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQTAction = new QAction(tr("About &Qt"), this);
    aboutQTAction->setStatusTip(tr("show the QT library's about box"));
 //   connect (aboutQTAction, SIGNAL(triggered()), qAPP, SLOT(aboutQT));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(selectAllAction);
    editMenu->addAction(findAction);

    formatMenu = menuBar()->addMenu(tr("&Format"));
    formatMenu->addAction(fontAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQTAction);


}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);

    formatToolBar = addToolBar(tr("&Format"));
    formatToolBar->addAction(fontAction);

}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("W999");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    statusBar()->addWidget(locationLabel);

}

void MainWindow::newFile()
{
        if(okToContinue())
            doc->clear();
}

void MainWindow::isModified()
{
    modified = true;
}

bool MainWindow::okToContinue()
{
   if(modified)
   {
       int r = QMessageBox::warning(this, tr("Word"),
                                    tr("This docuemnt has "
                                       "beenmodified. \n Do "
                                       "you want to save "
                                       "changes"),
                                    QMessageBox::Yes| QMessageBox::No
                                    |QMessageBox::Cancel);
       if (r == QMessageBox::Yes){
           return save();
       }else if (r == QMessageBox::Cancel){
           return false;
       }
    }
    return true;
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Word"), ".",
                                                        tr("Word files (*.txt)"));

        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        statusBar()->showMessage(tr("Loading canceled"),2000);
        return false;
    }

    doc->readFile(fileName);
    return true;
}

bool MainWindow::save()
{

    if(fileName.isEmpty()){
        return saveAs();
    } else {
        return saveFile(fileName);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Word"),
                                                    ".",
                                                    tr("Word Files (*.txt)"));
    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{

    if(!doc->writeFile(fileName)){
       statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }


    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File Saved"), 2000);
    modified = false;
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
}

void MainWindow::find()
{
    if(!findDialog){
       findDialog = new FindDialog;
       connect(findDialog, SIGNAL(findNext(QString &)), doc, SLOT(findNext(QString &)));
    }
    findDialog->show();
}


