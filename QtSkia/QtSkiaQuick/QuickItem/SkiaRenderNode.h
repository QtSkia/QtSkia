#pragma once
#include <QSGRenderNode>
#include <QTime>
class QSkiaQuickItem;
class SkiaRenderNodePrivate;
class SkiaRenderNode : public QSGRenderNode {
public:
    SkiaRenderNode(QSkiaQuickItem* parent);
    ~SkiaRenderNode() override;

public:
    void render(const RenderState* state) override;

protected:
    StateFlags changedStates() const override
    {
        return BlendState;
    }

    QSGRenderNode::RenderingFlags flags() const override
    {
        return BoundedRectRendering | DepthAwareRendering;
    }
private:
    SkiaRenderNodePrivate* m_dptr;
    QSkiaQuickItem* m_item;
    QTime m_lastTime;
    QSize m_lastSize;
};
