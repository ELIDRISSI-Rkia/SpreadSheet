#include "spreadsheet.h"
#include "godialog.h"
#include "finddialog.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>



SpreadSheet::SpreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();


    //Creating the tool bar
    createToolBars();

    //making the connexions
    makeConnexions();


    //Creating the labels for the status bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);
    //construire les labels verticaux
    QStringList labels;
    for(auto letter = 'A';letter<= 'Z';letter++)
        labels<<QString(letter);
    spreadsheet->setVerticalHeaderLabels(labels);

}

void SpreadSheet::setupMainWidget()
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(100);
    spreadsheet->setColumnCount(10);
    setCentralWidget(spreadsheet);

}

SpreadSheet::~SpreadSheet()
{
    delete spreadsheet;

    // --------------- Actions       --------------//
    delete  New;
    delete  open;
    delete  save;
    delete  saveAs;
    delete  exit;
    delete cut;
    delete copy;
    delete paste;
    delete deleteAction;
    delete find;
    delete row;
    delete Column;
    delete all;
    delete goCell;
    delete recalculate;
    delete sort;
    delete showGrid;
    delete auto_recalculate;
    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;
}

void SpreadSheet::createActions()
{
    // --------- New File -------------------
   QPixmap newIcon(":/new_file.png");
   New = new QAction(newIcon, "&New", this);
  New->setShortcut(tr("Ctrl+N"));


    // --------- open file -------------------
   open = new QAction("&Open", this);
   open->setShortcut(tr("Ctrl+O"));

    // --------- save file -------------------
   save = new QAction("&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    // --------- saveAs file -------------------
   saveAs = new QAction("save &As", this);


    // --------- cutfile -------------------
   QPixmap cutIcon(":/cut_icon.png");
   cut = new QAction(newIcon, "Cu&t", this);
   cut->setShortcut(tr("Ctrl+X"));

   // --------- copy file -----------------
   copy = new QAction( "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));
   ///////////////
  // --------- paste -----------------

   paste = new QAction( "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));
  // --------- delete menu -----------------

   deleteAction = new QAction( "&Delete", this);
   deleteAction->setShortcut(tr("Del"));

//---------------------------------------
   row  = new QAction("&Row", this);
   Column = new QAction("&Column", this);
   all = new QAction("&All", this);
   all->setShortcut(tr("Ctrl+A"));



   QPixmap findIcon(":/search_icon.png"); find= new QAction(newIcon, "&Find", this);
   find->setShortcut(tr("Ctrl+F"));

   QPixmap goCellIcon(":/go_to_icon.png");
   goCell = new QAction( goCellIcon, "&Go to Cell", this);
   deleteAction->setShortcut(tr("f5"));


   recalculate = new QAction("&Recalculate",this);
   recalculate->setShortcut(tr("F9"));


   sort = new QAction("&Sort");



   showGrid = new QAction("&Show Grid");
   showGrid->setCheckable(true);
   showGrid->setChecked(spreadsheet->showGrid());

   auto_recalculate = new QAction("&Auto-recalculate");
   auto_recalculate->setCheckable(true);
   auto_recalculate->setChecked(true);



   about =  new QAction("&About");
   aboutQt = new QAction("About &Qt");

    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"E&xit", this);
   exit->setShortcut(tr("Ctrl+Q"));
}

void SpreadSheet::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void SpreadSheet::createMenus()
{
    // --------  File menu -------//
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(New);
    FileMenu->addAction(open);
    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addSeparator();
    FileMenu->addAction(exit);


    //------------- Edit menu --------/
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    auto select = editMenu->addMenu("&Select");
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);

    editMenu->addAction(find);
    editMenu->addAction(goCell);



    //-------------- Toosl menu ------------
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);



    //Optins menus
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(auto_recalculate);


    //----------- Help menu ------------
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

void SpreadSheet::createToolBars()
{

    //Crer une bare d'outils
    auto toolbar1 = addToolBar("File");


    //Ajouter des actions acette bar
    toolbar1->addAction(New);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


    //Creer une autre tool bar
    auto toolbar2  = addToolBar("ToolS");
    toolbar2->addAction(goCell);
     toolbar2->addAction(find);

}

void SpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0, %1)"};
   cellLocation->setText(cell.arg(row+1).arg(col+1));

}

