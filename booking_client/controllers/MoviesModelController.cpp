#include <QDebug>
#include <QUrl>

#include "MoviesModelController.h"

MoviesModelController* MoviesModelController::s_movies(nullptr);

MoviesModelController::MoviesModelController(QObject* parent)
    : QAbstractListModel(parent)
{
    s_movies = this;
}

MoviesModelController::~MoviesModelController()
{
    s_movies = nullptr;
}

QHash<int, QByteArray> MoviesModelController::MoviesModelController::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[ScoreRole] = "score";
    roles[NameRole] = "name";
    roles[CriticsRole] = "critics";
    roles[SynopsisRole] = "synopsis";
    roles[StarringRole] = "starring";
    roles[DirectedRole] = "directed";
    return roles;
}

MoviesModelController* MoviesModelController::get()
{
    return s_movies;
}

void MoviesModelController::setModelList(const QList<Data::Movie>& list)
{
    beginResetModel();
    m_moviesList = list;
    std::sort(m_moviesList.begin(), m_moviesList.end());
    endResetModel();
}

QVariant MoviesModelController::data(const QModelIndex& index, int role) const
{
    QVariant value;

    if (index.isValid()) {
        if (role > Qt::UserRole) {
            switch (role) {
            case IdRole:
                value = m_moviesList[index.row()].id;
                break;
            case ScoreRole:
                value = m_moviesList[index.row()].score;
                break;
            case NameRole:
                value = m_moviesList[index.row()].name;
                break;
            case CriticsRole:
                value = m_moviesList[index.row()].critics;
                break;
            case SynopsisRole:
                value = m_moviesList[index.row()].synopsis;
                break;
            case StarringRole:
                value = m_moviesList[index.row()].starring;
                break;
            case DirectedRole:
                value = m_moviesList[index.row()].directed;
                break;
            default:
                break;
            }
        }
    }
    return value;
}

int MoviesModelController::rowCount(const QModelIndex& parent) const
{
    return m_moviesList.size();
}

int MoviesModelController::columnCount(const QModelIndex& parent) const
{
    return 1;
}
