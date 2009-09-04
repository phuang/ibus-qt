#include "qibusdemoengine.h"
#include <QDebug>
 
bool DemoEngine::ProcessKeyEvent (uint keyVal, uint keyCode, uint modifiers)
{
    qDebug () << "Process Key Event";
    return true;
}
 
