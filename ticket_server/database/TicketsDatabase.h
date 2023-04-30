#pragma once

#include <QHash>
#include <QObject>
#include <QSet>

#include "tools/DataStructures.h"

class TicketsDatabase : public QObject {
    Q_OBJECT

public:
    explicit TicketsDatabase(QObject* parent = nullptr);

    /*!
     * \brief init this function will create a database wuth tickets and theaters based on input json
     * \param data input json content
     * \return init result state
     */
    bool init(const QByteArray& data);

    /*!
     * \brief movies
     * \return List with all the available movies
     */
    const QVector<Data::Movie>& movies() const { return m_movies; };

    /*!
     * \brief theaters
     * \return List with all the available theaters
     */
    const QVector<Data::Theater>& theaters() const { return m_theaters; };

    /*!
     * \brief tickets
     * \return List with all the available tickets
     */
    const QVector<Data::Tickets>& tickets() const { return m_tickets; };

    /*!
     * \brief theaterMovieTickets providing actual information about seats status
     * \param theaterId theater id
     * \param movieId movie id
     * \return
     */
    [[nodiscard]] Data::Tickets theaterMovieTickets(quint32 theaterId, quint32 movieId);

    /*!
     * \brief bookTickets attempt to book tickets
     * \param tickets theaterId + movieId + wishful seats
     * \return
     */
    bool bookTickets(const Data::Tickets& tickets);
signals:

private:
    QVector<Data::Movie> m_movies;
    QVector<Data::Theater> m_theaters;
    QVector<Data::Tickets> m_tickets;
};
