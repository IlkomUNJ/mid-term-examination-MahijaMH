#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Create the main window.
    MainWindow w;
    //w.setWindowTitle("Qt Line Drawing Example");
    //LineWidget *lineWidget = new LineWidget(&w);
    // Set our custom widget as the central widget of the main window.
    //w.setCentralWidget(lineWidget);
    w.show();
    // Show the main window.
    return a.exec();
}
