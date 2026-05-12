#pragma once

#include <QWidget>//继承 Qt 基础界面控件

QT_BEGIN_NAMESPACE
namespace Ui {
class EntryPage;
}
QT_END_NAMESPACE

class EntryPage : public QWidget
{
    Q_OBJECT

public:
    explicit EntryPage(QWidget *parent = nullptr);
    ~EntryPage() override;

signals:
    void connectRequested(const QString &ip, quint16 port);//信号

private:
    Ui::EntryPage *ui;//界面指针
};