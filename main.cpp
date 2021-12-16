#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <memory>
#include "udppackage.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //UdpPackage udpPackage;
    //qmlRegisterType<UdpPackage>("UdpPackage", 1, 0, "UdpPackage");

    int len = 98;

    /* Frame (98 bytes) */
    static const unsigned char packet[98] = {
    0x9e, 0xe2, 0xf1, 0x4d, 0xa4, 0x2a, 0x02, 0x00, /* ...M.*.. */
    0x14, 0x8b, 0x70, 0x06, 0x08, 0x00, 0x45, 0x00, /* ..p...E. */
    0x00, 0x54, 0x2c, 0xd2, 0x00, 0x00, 0x40, 0x11, /* .T,...@. */
    0x80, 0x1e, 0x0a, 0xd2, 0xdc, 0x03, 0x0a, 0xd2, /* ........ */
    0xdc, 0x01, 0x77, 0x1a, 0x77, 0x1a, 0x00, 0x40, /* ..w.w..@ */
    0x81, 0x4b, 0xff, 0xff, 0x81, 0x00, 0x00, 0x00, /* .K...... */
    0x00, 0x30, 0x00, 0x00, 0x00, 0x22, 0x01, 0x01, /* .0...".. */
    0x02, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x10, 0x01, 0x00, 0x00, 0x10, 0x12, 0x55, /* .......U */
    0x00, 0x03, 0x01, 0xff, 0xff, 0xff, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x09, /* ........ */
    0x04, 0x00, 0x0a, 0xd2, 0xdc, 0x03, 0x00, 0x11, /* ........ */
    0x7d, 0x7d /* }} */
    };

    UdpPackage packageInstance((char*)packet, len);
    packageInstance.displayPackageDetails((char*)packet, len);

    QQmlApplicationEngine engine;
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("udpInstance", &packageInstance);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
