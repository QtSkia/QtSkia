#pragma once
#include <QSGRenderNode>
#include <QTime>
class QSkiaQuickItem;
class SkiaRenderNode : public QSGRenderNode
{
public:
    SkiaRenderNode(QSkiaQuickItem *parent);
    ~SkiaRenderNode() override;
public:
    void render(const RenderState *state) override;
    void releaseResources() override;
    StateFlags changedStates() const override;
    RenderingFlags flags() const override;
    QRectF rect() const override;
private:
    QSkiaQuickItem *m_item;
    QTime m_lastTime;
    QSizeF m_lastSize;
};

