#include "AudioInfo.hpp"

AudioInfo::AudioInfo(QObject *parent):
    QObject(parent)
{}

uint AudioInfo::songIndex() const { return m_songIndex; }
void AudioInfo::setSongIndex(const int val)
{
    if (m_songIndex == val) return;

    m_songIndex = val;
    emit songIndexChanged();
}

QString AudioInfo::title() const { return m_title; }
void AudioInfo::setTitle(const QString &val)
{
    if (m_title == val) return;

    m_title = val;
    emit titleChanged();
}

QString AudioInfo::authorName() const { return m_authorName; }
void AudioInfo::setAuthorName(const QString &val)
{
    if (m_authorName == val) return;

    m_authorName = val;
    emit authorNameChanged();
}

QUrl AudioInfo::imageSource() const { return m_imageSource; }
void AudioInfo::setImageSource(const QUrl &val)
{
    if (m_imageSource == val) return;

    m_imageSource = val;
    emit imageSourceChanged();
}

QUrl AudioInfo::videoSource() const { return m_videoSource; }
void AudioInfo::setVideoSource(const QUrl &val)
{
    if (m_videoSource == val) return;

    m_videoSource = val;
    emit videoSourceChanged();
}

QUrl AudioInfo::audioSource() const { return m_audioSource; }
void AudioInfo::setAudioSource(const QUrl &val)
{
    if (m_audioSource == val) return;

    m_audioSource = val;
    emit audioSourceChanged();
}
