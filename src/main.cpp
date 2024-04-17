#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "PlayerController.hpp"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:/Assets/Icons/app_icon.ico"));

    QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
			[] { QCoreApplication::exit(-1);  }, Qt::QueuedConnection);

    PlayerController *playerController = new PlayerController(&app);
    qmlRegisterSingletonInstance("com.refraction.PlayerController", 1, 0, "PlayerController", playerController);

    engine.loadFromModule("SongPlayer", "Main");
	return QGuiApplication::exec();
}
