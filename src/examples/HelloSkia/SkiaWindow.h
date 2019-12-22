#pragma once
#include <QWindow>
class QWindow;
class SkiaWindow : public QWindow
{
    Q_OBJECT
public:
    explicit SkiaWindow(QWindow *parent = nullptr);

    void resize(int w, int h);
    void show();
private:

};

