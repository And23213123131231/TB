#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QStack>
#include <QVariantMap>

#include "tools/DataStructures.h"

/*!
 * \brief The MoviesModelController class
 * This class represents the Movies Model
 */
class MoviesModelController : public QAbstractListModel {
    Q_OBJECT

    enum MovieRoles {
        IdRole = Qt::UserRole + 1,
        ScoreRole,
        NameRole,
        CriticsRole,
        SynopsisRole,
        StarringRole,
        DirectedRole
    };

public:
    /*!
     * \brief MoviesModelController
     * \param parent parent object
     */
    MoviesModelController(QObject* parent = nullptr);
    ~MoviesModelController() override;

    QHash<int, QByteArray> roleNames() const override;

    /*!
     * \brief get Get singletone object
     * \return instance
     */
    static MoviesModelController* get();

    void setModelList(const QList<Data::Movie>& list);

    QVariant data(const QModelIndex& index, int role) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

private:
    static MoviesModelController* s_movies;
    QList<Data::Movie> m_moviesList;
};
