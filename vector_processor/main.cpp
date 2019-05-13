#include <iostream>
#include <unistd.h>

#include <QApplication>

#include "main_window.h"
#include "image_encryption.h"


int main(int argc, char **argv){

   QApplication app(argc, argv);

   MainWindow mainWindow;
   mainWindow.show();
   return app.exec();
}
