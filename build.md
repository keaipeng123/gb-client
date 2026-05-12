1. 编译工具链安装 
`xcode-select --install`

2. Qt SDK：在官网安装qt

运行 CMake: Configure
如果第一次找不到 Qt，就在 VS Code 设置里加一项：
"cmake.configureSettings": {
  "CMAKE_PREFIX_PATH": "/Users/你的用户名/Qt/6.8.2/macos"
}

3. ffmpeg sdl json