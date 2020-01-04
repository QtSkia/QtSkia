#include "QSkiaWidget.h"

#include "core/SkData.h"
#include "core/SkImage.h"
#include "core/SkStream.h"
#include "core/SkSurface.h"
class QSkiaWidgetPrivate {
public:
};
QSkiaWidget::QSkiaWidget(QWidget* parent)
    : QWidget(parent)
    , m_dptr(new QSkiaWidgetPrivate)
{
}

QSkiaWidget::~QSkiaWidget()
{
    delete m_dptr;
    m_dptr = nullptr;
}

void QSkiaWidget::paintEvent(QPaintEvent* event)
{
}

void QSkiaWidget::resizeEvent(QResizeEvent* event)
{
}
