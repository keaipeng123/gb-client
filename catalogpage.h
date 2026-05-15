#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CatalogPage;
}
QT_END_NAMESPACE

class QLabel;//文本标签

class CatalogPage : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogPage(QWidget *parent = nullptr);
    ~CatalogPage() override;

    //设置服务器信息（IP + 端口）
    void setServerInfo(const QString &ip, quint16 port);
    //设置版本信息（FFmpeg/SDL 那段）
    void setStartupInfo(const QString &text);
    //获取显示标签（给外部播放视频用）
    QLabel *videoLabel() const;
    //在播放区域显示状态信息
    void showStatus(const QString &status, bool isError = false);
    void updateTree(const QByteArray &jsonData);

private:
    void populateTree();//加载左边目录树（内部用）

    Ui::CatalogPage *ui;
    QString startupInfo_;//保存版本信息
};