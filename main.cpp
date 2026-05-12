#include <QApplication>
#include <QString>

#include <SDL2/SDL.h>
#include <json/json.h>

#include "mainwindow.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    avformat_network_init();//FFmpeg 初始化网络模块

    Json::Value root;
    root["ffmpegVersion"] = av_version_info();
    root["jsonLibrary"] = JSONCPP_VERSION_STRING;

    QString sdlStatus;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        sdlStatus = QString("SDL init failed: %1").arg(SDL_GetError());
        root["sdlInit"] = "failed";
    } else {
        SDL_version version;
        SDL_GetVersion(&version);

        sdlStatus = QString("SDL version: %1.%2.%3")
                        .arg(version.major)
                        .arg(version.minor)
                        .arg(version.patch);
        root["sdlInit"] = "ok";
        root["sdlVersion"] = QString("%1.%2.%3")
                                 .arg(version.major)
                                 .arg(version.minor)
                                 .arg(version.patch)
                                 .toStdString();
    }

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "  ";
    const std::string jsonText = Json::writeString(builder, root);

    const QString text = QString("FFmpeg version: %1\n%2\n\nJsonCpp output:\n%3")
                             .arg(av_version_info())
                             .arg(sdlStatus)
                             .arg(QString::fromStdString(jsonText));

    //创建主窗口并显示
    MainWindow window(text);
    window.show();

    const int exitCode = app.exec();//运行 Qt 消息循环（保持窗口不退出）
    SDL_Quit();//关闭sdl
    return exitCode;
}