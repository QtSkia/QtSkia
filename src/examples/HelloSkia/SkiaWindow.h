#pragma once
#include <QWindow>
class QWindow;
class SkiaWindow : public QWindow
{
    Q_OBJECT
public:
    explicit SkiaWindow(QWindow *parent = nullptr);

private:

};

