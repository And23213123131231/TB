#include "DataStructures_Test.h"

#include "../DataStructures.h"

namespace {
template <typename T>
void comparsionTest(T obj1, T obj2Gt1, T obj3Eq1)
{

    QVERIFY(obj1 < obj2Gt1);
    QVERIFY(!(obj2Gt1 < obj1));

    QVERIFY(!obj1.hasSameId(obj2Gt1));
    QVERIFY(obj1.hasSameId(obj3Eq1));
}
}

namespace Test {
void DataStructures_Test::testMovieStruct()
{
    // init test
    {
        Data::Movie movie;
        QCOMPARE_EQ(movie.id, 0);
        QCOMPARE_EQ(movie.score, 0);
        QCOMPARE_EQ(movie.name, "");
        QCOMPARE_EQ(movie.critics, "");
        QCOMPARE_EQ(movie.synopsis, "");
        QCOMPARE_EQ(movie.starring, "");
        QCOMPARE_EQ(movie.directed, "");
    }

    // comparsion test
    comparsionTest(Data::Movie { 1 }, Data::Movie { 2 }, Data::Movie { 1 });
}

void DataStructures_Test::testTheaterStruct()
{
    // init test
    {
        Data::Theater theater;
        QCOMPARE_EQ(theater.id, 0);
        QCOMPARE_EQ(theater.name, "");
        QCOMPARE_EQ(theater.movies.size(), 0);
    }

    // comparsion test
    comparsionTest(Data::Theater { 1 }, Data::Theater { 2 }, Data::Theater { 1 });
}

void DataStructures_Test::testTicketsStruct()
{
    // init test
    {
        Data::Tickets theater;
        QCOMPARE_EQ(theater.theaterId, 0);
        QCOMPARE_EQ(theater.movieId, 0);
        QCOMPARE_EQ(theater.rowCount, 0);
        QCOMPARE_EQ(theater.colCount, 0);
        QCOMPARE_EQ(theater.ticketsStatus.size(), 0);
    }

    // comparsion test
    comparsionTest(Data::Tickets { 1, 2 }, Data::Tickets { 2, 1 }, Data::Tickets { 1, 2 });
    comparsionTest(Data::Tickets { 2, 2 }, Data::Tickets { 2, 3 }, Data::Tickets { 2, 2 });
    comparsionTest(Data::Tickets { 2, 2 }, Data::Tickets { 3, 3 }, Data::Tickets { 2, 2 });
}

}
