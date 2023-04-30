#pragma once

#include <QDataStream>
#include <QMetaType>
#include <QObject>
#include <QSet>
#include <QString>

#include <functional>

#include "DataStructures.h"

namespace NetworkData {
/*!
 * \brief The NetworkDataSctructure class
 * providing basic methods to streaming the data
 */
struct INetworkDataSctructure {
    Q_GADGET

public:
    INetworkDataSctructure() = default;
    virtual ~INetworkDataSctructure() = default;

    /*!
     * \brief The DataType enum
     * It should be the lead byte on any derived structure during writing
     */
    enum class DataType : quint8 {
        Movie = 0,
        Theater,
        Tickets,
        ReuqestMovies,
        ReuqestTheaters,
        ReuqestTickets,
        ReuqestBooking,
        BookingResult,
        DataPack,
        // Reserved value for unexpecting data
        _Last = std::numeric_limits<quint8>::max()
    };
    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    virtual bool readStream(QDataStream& in, DataType type) = 0;
    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    virtual bool writeStream(QDataStream& out, DataType type) const = 0;

    /*!
     * \brief getDataType
     * \param in data stream
     * \return next Data type or _DataLast if data is not valid
     */
    static DataType getDataType(QDataStream& in);

protected:
    /*!
     * \brief readStream with transaction and data type checking
     * \param in stream
     * \param expectedtype Type of current object
     * \param readDataCollback reading callback
     * \return result
     */
    bool transactionReadStream(QDataStream& in, DataType expectedtype, std::function<void(QDataStream& in)> readDataCollback);

    /*!
     * \brief readStream with transaction and data type checking
     * \param in stream
     * \param expectedtype Type of current object
     * \param writeDataCollback writing callback
     * \return result
     */
    bool transactionWriteStream(QDataStream& out, DataType expectedtype, std::function<void(QDataStream& in)> writeDataCollback) const;
};

/*!
 * \brief The Movie class represent a movie description only
 */
struct Movie : public INetworkDataSctructure {
    Q_GADGET

public:
    Movie() = default;
    ~Movie() override = default;

    Data::Movie data;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::Movie) override;
    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::Movie) const override;
};

/*!
 * \brief The Theaters class represent theater instance with movies
 */
struct Theater : public INetworkDataSctructure {
    Q_GADGET

public:
    Theater() = default;
    ~Theater() override = default;

    Data::Theater data;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::Theater) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::Theater) const override;
};

/*!
 * \brief The Theaters class represent theater instance with movies
 */
struct Tickets : public INetworkDataSctructure {
    Q_GADGET

public:
    Tickets() = default;
    ~Tickets() override = default;

    Data::Tickets data;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::Tickets) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::Tickets) const override;
};

/*!
 * \brief The BookingResult class represent booking result state
 */
struct BookingResult : public INetworkDataSctructure {
    Q_GADGET

public:
    BookingResult() = default;
    ~BookingResult() override = default;

    bool result = false;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::BookingResult) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::BookingResult) const override;
};

/*!
 * \brief The ReuqestTheaters class
 * Requsting theaters from server
 */
struct ReuqestTheaters : public INetworkDataSctructure {
    Q_GADGET

public:
    ReuqestTheaters() = default;
    ~ReuqestTheaters() override = default;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::ReuqestTheaters) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::ReuqestTheaters) const override;
};

/*!
 * \brief The ReuqestMovies class
 * Requesting movies from server
 */
struct ReuqestMovies : public INetworkDataSctructure {
    Q_GADGET

public:
    ReuqestMovies() = default;
    ~ReuqestMovies() override = default;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::ReuqestMovies) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::ReuqestMovies) const override;
};

/*!
 * \brief The ReuqestTickets class
 * Requesting tickets for given movie and theater
 */
struct ReuqestTickets : public INetworkDataSctructure {
    Q_GADGET

public:
    quint32 theaterId = 0;
    quint32 movieId = 0;

    ReuqestTickets() = default;
    ~ReuqestTickets() override = default;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::ReuqestTickets) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::ReuqestTickets) const override;
};

/*!
 * \brief The ReuqestTickets class
 * Requesting tickets booking
 */
struct ReuqestBooking : public Tickets {
    Q_GADGET

public:
    ReuqestBooking() = default;
    ~ReuqestBooking() override = default;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::ReuqestBooking) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::ReuqestBooking) const override;
};

/*!
 * \brief The PackData class
 * Indicates that several objects will follow next
 */
struct DataPack : public INetworkDataSctructure {
    Q_GADGET

public:
    qsizetype dataSize = 0;

    DataPack() = default;
    ~DataPack() override = default;

    /*!
     * \brief readStream Restore object from  stream
     * \param in stream
     * \return result
     */
    bool readStream(QDataStream& in, DataType type = DataType::DataPack) override;

    /*!
     * \brief writeStream
     * \param out write object to stram
     * \return result
     */
    bool writeStream(QDataStream& out, DataType type = DataType::DataPack) const override;
};

} // namespace NetworkData
