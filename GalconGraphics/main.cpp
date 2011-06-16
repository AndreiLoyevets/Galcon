#include <QtGui/QApplication>
#include <QTimer>

#include "mainwindow.h"

#include "Log.h"
#include "network.h"
#include "parser.h"
#include "DialogConnect.h"
#include "DialogCountdown.h"
#include "game.h"
#include "DialogMessage.h"

using namespace LogDecl;
using namespace NetworkDecl;
using namespace ParserDecl;
using namespace GameDecl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CParser parse;

    CGame game;


    return a.exec();
}
