#include "QSkiaLottieItem.h"
#include "modules/skottie/include/Skottie.h"
class QSkiaLottieItemPrivate {
private:
    friend class QSkiaLottieItem;

    bool autoPlay = true;
    QSkiaLottieItem::Direction direction = QSkiaLottieItem::Direction::Forward;
    int startFrame = 0;
    int endFrame = 0;
    int frameRate = 60;
    int loops = 1;
    QSkiaLottieItem::Quality quality = QSkiaLottieItem::Quality::MediumQuality;
    QUrl source;
    QSkiaLottieItem::Status status = QSkiaLottieItem::Status::Null;

    sk_sp<skottie::Animation> animation = nullptr;
};
QSkiaLottieItem::QSkiaLottieItem(QQuickItem* parent)
    : QSkiaQuickItem(parent)
    , m_dptr(new QSkiaLottieItemPrivate)
{
}

QSkiaLottieItem::~QSkiaLottieItem()
{
    delete m_dptr;
}

void QSkiaLottieItem::start()
{
    if (!m_dptr->animation) {
        m_dptr->animation = skottie::Animation::MakeFromFile(m_dptr->source.toLocalFile().toStdString().c_str());
        if (!m_dptr->animation) {
            qWarning() << "MakeFromFile failed";
            return;
        }
    }
    m_dptr->animation->seekFrame(0);
}

void QSkiaLottieItem::play()
{

}

void QSkiaLottieItem::pause()
{

}

void QSkiaLottieItem::togglePause()
{

}

void QSkiaLottieItem::stop()
{

}

void QSkiaLottieItem::gotoAndPlay(int frame)
{

}

bool QSkiaLottieItem::gotoAndPlay(const QString &frameMarker)
{
    return false;
}

void QSkiaLottieItem::gotoAndStop(int frame)
{

}

bool QSkiaLottieItem::gotoAndStop(const QString &frameMarker)
{
    return false;
}

double QSkiaLottieItem::getDuration(bool inFrames)
{
    return 0.0f;
}

bool QSkiaLottieItem::autoPlay() const
{
    return m_dptr->autoPlay;
}

QSkiaLottieItem::Direction QSkiaLottieItem::direction() const
{
    return m_dptr->direction;
}

int QSkiaLottieItem::startFrame() const
{
    return m_dptr->startFrame;
}

int QSkiaLottieItem::endFrame() const
{
    return m_dptr->endFrame;
}

int QSkiaLottieItem::frameRate() const
{
    return m_dptr->frameRate;
}

int QSkiaLottieItem::loops() const
{
    return m_dptr->loops;
}

QSkiaLottieItem::Quality QSkiaLottieItem::quality() const
{
    return m_dptr->quality;
}

const QUrl& QSkiaLottieItem::source() const
{
    return m_dptr->source;
}

QSkiaLottieItem::Status QSkiaLottieItem::status() const
{
    return m_dptr->status;
}

void QSkiaLottieItem::setAutoPlay(bool autoPlay)
{
    if (m_dptr->autoPlay == autoPlay)
        return;

    m_dptr->autoPlay = autoPlay;
    emit autoPlayChanged(m_dptr->autoPlay);
}

void QSkiaLottieItem::setDirection(QSkiaLottieItem::Direction direction)
{
    if (m_dptr->direction == direction)
        return;

    m_dptr->direction = direction;
    emit directionChanged(m_dptr->direction);
}

void QSkiaLottieItem::setEndFrame(int endFrame)
{
    if (m_dptr->endFrame == endFrame)
        return;

    m_dptr->endFrame = endFrame;
    emit endFrameChanged(m_dptr->endFrame);
}

void QSkiaLottieItem::setFrameRate(int frameRate)
{
    if (m_dptr->frameRate == frameRate)
        return;

    m_dptr->frameRate = frameRate;
    emit frameRateChanged(m_dptr->frameRate);
}

void QSkiaLottieItem::setLoops(int loops)
{
    if (m_dptr->loops == loops)
        return;

    m_dptr->loops = loops;
    emit loopsChanged(m_dptr->loops);
}

void QSkiaLottieItem::setQuality(QSkiaLottieItem::Quality quality)
{
    if (m_dptr->quality == quality)
        return;

    m_dptr->quality = quality;
    emit qualityChanged(m_dptr->quality);
}

void QSkiaLottieItem::setSource(const QUrl& source)
{
    if (m_dptr->source == source)
        return;

    m_dptr->source = source;
    emit sourceChanged(m_dptr->source);
}

void QSkiaLottieItem::setStatus(QSkiaLottieItem::Status status)
{
    if (m_dptr->status == status)
        return;

    m_dptr->status = status;
    emit statusChanged(m_dptr->status);
}

void QSkiaLottieItem::onInit(int w, int h)
{

}

void QSkiaLottieItem::onResize(int w, int h)
{

}

void QSkiaLottieItem::draw(SkCanvas *canvas, int elapsed)
{
    if (m_dptr->animation) {
        m_dptr->animation->render(canvas);
    }
}
