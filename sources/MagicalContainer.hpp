//
// Created by Segev on 24/05/2023.
//

#ifndef MAGICAL_ITERATORS_A_MAGICALCONTAINER_H
#define MAGICAL_ITERATORS_A_MAGICALCONTAINER_H

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace ariel {}
using namespace std;


class MagicalContainer {
private:
    std::vector<int> dArray;
    std::vector<int*> primes;

public:
    MagicalContainer(); //default
    MagicalContainer(MagicalContainer &other); // copy
    ~MagicalContainer(); //destructor
    MagicalContainer(MagicalContainer&& other) noexcept; // Move constructor
    MagicalContainer &operator=(MagicalContainer&& other) noexcept; // Move assignment operator

    MagicalContainer &operator=(const MagicalContainer &other);

    void addElement(int element);

    void removeElement(int element);

    int size() const;

    bool isPrime(int num);
    void updatePrimes();

    //AscendingIterator
    class AscendingIterator {
    private:
        const MagicalContainer &cont;
        int curr;

    public:
        AscendingIterator(const MagicalContainer &cont, int curr = 0);
        AscendingIterator(const AscendingIterator &other);
        ~AscendingIterator() {}
        AscendingIterator(AscendingIterator&& other) noexcept; // Move constructor
        AscendingIterator& operator=(AscendingIterator&& other) noexcept; // Move assignment operator




        AscendingIterator begin() const;
        AscendingIterator end() const;


        AscendingIterator &operator=(const AscendingIterator &other);
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        int operator*() const;
        AscendingIterator &operator++();



    };

    //SideCrossIterator
    class SideCrossIterator {
    private:
        const MagicalContainer &cont;
        int forward;
        int backward;
        bool isForward = true;

    public:
        SideCrossIterator(const MagicalContainer &cont, int forward = 0, int backward = -1);
        SideCrossIterator(const SideCrossIterator &other);
        ~SideCrossIterator() {}
        SideCrossIterator(SideCrossIterator&& other) noexcept; // Move constructor
        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept; // Move assignment operator

        SideCrossIterator begin() const;
        SideCrossIterator end() const;

        SideCrossIterator &operator=(const SideCrossIterator &other);
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;
        int operator*();
        SideCrossIterator &operator++();
    };

    //PrimeIterator
    class PrimeIterator {
    private:
        const MagicalContainer &cont;
        int curr;
        vector<const int*> primes;

    public:
        PrimeIterator(const MagicalContainer &cont, int curr = 0);
        PrimeIterator(const PrimeIterator &other);
        ~PrimeIterator() {}
        PrimeIterator(PrimeIterator&& other) noexcept; // Move constructor
        PrimeIterator& operator=(PrimeIterator&& other) noexcept; // Move assignment operator

        PrimeIterator begin() const;
        PrimeIterator end() const;

        PrimeIterator &operator=(const PrimeIterator &other);
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        int operator*() const;
        PrimeIterator &operator++();
    };
};



#endif //MAGICAL_ITERATORS_A_MAGICALCONTAINER_H



