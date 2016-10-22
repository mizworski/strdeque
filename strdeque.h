#ifndef ZADANIE2_STRDEQUE_H
#define ZADANIE2_STRDEQUE_H

//todo z tym ifdefem czy extern przy kazdej?
//todo https://isocpp.org/wiki/faq/mixing-c-and-cpp#include-c-hdrs-personal

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates new, empty, double-ended queue of strings.
 * @return identifier of queue.
 */
unsigned long strdeque_new();

/**
 * Removes queue with specified id if such exists.
 * @param id identifier of queue
 */
void strdeque_delete(unsigned long id);

/**
 * Quantity of elements in queue with specified id.
 * @param id identifier of queue
 * @return size of queue if such exists, otherwise zero.
 */
size_t strdeque_size(unsigned long id);

/**
 * Inserts element in front of specified element into specified queue
 * if element is not null and such queue exists.
 * If there is no element at specified position,
 * inserts element in the end of the queue.
 * @param id identifier of queue
 * @param pos position in front of which element is being inserted
 * @param value element that is being inserted
 */
void strdeque_insert_at(unsigned long id, size_t pos, const char* value);

/**
 * Removes element at specified position from the queue
 * if such element and queue exist.
 * @param id identifier of queue
 * @param pos position of element that is being deleted
 */
void strdeque_remove_at(unsigned long id, size_t pos);

/**
 * Gets an element from the queue at specified position.
 * @param id identifier of queue
 * @param pos position of element that is being get. //todo is it gramatically correct?
 * @return pointer to element if queue exists and pos is not out of bounds.
 * Otherwise returns null
 */
const char* strdeque_get_at(unsigned long id, size_t pos);

/**
 * Removes all elements from specified queue if such exists.
 * @param id identifier of queue
 */
void strdeque_clear(unsigned long id);

/**
 * Compares two queues using lexicographical order.
 * If queue with specified identifier doesn't exist then
 * it's being treated as an empty queue.
 * @param id1 identifier of first queue
 * @param id2 identifier of second queue
 * @return
 * -1 if first queue is lesser,
 * 0 if queues are equal,
 * 1 otherwiste.
 */
int strdeque_comp(unsigned long id1, unsigned long id2);


#ifdef __cplusplus
}
#endif

#endif //ZADANIE2_STRDEQUE_H
