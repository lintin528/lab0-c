#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

#define SAMPLES 1000

void q_create_runs(struct list_head *head)
{
    if (head == NULL || head->next == head)
        return;
    struct list_head *first;
    struct list_head *safe;
    bool flag = false;
    list_for_each_safe (first, safe, head) {
        int count = 0;
        while (count < rand() % 3 + 3 - 1 && safe != head) {
            safe = safe->next;
            if (flag)
                list_move(safe->prev, first->prev);
            first = first->prev;
            count++;
        }
        flag = !flag;
    }
}

// static void shaffle_partially(struct list_head *head)
// {
//     int offset = 0;
//     int limit;
//     struct list_head *tail = head->prev;
//     struct list_head *current = tail;
//     struct list_head *tmp;
//     while(current != head && current->prev != head) {
//         limit = rand() % 3 + 3;
//         offset = 0;
//         while (offset <= limit) {
//             if(current->prev == head) {
//                 break;
//             }
//             current = current->prev;
//             offset++;
//         }
//         tmp = current->prev;
//         list_move(current, tail);
//         list_move(tail, tmp);
//         current = tail;
//     }
// }

static void create_sample(struct list_head *head, element_t *space, int samples)
{
    printf("Creating sample\n");
    for (int i = 0; i < samples; i++) {
        element_t *elem = space + i;
        char v = (char) i;
        elem->value = &v;
        list_add_tail(&elem->list, head);
    }
}

int main(void)
{
    struct list_head sample_head;
    int nums = SAMPLES;

    /* Assume ASLR */
    srand((uintptr_t) &main);

    INIT_LIST_HEAD(&sample_head);

    element_t *samples = malloc(sizeof(*samples) * SAMPLES);

    create_sample(&sample_head, samples, nums);
    q_create_runs(&sample_head);

    q_sort(&sample_head, false);

    return 0;
}