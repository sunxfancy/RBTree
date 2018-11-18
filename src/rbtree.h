/**
 * @Author: Xiaofan Sun
 * @Date: 17 Nov 2018
 * 
 * This is a red-black tree which is designed as a common data structure with good scaliablity.
 * It refers to the implementation of RBTree in the Linux kernel.
 */

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <stdlib.h>

#ifndef MALLOC
#define MALLOC(type, obj) type* obj = (type*)malloc(sizeof(type))
#endif

#define RB_RED   1
#define RB_BLACK 0

/**
 * RB Node 
 * the last bit in parent pointer is used as color 
 */
typedef struct _rb_node
{
    struct _rb_node *parent; 
    struct _rb_node *right;
    struct _rb_node *left;
} rb_node;

#define rb_parent(r)    ((rb_node*)(((size_t)((r)->parent)) & ~3))
#define rb_grandparent(r)  (rb_parent(r) ? rb_parent(rb_parent(r)) : 0)
#define rb_color(r)     ((int)((r)->parent & 1))
#define rb_is_red(r)    rb_color(r)
#define rb_is_black(r)  (!rb_color(r))
#define rb_set_red(r)   do { (r)->parent &= ~1; } while (0)
#define rb_set_black(r) do { (r)->parent |= 1; } while (0)

#ifndef container_of
# undef container_of
#endif
#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * @brief The main struct of RB Tree
 */
typedef struct _rb_tree
{
	rb_node* root;
    int      size;
} rb_tree;

/**
 * @brief This macro is used to define custom data structure 
 * @details 
 * 	 RBTREE_DEF(test_list)
 * 	   int a;
 * 	   float b;
 * 	   ...
 * 	 RBTREE_DEF_END(test_list)
 */
#define RBTREE_DEF(type_name) typedef struct _##type_name \
	{	rb_node node;

#define RBTREE_DEF_END(type_name) } type_name;


#define RBTREE_INIT(addr) (addr)->parent = (addr)->left = (addr)->right = NULL

/**
 * @brief Init marco used in custom data structure
 */
#define RBTREE_CREATE_INIT(this_addr) RBTREE_INIT(&(this_addr->node))



static inline rb_tree* rb_create_tree() {
    MALLOC(rb_tree, n);
    n->root = NULL;
    n->size = 0;
    return n;
}


static inline int rb_is_empty(const rb_tree* r) {
    return r->root == NULL;
}



static inline rb_node* rb_sibling(const rb_node* n) {
    rb_node* p = rb_parent(n);
    if (n == p->left) return p->right;
    else return p->left; /** it could be NULL */
}


static inline rb_node* rb_uncle(const rb_node* n) {
    rb_node* p = rb_parent(n);
    rb_node* g = rb_parent(p);
    if (g == NULL) return NULL;
    return rb_sibling(p);
}


static inline rb_node* rb_rotate_left(rb_node* n) {
    rb_node* r = n->right; /* it will be the new root */
    rb_node* p = rb_parent(n);
    return r; /* return the new root */
}

#endif /* __RB_TREE_H__ */