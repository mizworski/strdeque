
#include <string>
#include <deque>
#include <queue>
#include <map>
#include <cstddef> //todo is it required for size_t to not throw error?
#include <iostream>

#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
static const bool debug() {
  return false;
}
#else
static const bool debug() {
  return true;
}
#endif

typedef std::deque<std::string> strdeque;
typedef std::map<unsigned long, strdeque> strdeques;
typedef std::queue<unsigned long> lld_queue;

static strdeques &deques() {
    static strdeques deques;
    return deques;
}

unsigned long current_index = 0;
lld_queue free_indices;

static std::ostream& write_to_cerr() {
  static std::ios_base::Init init;
  return std::cerr;
}

static void write_error(std::string message) {
  if (debug()) {
    write_to_cerr() << message << "\n";
  }
}

static std::string id_string(unsigned long id) {
  if (id == emptystrdeque()) {
    return "the Empty Deque";
  } else {
    return std::to_string(id);
  }
}

unsigned long strdeque_new() {
    write_error("strdeque_new()");
    unsigned long index;
    strdeque deque;

    if (free_indices.empty()) {
        index = current_index++;
        deques().insert(std::pair<unsigned long, strdeque>(index, deque));
    } else {
        index = free_indices.front();
        free_indices.pop();
        deques().insert(std::pair<unsigned long, strdeque>(index, deque));
    }

    write_error("strdeque_new: deque " + std::to_string(index) + " created");

    return index;
}

void strdeque_delete(unsigned long id) {
    write_error("strdeque_delete(" + id_string(id) + ")");

    if (id == emptystrdeque()) {
        write_error("strdeque_delete: attempt to remove " + id_string(id));
    } else {
        unsigned long elements_erased = deques().erase(id);
        if (elements_erased > 0) {
            free_indices.push(id);
        }
        write_error("strdeque_delete: deque " + id_string(id) + " deleted");
    }
}

size_t strdeque_size(unsigned long id) {
    write_error("strdeque_size(" + id_string(id) + ")");
    size_t ret_val = 0;
    strdeques::iterator it = deques().find(id);

    if (it != deques().end()) {
        ret_val = it->second.size();
        write_error("strdeque_size: deque " + id_string(id) +
          " contains " + std::to_string(ret_val) + " elements");
    } else {
        write_error("strdeque_size: deque " + id_string(id) + " does not exist");
    }

    return ret_val;
}

void strdeque_insert_at(unsigned long id, size_t pos, const char *value) {
    write_error("strdeque_insert_at("+ id_string(id) + ", "
      + std::to_string((int) pos) + ", \"" + ((value != nullptr) ? value : "NULL")
      + "\")");

    if (value != nullptr) {
        std::string str(value);
        strdeques::iterator it = deques().find(id);

        if (it != deques().end()) {
            strdeque &deque = it->second;
            if (it->first == emptystrdeque()) {
                write_error("strdeque_insert_at: attempt to insert into the Empty Deque");
            } else if (pos < deque.size()) { //todo deque.size() is unsigned long
                deque.insert(deque.begin() + pos, str); //todo to check
                write_error("strdeque_insert_at: deque " + id_string(id) +
                  " element \"" + value + "\" inserted at "+ std::to_string((int) pos));
            } else {
                deque.push_back(str);
                write_error("strdeque_insert_at: deque " + id_string(id) +
                  " element \"" + value + "\" inserted at "+ std::to_string((int) pos));
            }
        } else {
            write_error("strdeque_insert_at: deque " + id_string(id)
              + " does not exist");
        }
    } else {
      write_error("strdeque_insert_at: attempt to insert NULL into a deque");
    }
}

void strdeque_remove_at(unsigned long id, size_t pos) {
    write_error("strdeque_remove_at(" + id_string(id) + ", "
      + std::to_string((int) pos) + ")");

    strdeques::iterator it = deques().find(id);

    if (it != deques().end()) {
        strdeque &deque = it->second;
        if (it->first == emptystrdeque()) {
            write_error("strdeque_remove_at: attempt to remove from the Empty Deque");
        } else if (pos < deque.size()) {
            deque.erase(deque.begin() + pos);

            write_error("strdeque_remove_at: deque " + id_string(id) +
              " element at "+ std::to_string((int) pos) + " removed");
        } else {
            write_error("strdeque_remove_at: deque " + id_string(id) +
              " does not contain an element at " + std::to_string((int) pos));
        }
    } else {
      write_error("strdeque_remove_at: deque " + id_string(id)
        + " does not exist");
    }
}

const char *strdeque_get_at(unsigned long id, size_t pos) {
    write_error("strdeque_get_at(" + id_string(id) + ", "
      + std::to_string((int) pos) + ")");

    const char *ret_val = nullptr;
    strdeques::iterator it = deques().find(id);

    if (it != deques().end()) {
        strdeque deque = it->second;
        if (pos < deque.size()) {
            ret_val = deque.at(pos).c_str();

            write_error("strdeque_get_at: deque " + id_string(id)
              + ", element at " + std::to_string((int) pos) + " is \""
              + ((ret_val != nullptr) ? ret_val : "NULL") + "\"");
        } else {
            write_error("strdeque_get_at: deque " + id_string(id)
              + " does not contain an element at " + std::to_string((int) pos));
        }
    } else {
      write_error("strdeque_get_at: deque " + id_string(id)
        + " does not exist");
    }

    return ret_val;
}

void strdeque_clear(unsigned long id) {
    write_error("strdeque_clear(" + id_string(id) + ")");

    strdeques::iterator it = deques().find(id);

    if (it != deques().end()) {
        if (it->first == emptystrdeque()) {
            write_error("strdeque_clear: attempt to clear the Empty Deque");
        } else {
            it->second.clear();
            write_error("strdeque_clear: deque " + id_string(id)
              + " has been cleared");
        }
    }
}

int strdeque_comp(unsigned long id1, unsigned long id2) {
    write_error("strdeque_comp(" + id_string(id1) + ", " + id_string(id2) + ")");

    const int lesser = -1;
    const int equal = 0;
    const int greater = 1;
    int result;

    strdeques::iterator dequeues_it1 = deques().find(id1);
    strdeques::iterator dequeues_it2 = deques().find(id2);

    strdeque deque1;
    strdeque deque2;

    if (dequeues_it1 != deques().end()) {
        deque1 = dequeues_it1->second;
    } else {
        write_error("strdeque_comp: deque " + id_string(id1) + " does not exist");
    }
    if (dequeues_it2 != deques().end()) {
        deque2 = dequeues_it2->second;
    } else {
        write_error("strdeque_comp: deque " + id_string(id2) + " does not exist");
    }

    if (dequeues_it1 == deques().end() && dequeues_it2 == deques().end()) {
        return equal;
    } else if (dequeues_it1 == deques().end() && dequeues_it2 != deques().end() && id2 != emptystrdeque()) {
        return lesser;
    } else if (dequeues_it1 != deques().end() && dequeues_it2 == deques().end() && id1 != emptystrdeque()) {
        return greater;
    }

    // both deques() exist.

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
        result = equal;
    } else if (it1 == deque1.end()) {
        result = lesser;
    } else {
        result = greater;
    }

    write_error("strdeque_comp: result of comparing " + id_string(id1)
      + "to" + id_string(id2) + "is " + std::to_string(result));

    return result;
}
