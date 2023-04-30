#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QStack>
#include <QVariantMap>

#include "tools/DataStructures.h"

/*!
 * \brief The TheatersModelController class
 * This class represents the Theaters Model for given movie
 */
class TheatersModelController : public QAbstractListModel {
    Q_OBJECT

    enum MovieRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    Q_PROPERTY(int movieId READ movieId WRITE setMovieId NOTIFY movieIdChanged)

public:
    /*!
     * \brief TheatersModelController
     * \param parent parent object
     */
    TheatersModelController(QObject* parent = nullptr);
    ~TheatersModelController() override;

    QHash<int, QByteArray> roleNames() const override;

    /*!
     * \brief get Get singletone object
     * \return instance
     */
    static TheatersModelController* get();

    void setModelList(const QList<Data::Theater>& list);

    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /*!
     * \brief movieId
     * \return current movie id or 0 (no filter)
     */
    int movieId() const;

    /*!
     * \brief setMovieId set current movie id
     */
    void setMovieId(int id);

signals:
    void movieIdChanged();

private:
    static TheatersModelController* s_theaters;
    QList<Data::Theater> m_theatersList;
    QList<const Data::Theater*> m_currentTheaters;
    int m_movieId = 0;

    void updateCurrentTheatersList();
};
