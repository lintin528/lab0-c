#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new_queue = malloc(sizeof(struct list_head));
    if (new_queue == NULL)
        return NULL;
    INIT_LIST_HEAD(new_queue);
    return new_queue;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (head == NULL)
        return;
    struct list_head *node;
    struct list_head *safe;

    list_for_each_safe (node, safe, head) {
        element_t *next_elem = list_entry(node, element_t, list);
        q_release_element(next_elem);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (head == NULL || s == NULL) {
        return 0;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (new_element == NULL)
        return 0;
    char *new_value = strdup(s);
    if (new_value == NULL) {
        free(new_element);
        return 0;
    }
    list_add(&new_element->list, head);
    new_element->value = new_value;

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (head == NULL || s == NULL) {
        return 0;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (new_element == NULL)
        return 0;
    char *new_value = strdup(s);
    if (new_value == NULL) {
        free(new_element);
        return 0;
    }
    list_add_tail(&new_element->list, head);
    new_element->value = new_value;

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL)
        return NULL;
    element_t *removed = list_first_entry(head, element_t, list);

    if (sp) {
        memcpy(sp, removed->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    list_del(&removed->list);
    return removed;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL)
        return NULL;
    element_t *removed = list_last_entry(head, element_t, list);

    if (sp) {
        memcpy(sp, removed->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    list_del(&removed->list);
    return removed;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (head == NULL || head->next == head)
        return 0;
    struct list_head *node;
    int count = 0;
    list_for_each (node, head) {
        count++;
    }
    return count;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    int size = q_size(head);
    int count = 0;
    struct list_head *mid = head->next;
    size /= 2;
    while (count <= size - 1) {
        mid = mid->next;
        count++;
    }
    element_t *mid_element = list_entry(mid, element_t, list);
    list_del(mid);
    q_release_element(mid_element);
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (head == NULL || head->next == head)
        return false;
    struct list_head *node;
    struct list_head *safe;
    element_t *node_e;
    element_t *safe_e;
    bool dup_flag = false;
    list_for_each_safe (node, safe, head) {
        while (safe != head) {
            node_e = list_entry(node, element_t, list);
            safe_e = list_entry(safe, element_t, list);
            safe = safe->next;
            if (strcmp(node_e->value, safe_e->value) == 0) {
                list_del(safe->prev);
                q_release_element(safe_e);
                dup_flag = true;
            } else {
                break;
            }
        }
        safe = node->next;
        if (dup_flag) {
            list_del(node);
            q_release_element(node_e);
            dup_flag = false;
        }
    }

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (head == NULL || head->next == head)
        return;
    struct list_head *odd = head->next;
    struct list_head *even = odd->next;
    while (even != head && odd != head) {
        odd->next = even->next;
        even->prev = odd->prev;
        even->next = odd;
        odd->prev = even;
        even->prev->next = even;
        odd->next->prev = odd;

        odd = odd->next;
        even = odd->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (head == NULL || head->next == head)
        return;
    struct list_head *current = head->next;
    while (current != head) {
        struct list_head *tmp;
        tmp = current;
        current = current->next;
        list_move(tmp, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
