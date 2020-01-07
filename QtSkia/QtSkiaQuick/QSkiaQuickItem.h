#pragma once
#include "QtSkia_global.h"
#include <QQuickItem>
#include <QQuickWindow>
class SkCanvas;
class QSkiaQuickItemPrivate;
class QtSkia_API QSkiaQuickItem : public QQuickItem {
    Q_OBJECT
public:
    QSkiaQuickItem(QQuickItem *parent = nullptr);
    virtual ~QSkiaQuickItem() override;
    virtual void draw(SkCanvas* canvas, int elapsed) = 0;
protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
public slots:
    void sync();
    void cleanup();
    void init(int w, int h);
private slots:
    void handleWindowChanged(QQuickWindow *win);
    void onBeforeRendering();
private:
    QSkiaQuickItemPrivate* m_dptr = nullptr;
};
