#include "QSkiaQuickItem.h"
#include "SkiaRenderNode.h"
QSkiaQuickItem::QSkiaQuickItem(QQuickItem* parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAntialiasing(true);
}

QSGNode* QSkiaQuickItem::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
{
    QSGRenderNode* n = static_cast<QSGRenderNode*>(node);
    if (!n) {
        n = new SkiaRenderNode(this);
    }
    return n;
}

void QSkiaQuickItem::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    update();
    QQuickItem::itemChange(change, data);
}
