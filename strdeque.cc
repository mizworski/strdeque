#include <deque>
#include <queue>
#include <map>
#include <cstddef> //todo is it required for size_t to not throw error?

#include "strdeque.h"
#include "strdequeconst.h"

typedef std::deque<std::string> strdeque;
typedef std::map<unsigned long, strdeque> strdeques;
//typedef std::pair<unsigned long, strdeque> map_entity;
typedef std::queue<unsigned long> lld_queue;

unsigned long current_index = 0;
strdeques deques;
lld_queue free_indices;

unsigned long strdeque_new() {
    unsigned long index;
    strdeque deque;

    if (free_indices.empty()) {
        index = current_index++;
        deques.insert(std::pair<unsigned long, strdeque>(index, deque));
    } else {
        index = free_indices.front();
        free_indices.pop();
        deques.insert(std::pair<unsigned long, strdeque>(index, deque));
    }

    return index;
}

void strdeque_delete(unsigned long id) {
    if (id == emptystrdeque()) {
        // todo print error
    } else {
        unsigned long elements_erased = strdeques().erase(id);

        if (elements_erased > 0) {
            free_indices.push(id);
        }
    }
}

size_t strdeque_size(unsigned long id) {
    size_t ret_val = 0;
    strdeques::iterator it = deques.find(id);

    if (it != deques.end()) {
        ret_val = it->second.size();
    }

    return ret_val;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char *value) {
    if (value != nullptr) {
        strdeques::iterator it = deques.find(id);

        if (it != deques.end()) {
            strdeque deque = it->second;
            if (it->first == emptystrdeque()) {
                // todo print error
            } else if (pos < deque.size()) { //todo deque.size() is unsigned long
                deque.insert(deque.begin() + pos, value); //todo to check
            } else {
                deque.push_back(value);
            }
        }
    }
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    strdeques::iterator it = deques.find(id);

    if (it != deques.end()) {
        strdeque deque = it->second;
        if (it->first == emptystrdeque()) {
            // todo print error
        } else if (pos < deque.size()) {
            deque.erase(deque.begin() + pos);
        }
    }
}

const char *strdeque_get_at(unsigned long id, size_t pos) {
    const char *ret_val = nullptr;
    strdeques::iterator it = deques.find(id);

    if (it != deques.end()) {
        strdeque deque = it->second;
        if (pos < deque.size()) {
            ret_val = deque.at(pos).c_str();
        }
    }

    return ret_val;
}

void strdeque_clear(unsigned long id) {
    strdeques::iterator it = deques.find(id);

    if (it != deques.end()) {
        if (it->first == emptystrdeque()) {
            // todo print error
        } else {
            it->second.clear();
        }
    }
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    const int lesser = -1;
    const int equal = 0;
    const int greater = 1;

    strdeques::iterator dequeues_it1 = deques.find(id1);
    strdeques::iterator dequeues_it2 = deques.find(id2);

    strdeque deque1;
    strdeque deque2;

    if (dequeues_it1 != deques.end()) {
        deque1 = dequeues_it1->second;
    }
    if (dequeues_it2 != deques.end()) {
        deque2 = dequeues_it2->second;
    }

    if (dequeues_it1 == deques.end() && dequeues_it2 == deques.end()) {
        return equal;
    } else if (dequeues_it1 == deques.end() && dequeues_it2 != deques.end()) {
        return lesser;
    } else if (dequeues_it1 != deques.end() && dequeues_it2 == deques.end()) {
        return greater;
    }

    // both deques exist.

    strdeque::iterator it1 = deque1.begin();
    strdeque::iterator it2 = deque2.begin();

    while (it1 != deque1.end() && it2 != deque2.end()) {
        std::string str1 = (*it1);
        std::string str2 = (*it2);
        int result = str1.compare(str2);

        if (result < 0) {
            return lesser;
        } else if (result > 0) {
            return greater;
        } else {
            ++it1;
            ++it2;
        }
    }

    if (it1 == deque1.end() && it2 == deque2.end()) {
        return equal;
    } else if (it1 == deque1.end()) {
        return lesser;
    } else {
        return greater;
    }
}