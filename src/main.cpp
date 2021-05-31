#include "mainwindow.h"
#include "3rd_party/bergamot-translator/3rd_party/marian-dev/src/marian.h"

#include <QApplication>
#include <QCommandLineParser>

#ifdef __APPLE__
void mac_patchPlaceholderColor();
#endif

int main(int argc, char *argv[])
{
    // Set marian to throw exceptions instead of std::abort()
    marian::setThrowExceptionOnAbort(true);

    QApplication translateLocally(argc, argv);
    QCoreApplication::setApplicationName("translateLocally");
    QCoreApplication::setApplicationVersion("0.02");

#ifdef __APPLE__
    mac_patchPlaceholderColor();
#endif

    // Command line parsing
    QCommandLineParser parser;
    parser.setApplicationDescription("A secure translation service that performs translations for you locally, on your own machine.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(translateLocally);

    // Launch application
    MainWindow w;
    w.show();
    return translateLocally.exec();
}
