#pragma once
#include "QtSkia_global.h"
#include <QWidget>
class SkCanvas;
class QSkiaWidgetPrivate;
class QtSkia_API QSkiaWidget : public QWidget {
    Q_OBJECT
public:
    QSkiaWidget(QWidget* parent = nullptr);
    ~QSkiaWidget() override;

    virtual void dawn(SkCanvas* canvas, int elapsed = 16) = 0;

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QSkiaWidgetPrivate* m_dptr = nullptr;
};
