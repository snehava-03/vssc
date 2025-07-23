#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtGui/QMainWindow>
#include <QtGui/QTableWidget>
#include <QtGui/QLineEdit>
#include<QString>
#include<vector>
#include<utility>
#include<QComboBox>
#include<QStackedWidget>
#include<QMenuBar>
struct EntryData{
    QString baseGroup;
    QString subGroup;
    QString paramName;
    QString token0;
    QString token2;
};


namespace Ui {
class MainWindow;
}
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadDataFromFile(const QString &filePath);
     QComboBox  *simTypeCombo;
     QStackedWidget *stackedWidget;
     QWidget *generalPage;
     QWidget *simulationPage;

/*
private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked(bool checked);
*/
 //members
private:
    Ui::MainWindow *ui;
   QTableWidget *tableWidget;
   std::vector<EntryData>parsedData;

  //  ProfileGenerator myProf;

 //functions

 private:
    //void populateTable(const std::vector<std::pair<QString,QString> >&data);
   void populateTable(const std::vector<EntryData> &data);
 private slots:
    void onSubmitButtonClicked();
    void showGeneralConfig();
    void showSimulationConfig();
};

#endif // MAINWINDOW_H
