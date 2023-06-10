//
// Created by Segev on 24/05/2023.
//

#include "MagicalContainer.hpp"

MagicalContainer::MagicalContainer() {
}

MagicalContainer::MagicalContainer(MagicalContainer &other) {
    dArray = other.dArray;
    primes = other.primes;
}

MagicalContainer::~MagicalContainer() {}



MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    if (this == &other) {
        return *this;
    }
    dArray = other.dArray; //copy
    primes = other.primes;
    return *this;
}

void MagicalContainer::addElement(int element) {
    dArray.push_back(element);
    sort(dArray.begin(), dArray.end());
    updatePrimes();
}

void MagicalContainer::removeElement(int element) {
    auto x = std::find(dArray.begin(), dArray.end(), element);
    if (x != dArray.end()) {
        dArray.erase(x);
    }
    else {
        throw runtime_error("Element not found");
    }
    updatePrimes();
}

int MagicalContainer::size() const {
    return dArray.size();
}

bool MagicalContainer::isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}


void MagicalContainer::updatePrimes() {
    primes.clear();
    for (int& num : dArray) {
        if (isPrime(num)) {
            primes.push_back(&num);
        }
    }
}

//---------------------------AscendingIterator-----------------------------------

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &cont, int curr)
        : cont(cont), curr(curr) {
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : cont(other.cont), curr(other.curr) {}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return MagicalContainer::AscendingIterator(cont, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    return AscendingIterator(cont, cont.size());
}
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
    if (&this->cont != &other.cont)
        throw runtime_error("Not the same container");
    if (this != &other) {
        curr = other.curr;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    return curr == other.curr;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    return curr > other.curr;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    return curr < other.curr;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return cont.dArray[(std::vector<int>::size_type) curr];
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (*this == end())
        throw runtime_error("You are at the end");
    ++curr;
    return *this;
}


//----------------------------------SideCrossIterator----------------------------------

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont, int forward, int backward)
        : cont(cont), forward(forward), backward(backward) {
    if (backward == -1)
        this->backward = cont.size()-1;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : cont(other.cont), forward(other.forward), backward(other.backward) {}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(cont, 0, cont.size()-1);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    int s = cont.size() / 2;
    if (cont.size() % 2 == 0) {
        return SideCrossIterator(cont, s, s-1);
    }
    return SideCrossIterator(cont, s+1, s);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (&this->cont != &other.cont)
        throw runtime_error("Not the same container");
    if (this != &other) {
        forward = other.forward;
        backward = other.backward;
        isForward = other.isForward;
    }
    return *this;
}


bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return forward == other.forward && backward == other.backward;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    if (isForward && other.isForward) {
        return forward > other.forward;
    }
    else if (isForward && !other.isForward) {
        return forward > other.backward;
    }
    else if (!isForward && other.isForward) {
        return backward > other.isForward;
    }
    return backward > other.backward;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    if (isForward && other.isForward) {
        return forward < other.forward;
    }
    else if (isForward && !other.isForward) {
        return forward < other.backward;
    }
    else if (!isForward && other.isForward) {
        return backward < other.isForward;
    }
    return backward < other.backward;
}

int MagicalContainer::SideCrossIterator::operator*() {
    if (isForward) {
        return cont.dArray[(std::vector<int>::size_type) forward];
    }
    return cont.dArray[(std::vector<int>::size_type) backward];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (*this == end())
        throw runtime_error("You are at the end");
    if (isForward) {
        ++forward;
        isForward = false;
    }
    else {
        --backward;
        isForward = true;
    }
    return *this;
}



//------------------------------PrimeIterator--------------------------------

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &cont, int curr)
        : cont(cont), curr(curr) {
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : cont(other.cont), curr(other.curr) {}



MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(cont, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(cont, cont.primes.size());
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (&this->cont != &other.cont)
        throw runtime_error("Not the same container");
    if (this != &other) {
        curr = other.curr;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    return curr == other.curr;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    return curr > other.curr;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    return curr < other.curr;
}

int MagicalContainer::PrimeIterator::operator*() const {
    return *cont.primes[(std::vector<int>::size_type)curr];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (*this == end())
        throw runtime_error("You are at the end");
    ++curr;
    return *this;
}


