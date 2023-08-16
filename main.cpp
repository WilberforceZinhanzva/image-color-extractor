#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cropper.h"
#include "colorextractormodel.h"
#include "colorextractorthread.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType(QUrl("qrc:/ColorExtractor/Theme.qml"),"Theme",1,0,"AppTheme");

    qmlRegisterType<Cropper>("Widgets",1,0,"Cropper");
    qmlRegisterType<ColorExtractorModel>("Models",1,0,"ColorExtractorModel");

    qmlRegisterUncreatableType<ColorExtractorThread>("Enums",1,0,"AlgorithmType","Enum is not a type");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ColorExtractor/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
