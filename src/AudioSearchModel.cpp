#include "AudioSearchModel.hpp"
#include <AudioInfo.hpp>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

AudioSearchModel::AudioSearchModel(QObject *parent):
    QAbstractListModel(parent),
    m_accessManager(new QNetworkAccessManager(this)),
    m_reply(nullptr),
    m_isSearching(false)
{
    m_roleNames.emplace(NameRole, "name");
    m_roleNames.emplace(AuthorRole, "author");
    m_roleNames.emplace(SourceRole, "source");
    m_roleNames.emplace(ImageSourceRole, "imageSource");
}

int AudioSearchModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_audioList.size();
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if (!index.isValid() || row < 0 || row >= m_audioList.size()) return {};

    AudioInfo *info = m_audioList[row];
    switch (role)
    {
    case NameRole: return info->title();
    case AuthorRole: return info->authorName();
    case SourceRole: return info->audioSource();
    case ImageSourceRole: return info->imageSource();
    default: return {};
    }
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const { return m_roleNames; }

void AudioSearchModel::searchSong(const QString &name)
{
    if (!name.trimmed().isEmpty())
    {
        if (m_reply)
        {
            m_reply->abort();
            m_reply->deleteLater();
            m_reply = nullptr;
        }

        QUrlQuery query;
        query.addQueryItem("client_id", CLIENT_ID);
        query.addQueryItem("namesearch", name);
        query.addQueryItem("format", "json");

        QUrl requestUrl = URL;
        requestUrl.setQuery(query);
        const QNetworkRequest request(requestUrl);

        setIsSearching(true);
        m_reply = m_accessManager->get(request);
        QObject::connect(m_reply, &QNetworkReply::finished, this, &AudioSearchModel::parseData);
    }
}

void AudioSearchModel::parseData()
{
    if (m_reply->error() == QNetworkReply::NoError)
    {
        beginResetModel();

        qDeleteAll(m_audioList);
        m_audioList.clear();

        const QByteArray data = m_reply->readAll();
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        const QJsonObject headers = jsonDoc["headers"].toObject();

        if (headers["status"].toString() == "success")
        {
            const QJsonArray results = jsonDoc["results"].toArray();

            for (const auto &el : results)
            {
                QJsonObject entry = el.toObject();
                if (entry["audiodownload_allowed"].toBool())
                {
                    AudioInfo *audioInfo = new AudioInfo(this);
                    audioInfo->setTitle(entry["name"].toString());
                    audioInfo->setAuthorName(entry["artist_name"].toString());
                    audioInfo->setImageSource(entry["image"].toString());
                    audioInfo->setAudioSource(entry["audiodownload"].toString());

                    m_audioList << audioInfo;
                }
            }
        }
        else qWarning() << headers["error_string"];

        endResetModel();
    }
    else if (m_reply->error() == QNetworkReply::OperationCanceledError)
    {
        qCritical() << "Reply failed, error:" << m_reply->errorString();
    }

    setIsSearching(false);
    m_reply->deleteLater();
    m_reply = nullptr;
}

bool AudioSearchModel::isSearching() const { return m_isSearching; }

void AudioSearchModel::setIsSearching(const bool val)
{
    if (m_isSearching == val) return;

    m_isSearching = val;
    emit isSearchingChanged();
}
