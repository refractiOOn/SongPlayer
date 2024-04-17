#pragma once

#include <QAbstractListModel>
#include <QMediaPlayer>

class AudioInfo;
class PlayerController: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PlayerController)

    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(AudioInfo *currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged)

public:
    enum Role
    {
        TitleRole = Qt::UserRole + 1,
        AuthorNameRole,
        SourceRole,
        ImageSourceRole,
        VideoSourceRole

    }; // enum Role

public:
    explicit PlayerController(QObject *parent = nullptr);
    ~PlayerController() override = default;

    bool playing() const;

    AudioInfo *currentSong() const;
    void setCurrentSong(AudioInfo *val);

    Q_INVOKABLE void switchToNext();
    Q_INVOKABLE void switchToPrevious();
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void changeAudioSource(const QUrl &source);
    Q_INVOKABLE void addAudio(const QString &title,
                  const QString &authorName,
                  const QUrl &audioSource,
                  const QUrl &imageSource,
                  const QUrl &videoSource = QUrl());
    Q_INVOKABLE void removeAudio(const int index);
    Q_INVOKABLE void switchToAudio(const int index);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QHash<int, QByteArray> m_roleNames;
    QVector<AudioInfo *> m_audioList;

    bool m_playing;
    QMediaPlayer *m_mediaPlayer;
    AudioInfo *m_currentSong;

signals:
    void playingChanged();
    void currentSongChanged();

}; // class PlayerController
