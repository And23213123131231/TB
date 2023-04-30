#include <QDebug>
#include <QUrl>

#include "TheatersModelController.h"

TheatersModelController* TheatersModelController::s_theaters(nullptr);

TheatersModelController::TheatersModelController(QObject* parent)
    : QAbstractListModel(parent)
{
    s_theaters = this;
}

TheatersModelController::~TheatersModelController()
{
    s_theaters = nullptr;
}

QHash<int, QByteArray> TheatersModelController::TheatersModelController::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    return roles;
}

TheatersModelController* TheatersModelController::get()
{
    return s_theaters;
}

void TheatersModelController::setModelList(const QList<Data::Theater>& list)
{
    beginResetModel();
    m_theatersList = list;
    updateCurrentTheatersList();
    std::sort(m_theatersList.begin(), m_theatersList.end());
    endResetModel();
}

QVariant TheatersModelController::data(const QModelIndex& index, int role) const
{
    QVariant value;

    if (index.isValid()) {
        if (role > Qt::UserRole) {
            switch (role) {
            case IdRole:
                value = m_currentTheaters[index.row()]->id;
                break;
            case NameRole:
                value = m_currentTheaters[index.row()]->name;
                break;
            default:
                break;
            }
        }
    }
    return value;
}

int TheatersModelController::rowCount(const QModelIndex& parent) const
{
    return m_currentTheaters.size();
}

int TheatersModelController::columnCount(const QModelIndex& parent) const
{
    return 1;
}

int TheatersModelController::movieId() const
{
    return m_movieId;
}

void TheatersModelController::setMovieId(int id)
{
    if (id != m_movieId) {
        m_movieId = id;
        updateCurrentTheatersList();
        emit movieIdChanged();
    }
}

void TheatersModelController::updateCurrentTheatersList()
{
    beginResetModel();
    m_currentTheaters.clear();
    for (const auto& theater : m_theatersList) {
        if (m_movieId == 0) {
            m_currentTheaters.push_back(&theater);
        } else if (theater.movies.contains(m_movieId)) {
            m_currentTheaters.push_back(&theater);
        }
    }
    endResetModel();
}
