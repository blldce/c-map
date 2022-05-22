

#ifndef MAP_H
#define MAP_H

struct map
{
    int size;                               // 4 bytes
    struct node(*head);                     // 8 bytes
    int (*add)(struct map(*), int, int);    // 8 bytes
    int (*remove_item)(struct map(*), int); // 8 bytes
    int (*get)(struct map(*), int);         // 8 bytes
};

struct node
{
    int key;                 // 4 bytes
    int value;               // 4 bytes
    struct node(*next_node); // 8 bytes
    struct node(*prev_node); // 8 bytes
};

// constructors
extern struct map init_map_stack(void);
extern struct map *init_map_heap(void);

// member funcs
extern int add(struct map(*), int, int);
extern int remove_item(struct map(*), int);
extern int get(struct map(*), int);

// internals
static int check_key(struct map(*),int);

#endif
