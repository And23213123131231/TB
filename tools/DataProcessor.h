#pragma once

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

#include "NetworkStructures.h"

/*!
 * \brief The DataProcessor class
 * This class are providing functionality to parse network messages
 */
class DataProcessor {
public:
    DataProcessor() = default;
    virtual ~DataProcessor() = default;

protected:
    /*!
     * \brief parseMessage this method willparse incoming message and will call corresponding methd
     * \param message incoming message
     * \return
     */
    bool parseMessage(const QByteArray& message);

    /*!
     * \brief packListToMessage Usefull method for pack container into message
     * \param list container
     * \param buff output message
     * \return packing result
     */
    template <typename Compressor, typename List>
    bool packListToMessage(const List& list, QByteArray& buff)
    {
        NetworkData::DataPack pack;
        pack.dataSize = list.size();

        QDataStream stream(&buff, QIODevice::WriteOnly);
        if (!pack.writeStream(stream)) {
            return false;
        }

        for (const auto& item : list) {
            Compressor compressor;
            compressor.data = item;
            if (!compressor.writeStream(stream)) {
                return false;
            }
        }
        return true;
    }

    /*!
     * \brief onMovieRecived if incoming message is Movie this method will be called
     */
    virtual void onMovieRecived(const Data::Movie&) = 0;

    /*!
     * \brief onTheaterRecived if incoming message is Theater this method will be called
     */
    virtual void onTheaterRecived(const Data::Theater&) = 0;

    /*!
     * \brief onTicketsRecived if incoming message is Tickets this method will be called
     */
    virtual void onTicketsRecived(const Data::Tickets&) = 0;

    /*!
     * \brief onReuqestMoviesRecived if incoming message is ReuqestMovies this method will be called
     */
    virtual void onReuqestMoviesRecived() = 0;

    /*!
     * \brief onReuqestTheatersRecived if incoming message is ReuqestTheaters this method will be called
     */
    virtual void onReuqestTheatersRecived() = 0;

    /*!
     * \brief onReuqestTicketsRecived if incoming message is ReuqestTickets this method will be called
     */
    virtual void onReuqestTicketsRecived(quint32 theaterId, quint32 movieId) = 0;

    /*!
     * \brief onReuqestBookingRecived if incoming message is ReuqestBooking this method will be called
     */
    virtual void onReuqestBookingRecived(const Data::Tickets&) = 0;

    /*!
     * \brief onBookingResultRecived if incoming message is BookingResult this method will be called
     */
    virtual void onBookingResultRecived(bool) = 0;

    /*!
     * \brief onMoviePackRecived if incoming message is Pack of Movie this method will be called
     */
    virtual void onMoviePackRecived(const QList<Data::Movie>&) = 0;

    /*!
     * \brief onMoviePackRecived if incoming message is Pack of Theater this method will be called
     */
    virtual void onTheaterPackRecived(const QList<Data::Theater>&) = 0;

private:
    bool readPack(qsizetype dataSize, QDataStream& in);
};
