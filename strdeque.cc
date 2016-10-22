//
// Created by michal on 10/22/16.
//

#include <deque>
#include <queue>
#include <map>
#include "strdeque.h"

typedef std::deque<std::string> strdeque;
typedef std::map<unsigned long, strdeque> strdeques;
//typedef std::pair<unsigned long, strdeque> map_entity;
typedef std::queue<unsigned long> lld_queue;

strdeques queues;
unsigned long current_index = 0;
lld_queue free_indicies;

unsigned long strdeque_new() {
    unsigned long index;
    strdeque queue;

    if (free_indicies.empty()) {
        index = current_index++;
        queues.insert(std::pair<unsigned long, strdeque>(index, queue));
    } else {
        index = free_indicies.front();
        free_indicies.pop();
        queues.insert(std::pair<unsigned long, strdeque>(index, queue));
    }

    return index;
}

int main() {
    std::string s;
    std::deque<std::string> q (4, "dupa");

    size_t size = q.size();
    long x = strdeque_new();
}
