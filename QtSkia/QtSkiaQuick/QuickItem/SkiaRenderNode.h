#pragma once
#include <QSGRenderNode>
#include <QTime>
class QSkiaQuickItem;
class SkiaRenderNode : public QSGRenderNode
{
public:
    SkiaRenderNode(QSkiaQuickItem *parent);
public:
    virtual void render(const RenderState *state) override;
    virtual void releaseResources() override;
    virtual StateFlags changedStates() const override;
    virtual RenderingFlags flags() const override;
private:
    QSkiaQuickItem *m_item;
    QTime m_lastTime;
    QSizeF m_lastSize;
};

