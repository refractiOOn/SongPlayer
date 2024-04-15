#include "PlayerController.hpp"
#include <QMediaDevices>
#include <QAudioOutput>
#include <QAudioDevice>

PlayerController::PlayerController(QObject *parent) :
    QObject(parent),
    m_currentSongIndex(0),
    m_songCount(3),
    m_playing(false),
    m_mediaPlayer(new QMediaPlayer(this))
{
    if (!QMediaDevices::audioOutputs().isEmpty())
    {
        m_mediaPlayer->setAudioOutput(new QAudioOutput(m_mediaPlayer));
    }
}

uint PlayerController::currentSongIndex() const { return m_currentSongIndex; }
uint PlayerController::songCount() const { return m_songCount; }
bool PlayerController::playing() const { return m_playing; }

void PlayerController::switchToNext()
{
    if (m_currentSongIndex + 1 >= m_songCount) m_currentSongIndex = 0;
    else ++m_currentSongIndex;

    emit currentSongIndexChanged();
}

void PlayerController::switchToPrevious()
{
    if (m_currentSongIndex - 1 < 0) m_currentSongIndex = m_songCount - 1;
    else --m_currentSongIndex;

    emit currentSongIndexChanged();
}

void PlayerController::playPause()
{
    m_playing = !m_playing;
    emit playingChanged();

    if (m_playing) m_mediaPlayer->play();
    else m_mediaPlayer->pause();
}

void PlayerController::changeAudioSource(const QUrl &source)
{
    m_mediaPlayer->stop();
    m_mediaPlayer->setSource(source);

    if (m_playing) m_mediaPlayer->play();
}