void SpreadSheet::makeConnexions()
{




   // --------- Connexion for the  select all action ----/
   connect(all, &QAction::triggered,
           spreadsheet, &QTableWidget::selectAll);

   // Connection for the  show grid
   connect(showGrid, &QAction::triggered,
           spreadsheet, &QTableWidget::setShowGrid);

   //Connection for the exit button
   connect(exit, &QAction::triggered, this, &SpreadSheet::close);


//      //Connection for the AboutQt Action
   connect(aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
   //Connection for the New  Action
connect(New, SIGNAL(triggered()), this, SLOT(newFile()));

   //connectting the chane of any element in the spreadsheet with the update status bar
   connect(spreadsheet, &QTableWidget::cellClicked, this,  &SpreadSheet::updateStatusBar);
   //Connextion between the gocell action and the gocell slot
   connect(goCell, &QAction::triggered, this, &SpreadSheet::gocelldialog);
  //connecter le save Action
   connect(save, &QAction::triggered, this, &SpreadSheet::Save);
  // connect(saveAs, &QAction::triggered, this, &SpreadSheet::SaveAs);
   //--------------------------
 // connect(saveAs, &QAction::triggered, this, &SpreadSheet::saveContent);
   connect(open, &QAction::triggered, this, &SpreadSheet::Open);
      connect(find, &QAction::triggered, this, &SpreadSheet::Find);






}
void SpreadSheet::gocelldialog(){
    //bar d'out
   statusBar()->showMessage("gO DIALOG",3000);
   // creer le dialog
    goDialog D;

    //executer le dialog
    auto reply=D.exec();

    //si accepter on traite le texte
    if(reply==QDialog::Accepted)
       {
        QString cell=D.gocell();
        int row=cell[0].toLatin1() - 'A';

        //obtenir le colomne
        cell=cell.remove(0,1);
        int col=cell.toInt() -1;
        spreadsheet->setCurrentCell(row,col);


        // Initier le nom de fichier
        currentFile=nullptr;
        setWindowTitle("Buffer");
        }
}

   void SpreadSheet:: Save()
    {
         // tester si j'ai un nom de fichier (currentFile)
       if (currentFile)
       {
           // au cas ou non obtenir le nom au fichier
           QFileDialog D;
           auto filename =D.getSaveFileName();
           currentFile= new QString (filename);
           setWindowTitle(filename);
           saveContent(filename);
       }

       if( !currentFile)
         {
                 saveContent(*currentFile);
         }

}

       // Sauvgarder le contenu

 void SpreadSheet:: saveContent(QString filename)const
 {
     //ouvrir un pointeur sur le fichier
     QFile file(filename);



     //tester si je peux ouvrir le fichier

    if(file.open(QIODevice::WriteOnly))
    {
        //Flu d information

        QTextStream out(&file);
        for(int i =0;i<spreadsheet->rowCount();i++)
            for(int j=0;j<spreadsheet->columnCount(); j++)
            {

                auto cell =spreadsheet->item(i,j);
                if(cell)
                    out << i << ',' << j << ','<< cell->text() << endl;
            }

    }
   file.close();
 }











 void SpreadSheet::newFile()
 {

         spreadsheet->clear();


 }
 bool SpreadSheet::loadFile(QString filename) const
 {
     QFile file(filename);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text )) {
       statusBar()->showMessage(tr("Loading canceled"), 2000);
         return false;}



        QTextStream in(&file);
             for(int i =0;i<spreadsheet->rowCount();i++){
                 for(int j=0;j<spreadsheet->columnCount(); j++)
                 {

                     auto cell =spreadsheet->item(i,j);
                     if(cell)
                        in<< i << ',' << j << ','<< cell->text() << endl;




     statusBar()->showMessage(tr("File loaded"), 2000);
     return true;
                 }}
 }


 void SpreadSheet::Open()
 {

         QString fileName = QFileDialog::getOpenFileName(this,tr("Open Spreadsheet"));


        if (!fileName.isEmpty())

        loadFile(fileName);
          setWindowTitle(fileName);



}



 void SpreadSheet::Find()
 { //creer le dialog
   FindDialog d;

      //executer le dialog
      auto reply=d.exec();

      //si accepter on traite le texte
      if(reply==QDialog::Accepted)
        {
       auto pattern=d.find();

        for(int i =0;i<spreadsheet->rowCount();i++){
            for(int j=0;j<spreadsheet->columnCount(); j++){
                auto c = spreadsheet->item(i,j);
                if(c){
                    if(c->text().contains(pattern)){
                        spreadsheet->setCurrentCell(i,j);
                        return;
                    }
                }


 }}



    }}
