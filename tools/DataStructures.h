#pragma once

#include <QDataStream>
#include <QMetaType>
#include <QObject>
#include <QSet>
#include <QString>

namespace Data {
/*!
 * \brief The Movie class represent a movie description only
 */
struct Movie {
    Q_GADGET

public:
    quint32 id = 0;
    quint32 score = 0;
    QString name;
    QString critics;
    QString synopsis;
    QString starring;
    QString directed;

    /*!
     * \brief operator <
     * \param other
     * \return comparison in ascending sort order by id
     */
    bool operator<(const Movie& other) const
    {
        return id < other.id;
    }

    /*!
     * \brief hasSameId comparsion by Id
     * \param other
     * \return comparison result
     */
    bool hasSameId(const Movie& other) const
    {
        return id == other.id;
    }
};

/*!
 * \brief The Theaters class represent theater instance with movies and tickets
 */
struct Theater {
    Q_GADGET

public:
    quint32 id = 0;
    QString name;
    QSet<quint32> movies;

    /*!
     * \brief operator <
     * \param other
     * \return comparison in ascending sort order by id
     */
    bool operator<(const Theater& other) const
    {
        return id < other.id;
    }

    /*!
     * \brief hasSameId comparsion by Id
     * \param other
     * \return comparison result
     */
    bool hasSameId(const Theater& other) const
    {
        return id == other.id;
    }
};

/*!
 * \brief The Tickets class represent theater movie booking status
 */
struct Tickets {
    Q_GADGET

public:
    quint32 theaterId = 0;
    quint32 movieId = 0;
    quint32 rowCount = 0;
    quint32 colCount = 0;

    enum class Status : quint8 {
        Free = 0,
        Booked,
        TryBook
    };

    QVector<Status> ticketsStatus;

    /*!
     * \brief operator <
     * \param other
     * \return comparison in ascending sort order by theaterId and movieId
     */
    bool operator<(const Tickets& other) const
    {
        if (theaterId < other.theaterId) {
            return true;
        } else if (theaterId == other.theaterId && movieId < other.movieId) {
            return true;
        }
        return false;
    }

    /*!
     * \brief  hasSameId  sort order by theaterId and movieId
     * \param other
     * \return comparison result
     */
    bool hasSameId(const Tickets& other) const
    {
        return theaterId == other.theaterId && movieId == other.movieId;
    }
};

} // namespace NetworkData
