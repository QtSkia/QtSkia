#pragma once
#include "QtSkia_global.h"
#include <QQuickItem>

class SkCanvas;
class QtSkia_API QSkiaQuickItem : public QQuickItem {
    Q_OBJECT
public:
    QSkiaQuickItem(QQuickItem *parent = nullptr);
    virtual ~QSkiaQuickItem() override = default;

    virtual void onInit(int w, int h) = 0;

    virtual void draw(SkCanvas* canvas, int elapsed) = 0;

protected:
    QSGNode * updatePaintNode(QSGNode *node, UpdatePaintNodeData *data) override;

};
