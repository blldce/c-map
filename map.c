


#include <stdio.h>
#include <stdlib.h>
#include "map.h"

struct map init_map_stack(void)
{
    struct map my_map = {.size = 0, .head = (void(*))0, .add = add, .get = get, .remove_item = remove_item};
    return my_map;
}

struct map *init_map_heap(void)
{
    struct map(*my_map) = (struct map(*))malloc(sizeof(struct map));
    my_map->size = 0;
    my_map->head = (void(*))0;
    my_map->add = add;
    my_map->get = get;
    my_map->remove_item = remove_item;
    return my_map;
}

int add(struct map(*map_ptr), int key, int value)
{
    struct node(*new_node_ptr);

    if (map_ptr->head == (void(*))0) // first time?
    {
        // we do not need to check key, its first addition anyway
        new_node_ptr = (struct node(*))malloc(sizeof(struct node));
        new_node_ptr->next_node = (void *)0;
        new_node_ptr->prev_node = (void *)0;
        new_node_ptr->key = key;
        new_node_ptr->value = value;
        map_ptr->head = new_node_ptr;
    }
    else // nope
    {
        if (check_key(map_ptr, key)) // check key is exist
            return 0;
        new_node_ptr = (struct node(*))malloc(sizeof(struct node));
        new_node_ptr->key = key;
        new_node_ptr->value = value;
        map_ptr->head->next_node = new_node_ptr;
        new_node_ptr->next_node = (void(*))0;
        new_node_ptr->prev_node = map_ptr->head;
        map_ptr->head = new_node_ptr;
    }
    map_ptr->size++;
    return 1;
}

int remove_item(struct map(*map_ptr), int key)
{
    if (!check_key(map_ptr, key))
        return 0;

    struct node(*iter) = map_ptr->head;
    while (iter != (void(*))0)
    {
        if (iter->key == key)
        {
            struct node(*curr_next_node) = iter->next_node;
            struct node(*curr_previous_node) = iter->prev_node;
            if (curr_next_node != (void(*))0)
                curr_next_node->prev_node = curr_previous_node;
            if (curr_previous_node != (void(*))0)
                curr_previous_node->next_node = curr_next_node;
            free(iter);
            map_ptr->size--;
            return 1;
        }
        iter = iter->prev_node;
    }

    return 0;
}

int get(struct map(*map_ptr), int key)
{
    struct node(*iter) = map_ptr->head;
    while (iter != (void(*))0)
    {
        if (iter->key == key)
            return iter->value; // ret value
        iter = iter->prev_node;
    }
    return 0; // false
}

static int check_key(struct map(*map_ptr), int key)
{
    struct node(*iter) = map_ptr->head;
    while (iter != (void(*))0)
    {
        if (iter->key == key)
            return 1; // true
        iter = iter->prev_node;
    }
    return 0; // false
}

static void print_items(struct map(*map_ptr))
{
    printf("**********************\n");
    struct node(*iter) = map_ptr->head;
    while (iter != (void(*))0)
    {
        printf("Address : %p -- Key : %d -- Value :%d  -- previous node : %p -- next node : %p \n ", iter, iter->key, iter->value, iter->prev_node, iter->next_node);
        iter = iter->prev_node;
    }
}
