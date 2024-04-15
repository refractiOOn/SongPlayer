#pragma once

#include <QObject>
#include <QMediaPlayer>

class PlayerController: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PlayerController)

    Q_PROPERTY(uint currentSongIndex READ currentSongIndex NOTIFY currentSongIndexChanged)
    Q_PROPERTY(uint songCount READ songCount NOTIFY songCountChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)

public:
    explicit PlayerController(QObject *parent = nullptr);
    ~PlayerController() override = default;

    uint currentSongIndex() const;
    uint songCount() const;
    bool playing() const;

    Q_INVOKABLE void switchToNext();
    Q_INVOKABLE void switchToPrevious();
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void changeAudioSource(const QUrl &source);

private:
    uint m_currentSongIndex;
    uint m_songCount;
    bool m_playing;
    QMediaPlayer *m_mediaPlayer;

signals:
    void currentSongIndexChanged();
    void songCountChanged();
    void playingChanged();

}; // class PlayerController
