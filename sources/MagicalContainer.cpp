//
// Created by Segev on 24/05/2023.
//

#include "MagicalContainer.hpp"

MagicalContainer::MagicalContainer() {
}

MagicalContainer::MagicalContainer(MagicalContainer &other) {
    dArray = other.dArray;
}

MagicalContainer::~MagicalContainer() {}

MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    if (this == &other) {
        return *this;
    }
    dArray = other.dArray; //copy
    return *this;
}

void MagicalContainer::addElement(int element) {
    dArray.push_back(element);
    sort(dArray.begin(), dArray.end());
}

void MagicalContainer::removeElement(int element) {
    auto x = std::find(dArray.begin(), dArray.end(), element);
    if (x != dArray.end()) {
        dArray.erase(x);
    }
    else {
        throw std::invalid_argument("Element not found");
    }
}

int MagicalContainer::size() const {
    return dArray.size();
}

//AscendingIterator

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
    if (this != &other) {
//        cont = other.cont;
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
    ++curr;
    return *this;
}


//SideCrossIterator

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont, int forward, int backward)
        : cont(cont), forward(forward), backward(backward) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : cont(other.cont), forward(other.forward), backward(other.backward) {}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(cont, 0, cont.size());
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    int s = cont.size() / 2;
    if (cont.size() % 2 == 0) {
        return SideCrossIterator(cont, cont.size(), 0);
    }
    return SideCrossIterator(cont, s, s);
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (this != &other) {
//        cont = other.cont;
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
    return forward > other.forward && backward > other.backward;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return forward < other.forward && backward < other.backward;
}

int MagicalContainer::SideCrossIterator::operator*() {
    if (isForward) {
        isForward = false;
        return cont.dArray[(std::vector<int>::size_type) forward];
    }
    isForward = true;
    return cont.dArray[(std::vector<int>::size_type) backward];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (isForward)
        ++forward;
    else
        --backward;
    return *this;
}



//PrimeIterator

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &cont, int curr)
        : cont(cont), curr(curr) {
    while (this->curr < this->cont.size()) {
        if (isPrime(this->cont.dArray[(std::vector<int>::size_type) this->curr])) {
            break;
        }
        ++this->curr;
    }
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : cont(other.cont), curr(other.curr) {}


bool MagicalContainer::PrimeIterator::isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(cont, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(cont, cont.size());
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (this != &other) {
//        cont = other.cont;
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
    return cont.dArray[(std::vector<int>::size_type) curr];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    ++curr;
    while (curr < cont.size()) {
        if (isPrime(cont.dArray[(std::vector<int>::size_type) curr])) {
            break;
        }
        ++curr;
    }
    return *this;
}

