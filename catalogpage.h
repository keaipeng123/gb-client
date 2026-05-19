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
    void updateCatalogTree(const QString &sipId, const QByteArray &jsonData);

signals:
    void refreshRequested();//用户点了"媒体目录"节点，请求刷新设备列表
    void sipIdClicked(const QString &sipId);//用户点了某个设备，请求获取该设备的目录
    void playRequested(const QString &sipId, const QString &deviceId);//用户点了摄像头节点，请求开流播放

private:
    void populateTree();

    Ui::CatalogPage *ui;//管理 UI 文件里定义的所有控件
    QString startupInfo_;
    bool updatingTree_ = false;// 一个"锁"，防止更新树的时候触发信号，造成无限循环
};