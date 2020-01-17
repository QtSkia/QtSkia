#pragma once
#include "QtSkia_global.h"
#include <QQuickItem>
class SkCanvas;
class QSkiaQuickItemPrivate;
class QtSkia_API QSkiaQuickItem : public QQuickItem {
    Q_OBJECT
public:
    QSkiaQuickItem(QQuickItem* parent = nullptr);
    virtual ~QSkiaQuickItem() override;
    //after skia init. Note: this function work in Skia Renderer Thread.
    virtual void onInit(int w, int h) = 0;
    //after skia resize. Note: this function work in Skia Renderer Thread.
    virtual void onResize(int w, int h) = 0;
    //draw. Note: this function work in Skia Renderer Thread.
    virtual void draw(SkCanvas* canvas, int elapsed) = 0;

protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData* data) override;

private:
    QSkiaQuickItemPrivate *m_dptr;
};
