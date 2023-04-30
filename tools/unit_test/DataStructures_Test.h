#pragma once

#include <QTest>

namespace Test {
class DataStructures_Test : public QObject {
    Q_OBJECT
public:
    DataStructures_Test() = default;
    ~DataStructures_Test() override = default;

private slots:
    void testMovieStruct();
    void testTheaterStruct();
    void testTicketsStruct();
};
}
