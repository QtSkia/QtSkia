#pragma once
#include "QtSkia_global.h"
#include <QQuickItem>

class SkCanvas;
class QSkiaQuickItemPrivate;
class QtSkia_API QSkiaQuickItem : public QQuickItem {
    Q_OBJECT
public:
    QSkiaQuickItem(QWindow *parent = nullptr);
    ~QSkiaQuickItem() override;
    virtual void draw(SkCanvas* canvas, int elapsed = 16) = 0;

private:
    QSkiaQuickItem* m_dptr = nullptr;
};
