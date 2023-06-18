#include <iostream>
#include <sstream>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("init") {
    MagicalContainer container;
    CHECK_NOTHROW(container.addElement(15));
    CHECK_NOTHROW(container.removeElement(15));
    CHECK_THROWS(container.removeElement(15)); //remove throw

    container.addElement(24);
    container.addElement(1);
    container.addElement(9);
    CHECK_EQ(container.size(), 3);



    CHECK_NOTHROW(MagicalContainer::AscendingIterator ascIter(container));
    CHECK_NOTHROW(MagicalContainer::SideCrossIterator sidIter(container));
    CHECK_NOTHROW(MagicalContainer::PrimeIterator priIter(container));
}

TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(24);
    container.addElement(1);
    container.addElement(9);
    MagicalContainer::AscendingIterator ascIter(container); // 1 9 24

    auto it = ascIter.begin();
    CHECK_EQ(*it, 1);
    CHECK_NOTHROW(++it);
    CHECK_EQ(*it, 9);
    CHECK_NOTHROW(++it);
    CHECK_EQ(*it, 24);
    CHECK_THROWS(++it); //++ throw


    CHECK(*ascIter.begin() > *ascIter.end());
    CHECK_FALSE(*ascIter.begin() < *ascIter.end());
    CHECK(*ascIter.begin() != *ascIter.end());
//    container.addElement(1);
//    container.removeElement(24);
//    container.removeElement(9);
    CHECK_FALSE(*ascIter.begin() == *ascIter.end());
}

TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(24);
    container.addElement(1);
    container.addElement(9);
    MagicalContainer::SideCrossIterator sidIter(container); // 24 9 1

    auto it = sidIter.begin();
    CHECK_EQ(*it, 24);
    CHECK_NOTHROW(++it);
    CHECK_EQ(*it, 9);
    CHECK_NOTHROW(++it);
    CHECK_EQ(*it, 1);
    CHECK_THROWS(++it);//++ throw

    CHECK(*sidIter.begin() > *sidIter.end());
    CHECK_FALSE(*sidIter.begin() < *sidIter.end());
    CHECK(*sidIter.begin() != *sidIter.end());
//    container.addElement(1);
//    container.removeElement(24);
//    container.removeElement(9);
    CHECK_FALSE(*sidIter.begin() == *sidIter.end());
}

TEST_CASE("PrimeIterator") {
    MagicalContainer container;
    container.addElement(24);
    container.addElement(1);
    container.addElement(7);
    container.addElement(9);
    MagicalContainer::PrimeIterator primIter(container); // 1 7

    auto it = primIter.begin();
    CHECK_EQ(*it, 1);
    CHECK_NOTHROW(++it);
    CHECK_EQ(*it, 7);
    CHECK_THROWS(++it); //++ throw



    CHECK(*primIter.begin() > *primIter.end());
    CHECK_FALSE(*primIter.begin() < *primIter.end());
    CHECK(*primIter.begin() != *primIter.end());
//    container.addElement(1);
//    container.removeElement(24);
//    container.removeElement(9);
    CHECK_FALSE(*primIter.begin() == *primIter.end());
}

TEST_CASE("different containers") {
    MagicalContainer container1;
    MagicalContainer container2;

    //container1
    container1.addElement(1);
    container1.addElement(2);
    container1.addElement(3);
    //container2
    container2.addElement(11);
    container2.addElement(22);
    container2.addElement(33);

    SUBCASE("AscendingIterator")
    {
        MagicalContainer::AscendingIterator it1(container1);
        MagicalContainer::AscendingIterator it2(container2);

        CHECK_THROWS(it1 = it2);
    }
    SUBCASE("SideCrossIterator")
    {
        MagicalContainer::SideCrossIterator it1(container1);
        MagicalContainer::SideCrossIterator it2(container2);

        CHECK_THROWS(it1 = it2);
    }
    SUBCASE("AscendingIterator")
    {
        MagicalContainer::PrimeIterator it1(container1);
        MagicalContainer::PrimeIterator it2(container2);

        CHECK_THROWS(it1 = it2);
    }
}

