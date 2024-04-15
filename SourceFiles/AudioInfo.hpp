#pragma once

#include <QObject>
#include <QtQml>

class AudioInfo: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AudioInfo)

    QML_ELEMENT
    Q_PROPERTY(uint songIndex READ songIndex WRITE setSongIndex NOTIFY songIndexChanged REQUIRED)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged)
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(QUrl videoSource READ videoSource WRITE setVideoSource NOTIFY videoSourceChanged)
    Q_PROPERTY(QUrl audioSource READ audioSource WRITE setAudioSource NOTIFY audioSourceChanged REQUIRED)

public:
    explicit AudioInfo(QObject *parent = nullptr);
    ~AudioInfo() override = default;

    uint songIndex() const;
    void setSongIndex(const int val);

    QString title() const;
    void setTitle(const QString &val);

    QString authorName() const;
    void setAuthorName(const QString &val);

    QUrl imageSource() const;
    void setImageSource(const QUrl &val);

    QUrl videoSource() const;
    void setVideoSource(const QUrl &val);

    QUrl audioSource() const;
    void setAudioSource(const QUrl &val);

private:
    uint m_songIndex;
    QString m_title;
    QString m_authorName;
    QUrl m_imageSource;
    QUrl m_videoSource;
    QUrl m_audioSource;

signals:
    void songIndexChanged();
    void titleChanged();
    void authorNameChanged();
    void imageSourceChanged();
    void videoSourceChanged();
    void audioSourceChanged();

}; // class AudioInfo
