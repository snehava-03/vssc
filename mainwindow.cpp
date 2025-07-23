#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui/QVBoxLayout>
#include<QtGui/QLineEdit>
#include<QtGui/QWidget>
#include<QtGui/QPushButton>
#include<QDebug>
#include<QRegExp>
#include<QMap>
#include<QFileDialog>
#include<QComboBox>
#include<QStackedWidget>
#include<QMenuBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget=new QWidget (this);
    QVBoxLayout *mainlayout =new QVBoxLayout(centralWidget);
    stackedWidget=new QStackedWidget(this);
    generalPage=new QWidget(this);
    stackedWidget->addWidget(generalPage);
     simulationPage=new QWidget(this);
     QVBoxLayout *simLayout=new QVBoxLayout(simulationPage);
    tableWidget=new QTableWidget(0,4,this);
    tableWidget->setMinimumSize(700,400);
    QStringList headers;
    headers<<"BaseGroup"<<"Parameters"<<"Simulation Type"<<"Details";
    tableWidget->setHorizontalHeaderLabels(headers);
    simLayout->addWidget(tableWidget);

    tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
   // layout->addWidget(tableWidget);
    QPushButton *submitButton = new QPushButton("Submit");
    simLayout->addWidget(submitButton);
    stackedWidget->addWidget(simulationPage);
    mainlayout->addWidget(stackedWidget);
    setCentralWidget(centralWidget);
    setWindowTitle("Simulation Table");


    QMenuBar *menuBar=new QMenuBar(this);
    QMenu *configMenu=menuBar->addMenu("Configuration");
    configMenu->addAction("General Configuration",this,SLOT(showGeneralConfig()));
    configMenu->addAction("Simulation Configuration",this,SLOT(showSimulationConfig()));
    setMenuBar(menuBar);

  QString path="/SLICE/input_data/parameters.dat";

        loadDataFromFile(path);

    connect(submitButton, SIGNAL(clicked()),this,SLOT(onSubmitButtonClicked()));




}

void MainWindow::showGeneralConfig(){
    stackedWidget->setCurrentWidget(generalPage);
}

void MainWindow::showSimulationConfig(){
    stackedWidget->setCurrentWidget(simulationPage);
}


 void MainWindow::loadDataFromFile(const QString &filePath)
 {
     QFile file(filePath);
     if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
     {
         return;
     }
     QTextStream in(&file);
     QString mainGroup,subGroup;
     std::vector<EntryData>data;
     while(!in.atEnd())
     {
         QString line=in.readLine().trimmed();
         if(line.startsWith("%"))
         {
             QStringList parts=line.split(QRegExp("\\s+"));
             if(parts.size()>1)
                 mainGroup=parts[1].trimmed();
         }
         else if(line.startsWith("@"))
         {
             QStringList parts=line.split(QRegExp("\\s+"));
             if(parts.size()>=3)
             {
                 subGroup=parts[1].trimmed();

             }
         }
         else if(line.startsWith("#"))
         {
             QStringList parts=line.split(QRegExp("\\s+"));
             if(parts.size()>=3)
             {
                 EntryData entry;
                entry.baseGroup=mainGroup;
                entry.subGroup=subGroup;
                entry.token0=parts[0];
                entry.paramName=parts[1];
                entry.token2=parts[2];
                 data.push_back(entry);
             }
         }
     }

     file.close();
     populateTable(data);
 }
 void MainWindow::populateTable(const std::vector<EntryData> &data)
{
     tableWidget->setRowCount(data.size());
     parsedData=data;
     for(int i=0;i<data.size();i++)
     {
     QTableWidgetItem *groupItem=new QTableWidgetItem(data[i].baseGroup);
     QTableWidgetItem *paramItem=new QTableWidgetItem(data[i].paramName);
     QComboBox  *simTypeCombo=new QComboBox;
     simTypeCombo->addItem("");
     simTypeCombo->addItem("offnominal");
     simTypeCombo->addItem("alt");
     simTypeCombo->addItem("prof");
     QLineEdit  *extraInfo=new QLineEdit;
     tableWidget->setItem(i,0,groupItem);
     tableWidget->setItem(i,1,paramItem);
     tableWidget->setCellWidget(i,2,simTypeCombo);
     tableWidget->setCellWidget(i,3,extraInfo);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: onSubmitButtonClicked()
{
    QFile file("output.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qWarning("Could not open output.txt");
        return;
    }
    QTextStream out(&file);
    QMap<QString,QMap<QString,QStringList> > groupedData;
    for(int i=0;i<parsedData.size();i++)
    {
        const EntryData &entry=parsedData[i];
        QComboBox *simCombo=qobject_cast<QComboBox*>(tableWidget->cellWidget(i,2));
        QLineEdit *extraEdit=qobject_cast<QLineEdit*>(tableWidget->cellWidget(i,3));
        QString simType=simCombo ? simCombo->currentText().trimmed():"";
        QString extraInfo=extraEdit ? extraEdit->text().trimmed():"";
        if(simType.isEmpty())
            continue;
        QString finalLine=QString(" %1\t %2\t %3\t %4")
                .arg(entry.token0)
                .arg(entry.paramName)
                .arg(entry.token2)
                .arg(simType);
        if(!extraInfo.isEmpty())
            finalLine+=" "+extraInfo;
        groupedData[entry.baseGroup][entry.subGroup].append(finalLine);
    }

    for(QMap<QString,QMap<QString,QStringList> >::const_iterator it=groupedData.begin();it!=groupedData.end();++it)
    {
         const QMap<QString,QStringList>&subMap=it.value();
         bool grphasValidsubgrp=false;
          for( QMap<QString,QStringList>::const_iterator sublt=subMap.begin();sublt !=subMap.end();++sublt)
            {
              if(!sublt.value().isEmpty()){
                 grphasValidsubgrp =true;
                  break;
              }
             }

        out<<"%\t"<<it.key()<<"{\n";

        for( QMap<QString,QStringList>::const_iterator sublt=subMap.begin();sublt !=subMap.end();++sublt)
        {

            out<<"\t@"<<sublt.key()<<"{\n";
           const QStringList &lines=sublt.value();
           if(lines.isEmpty())
               continue;
           for(int j=0;j<lines.size();j++)
           {
                out<<"\t\t"<<lines[j]<<"\n";
            }
            out<<"\t}\n";

        }
        out<<"}\n";
   }
    file.close();
    qDebug()<<"Output written to output.txt";
 }



