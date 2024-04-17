#include "PlayerController.hpp"
#include "AudioInfo.hpp"
#include <QMediaDevices>
#include <QAudioOutput>
#include <QAudioDevice>

PlayerController::PlayerController(QObject *parent) :
    QAbstractListModel(parent),
    m_playing(false),
    m_mediaPlayer(new QMediaPlayer(this))
{
    m_roleNames.emplace(Role::TitleRole, "title");
    m_roleNames.emplace(Role::AuthorNameRole, "authorName");
    m_roleNames.emplace(Role::SourceRole, "source");
    m_roleNames.emplace(Role::ImageSourceRole, "imageSource");
    m_roleNames.emplace(Role::VideoSourceRole, "videoSource");

    if (!QMediaDevices::audioOutputs().isEmpty())
    {
        m_mediaPlayer->setAudioOutput(new QAudioOutput(m_mediaPlayer));
    }

    addAudio("Eine Kleine Nachtmusik",
             "Wolfgang Amadeus Mozart",
             QUrl("qrc:/Assets/Audio/eine_kleine_nachtmusik.mp3"),
             QUrl("qrc:/Assets/Images/song_1.jpg"));
    addAudio("Symphony No. 5",
             "Ludwig Van Beethoven",
             QUrl("qrc:/Assets/Audio/symphony_no_5.mp3"),
             QUrl("qrc:/Assets/Images/song_2.jpg"));
    addAudio("Air on the G String",
             "Johann Sebastian Bach",
             QUrl("qrc:/Assets/Audio/air_on_the_g_string.mp3"),
             QUrl("qrc:/Assets/Images/song_3.jpg"),
             QUrl("qrc:/Assets/Videos/video_1.avi"));
}

bool PlayerController::playing() const { return m_playing; }

AudioInfo *PlayerController::currentSong() const { return m_currentSong; }

void PlayerController::setCurrentSong(AudioInfo *val)
{
    if (m_currentSong == val) return;

    m_currentSong = val;
    emit currentSongChanged();

    if (m_currentSong) changeAudioSource(m_currentSong->audioSource());
    else
    {
        m_mediaPlayer->stop();
        m_mediaPlayer->setSource(QUrl());
        m_playing = false;
        emit playingChanged();
    }
}

void PlayerController::switchToNext()
{
    const int index = m_audioList.indexOf(m_currentSong);
    if (index + 1 >= m_audioList.size()) setCurrentSong(m_audioList.first());
    else setCurrentSong(m_audioList[index + 1]);
}

void PlayerController::switchToPrevious()
{
    const int index = m_audioList.indexOf(m_currentSong);

    if (index - 1 < 0) setCurrentSong(m_audioList.last());
    else setCurrentSong(m_audioList[index - 1]);
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

void PlayerController::addAudio(const QString &title,
                                const QString &authorName,
                                const QUrl &audioSource,
                                const QUrl &imageSource,
                                const QUrl &videoSource)
{
    AudioInfo *audioInfo = new AudioInfo(this);

    audioInfo->setTitle(title);
    audioInfo->setAuthorName(authorName);
    audioInfo->setAudioSource(audioSource);
    audioInfo->setImageSource(imageSource);
    audioInfo->setVideoSource(videoSource);

    beginInsertRows(QModelIndex(), m_audioList.size(), m_audioList.size());
    if (m_audioList.isEmpty()) setCurrentSong(audioInfo);
    m_audioList << audioInfo;
    endInsertRows();
}

void PlayerController::removeAudio(const int index)
{
    if (index < 0 || index >= m_audioList.size()) return;

    AudioInfo *audioInfo = m_audioList[index];
    if (audioInfo == m_currentSong)
    {
        if (m_audioList.size() > 1)
        {
            if (index != 0) setCurrentSong(m_audioList[index - 1]);
            else setCurrentSong(m_audioList[index + 1]);
        }
        else setCurrentSong(nullptr);
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_audioList.removeAt(index);
    audioInfo->deleteLater();
    endRemoveRows();
}

void PlayerController::switchToAudio(const int index)
{
    if (index < 0 || index >= m_audioList.size()) return;
    setCurrentSong(m_audioList[index]);
}

int PlayerController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.size();
}

QVariant PlayerController::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (!index.isValid() || row < 0 || row >= m_audioList.size()) return {};

    AudioInfo *audioInfo = m_audioList[row];
    switch (role)
    {
    case TitleRole:
        return audioInfo->title();
    case AuthorNameRole:
        return audioInfo->authorName();
    case SourceRole:
        return audioInfo->audioSource();
    case ImageSourceRole:
        return audioInfo->imageSource();
    case VideoSourceRole:
        return audioInfo->videoSource();
    default: return {};
    }
}

QHash<int, QByteArray> PlayerController::roleNames() const { return m_roleNames; }
