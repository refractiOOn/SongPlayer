#pragma once

#include <QAbstractListModel>

class QNetworkAccessManager;
class QNetworkReply;
class AudioInfo;
class AudioSearchModel: public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(AudioSearchModel)

    Q_PROPERTY(bool isSearching READ isSearching NOTIFY isSearchingChanged)

public:
    enum Role
    {
        NameRole = Qt::UserRole + 1,
        AuthorRole,
        SourceRole,
        ImageSourceRole

    }; // enum Role

    const QString URL{ "https://api.jamendo.com/v3.0/tracks/" };
    const QString CLIENT_ID{ "324d26fa" };

public:
    explicit AudioSearchModel(QObject *parent = nullptr);
    ~AudioSearchModel() override = default;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void searchSong(const QString &name);
    void parseData();

    bool isSearching() const;
    void setIsSearching(const bool val);

signals:
    void isSearchingChanged();

private:
    QHash<int, QByteArray> m_roleNames;
    QVector<AudioInfo *> m_audioList;
    QNetworkAccessManager *m_accessManager;
    QNetworkReply *m_reply;
    bool m_isSearching;

}; // class AudioSearchModel
