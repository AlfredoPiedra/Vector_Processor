#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPushButton>

#include <string>
#include <sstream>

#include "vectorial_processor.h"

 namespace Ui {
  class MainWindow;
 }

 class MainWindow : public QMainWindow
 {
 Q_OBJECT
 public:

 explicit MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

 private slots:

 void handleButton();

 std::string GetHexString(int integer);

 private:

 QPushButton *p_button;
 Ui::MainWindow *ui;
 VectorialProcessor *processor;

 };

#endif // MAINWINDOW_H
