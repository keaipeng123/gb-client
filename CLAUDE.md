# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 语言偏好

后续所有针对此项目的回答和交流都使用中文。

## 构建系统

CMake + Ninja，macOS 平台，基于 Qt6。项目已预配置在 `build/` 目录下。

- **配置**: `cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/Users/sxr/Qt/6.11.0/macos -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- **构建**: `cmake --build build`
- **运行**: `./build/HelloQt`

VS Code 任务已配置在 `.vscode/tasks.json` — 按 F5 即可构建并启动调试器。

## 依赖（Homebrew）

- Qt 6.11.0（macOS SDK，安装路径 `/Users/sxr/Qt/6.11.0/macos`）
- CMake（`/opt/homebrew/bin/cmake`）
- JsonCpp、FFmpeg（libavformat/libavcodec/libavutil/libswscale/libswresample）、SDL2 — 均通过 pkg-config 引入

## 架构

一个两页面的 Qt 桌面客户端，用于连接媒体服务器，浏览和播放流媒体及录像。

**`main.cpp`** — 程序入口。初始化 FFmpeg 网络模块、SDL、JsonCpp，输出版本信息，然后启动 Qt 应用并显示 `MainWindow`。

**`MainWindow`**（`mainwindow.h/cpp`）— 顶层 `QMainWindow`。持有一个 `QStackedWidget`，在两个页面之间切换：

- `EntryPage` — 登录页，首先显示
- `CatalogPage` — 目录页，连接服务器后显示

将 `EntryPage::connectRequested` 信号连接到 `handleConnectRequested` 槽函数，后者将服务器的 IP/端口传给 `CatalogPage` 并切换页面。

**`EntryPage`**（`entrypage.h/cpp` + `entrypage.ui`）— 登录表单，包含 IP 和端口输入框。端口输入框限制为 1–65535 的整数。"确定"按钮发出 `connectRequested(ip, port)` 信号；"取消"按钮清空输入。

**`CatalogPage`**（`catalogpage.h/cpp` + `catalogpage.ui`）— 主工作区，左侧为 `QTreeWidget`（媒体目录），右侧为 `QLabel`（视频播放占位区域）。目录树目前为硬编码的示例项（"直播源/camera_01"、"历史记录/sample.mp4"）。`videoLabel()` 方法暴露播放标签，供后续视频渲染使用。

## UI 文件

`.ui` 文件是 Qt Designer 生成的 XML。构建时通过 Qt UIC 工具自动生成 `ui_*.h` 头文件，生成的头文件位于 `build/HelloQt_autogen/`，在对应的 `.cpp` 文件中被 include。
