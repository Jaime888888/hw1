#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

ULListStr::~ULListStr() {
    clear();
}

size_t ULListStr::size() const {
    return size_;
}

bool ULListStr::empty() const {
    return size_ == 0;
}

void ULListStr::push_back(const std::string& val) {
    if (tail_ == nullptr) {
        tail_ = new Item();
        head_ = tail_;
    }

    if (tail_->last == ARRSIZE) {
        Item* newNode = new Item();
        newNode->prev = tail_;
        tail_->next = newNode;
        tail_ = newNode;
    }

    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
}
void ULListStr::set(size_t loc, const std::string& val)
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == nullptr) {
        throw std::invalid_argument("Bad location");
    }
    *ptr = val; // Update the value at the location
}

void ULListStr::pop_back() {
    if (tail_ == nullptr) return;

    tail_->last--;
    size_--;

    if (tail_->first == tail_->last) {
        Item* temp = tail_;
        tail_ = tail_->prev;

        if (tail_) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete temp;
    }
}

void ULListStr::push_front(const std::string& val) {
    if (head_ == nullptr) {
        head_ = new Item();
        tail_ = head_;
        head_->first = ARRSIZE;
        head_->last = ARRSIZE;
    }

    if (head_->first == 0) {
        Item* newNode = new Item();
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
        head_->first = ARRSIZE;
        head_->last = ARRSIZE;
    }

    head_->first--;
    head_->val[head_->first] = val;
    size_++;
}

void ULListStr::pop_front() {
    if (head_ == nullptr) return;

    head_->first++;
    size_--;

    if (head_->first == head_->last) {
        Item* temp = head_;
        head_ = head_->next;

        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete temp;
    }
}

std::string const & ULListStr::back() const {
    if (tail_ == nullptr) throw std::runtime_error("List is empty");
    return tail_->val[tail_->last - 1];
}
std::string& ULListStr::get(size_t loc)
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == nullptr) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
    std::string* ptr = getValAtLoc(loc);
    if (ptr == nullptr) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

std::string const & ULListStr::front() const {
    if (head_ == nullptr) throw std::runtime_error("List is empty");
    return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
    if (loc >= size_) return nullptr;

    Item* current = head_;
    size_t index = 0;

    while (current) {
        size_t numElements = current->last - current->first;

        if (loc < index + numElements) {
            return &current->val[current->first + (loc - index)];
        }

        index += numElements;
        current = current->next;
    }
    return nullptr;
}

void ULListStr::clear() {
    while (head_ != nullptr) {
        Item *temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = nullptr;
    size_ = 0;
}
