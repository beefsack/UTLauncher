#include "utlauncher.h"

#include <QtPlugin>
#include <QDebug>
#include <iostream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n\0 (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n\0 (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n\0 (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n\0 (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char** argv)
{
    qInstallMessageHandler(myMessageOutput);
    QCoreApplication::setOrganizationName("CodeCharm");
    QCoreApplication::setOrganizationDomain("codecharm.co.uk");
    QCoreApplication::setApplicationName("UTLauncher");
    
    UTLauncher app(argc, argv);
    QSystemTrayIcon icon(QIcon(":/icon.png"));
    icon.show();
    
    return app.exec();
}

#ifdef STATIC_PLUGIN_WINDOWS
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin);
#endif