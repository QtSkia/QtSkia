#pragma once
#include "QSkiaQuickItem.h"

class QSkiaLottieItemPrivate;
class QtSkia_API QSkiaLottieItem : public QSkiaQuickItem {
    Q_OBJECT

    Q_PROPERTY(bool autoPlay READ autoPlay WRITE setAutoPlay NOTIFY autoPlayChanged)
    Q_PROPERTY(Direction direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(int startFrame READ startFrame NOTIFY startFrameChanged)
    Q_PROPERTY(int endFrame READ endFrame NOTIFY endFrameChanged)
    Q_PROPERTY(int frameRate READ frameRate WRITE setFrameRate NOTIFY frameRateChanged)
    Q_PROPERTY(int loops READ loops WRITE setLoops NOTIFY loopsChanged)
    Q_PROPERTY(Quality quality READ quality WRITE setQuality NOTIFY qualityChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
public:
    enum Direction {
        Forward = 0,
        Reverse,
    };
    Q_ENUM(Direction)
    enum Quality {
        LowQuality,
        MediumQuality,
        HighQuality
    };
    Q_ENUM(Quality)
    enum Status {
        Null,
        Loading,
        Ready,
        Error
    };
    Q_ENUM(Status)

    enum LoopCount { Infinite = -1 };
    Q_ENUM(LoopCount)

public:
    QSkiaLottieItem(QQuickItem* parent = nullptr);
    virtual ~QSkiaLottieItem() override;
    static void registerLottie()
    {
        qmlRegisterType<QSkiaLottieItem>("SkiaLottieItem", 1, 0, "SkiaLottieItem");
    }
    Q_INVOKABLE void start();

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void togglePause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void gotoAndPlay(int frame);
    Q_INVOKABLE bool gotoAndPlay(const QString& frameMarker);
    Q_INVOKABLE void gotoAndStop(int frame);
    Q_INVOKABLE bool gotoAndStop(const QString& frameMarker);
    Q_INVOKABLE double getDuration(bool inFrames = false);

public:
    //properties
    bool autoPlay() const;

    Direction direction() const;

    int startFrame() const;

    int endFrame() const;

    int frameRate() const;

    int loops() const;

    Quality quality() const;

    const QUrl& source() const;

    Status status() const;

signals:
    //property change
    void autoPlayChanged(bool autoPlay);

    void directionChanged(Direction direction);

    void startFrameChanged(int startFrame);

    void endFrameChanged(int endFrame);

    void frameRateChanged(int frameRate);

    void loopsChanged(int loops);

    void qualityChanged(Quality quality);

    void sourceChanged(QUrl source);

    void statusChanged(Status status);
signals:
    void finished();

public slots:

    void setAutoPlay(bool autoPlay);

    void setDirection(Direction direction);

    void setEndFrame(int endFrame);

    void setFrameRate(int frameRate);

    void setLoops(int loops);

    void setQuality(Quality quality);

    void setSource(const QUrl& source);

    void setStatus(Status status);

protected:
    virtual void onInit(int w, int h) override;
    virtual void onResize(int w, int h) override;
    virtual void draw(SkCanvas* canvas, int elapsed) override;

private:
    QSkiaLottieItemPrivate* m_dptr;
};
