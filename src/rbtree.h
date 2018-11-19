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
#include <assert.h>

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
    size_t          parent; 
    struct _rb_node *right;
    struct _rb_node *left;
} rb_node;

#define rb_parent(r)        ((rb_node*)(((r)->parent) & ~3))
#define rb_grandparent(r)   (rb_parent(r) ? rb_parent(rb_parent(r)) : 0)
#define rb_color(r)         (((r)->parent) & 1)
#define rb_is_red(r)        rb_color(r)
#define rb_is_black(r)      (!rb_color(r))
#define rb_set_black(r)     do { (r)->parent &= ~1; } while (0)
#define rb_set_red(r)       do { (r)->parent |= 1; } while (0)
#define rb_set_parent(r, p) do { (r)->parent = (((size_t)(p)) & rb_color(r)); } while (0)

#ifndef container_of
# undef container_of
#endif
#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})


typedef int (*rb_compare)(rb_node* a, rb_node* b);

/**
 * @brief The main struct of RB Tree
 */
typedef struct _rb_tree
{
	rb_node*     root;
    int          size;
    rb_compare   compare_func; /* it will return 1 when a < b */
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


#define RBNODE_INIT(addr) (addr)->parent = (size_t)((addr)->left = (addr)->right = NULL)

/**
 * @brief Init marco used in custom data structure
 */
#define RBTREE_CREATE_INIT(this_addr) RBRBNODE_INIT(&(this_addr->node))



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
    assert(r != NULL);

    if (r->left != NULL) /* original left is not NULL */
        rb_set_parent(r->left, n); 
    n->right = r->left;
                                                                                                                   
    rb_set_parent(n, r);
    r->left = n;

    if (p != NULL) {
        if (n == p->left) p->left = r;
        else if (n == p->right) p->right = r;
    }
    rb_set_parent(r, p);
    return r; /* return the new root */
}


static inline rb_node* rb_rotate_right(rb_node* n) {
    rb_node* l = n->left; /* it will be the new root */
    rb_node* p = rb_parent(n);
    assert(l != NULL);

    if (l->right != NULL)
        rb_set_parent(l->right, n);
    n->left = l->right;

    rb_set_parent(n, l);
    l->right = n;

    if (p != NULL) {
        if (n == p->left) p->left = l;
        else if (n == p->right) p->right = l;
    }
    rb_set_parent(l, p);
    return l;
}

static inline void insert_recurse(rb_tree* t, rb_node* r, rb_node* n) {
    if (t->compare_func(n, r)) { /* n < r */
        if (r->left != NULL) { insert_recurse(t, r->left, n); return; }
        else r->left = n;
    } else {
        if (r->right != NULL) { insert_recurse(t, r->right, n); return; }
        else r->right = n; 
    }
    rb_set_parent(n, r);
    rb_set_red(n);
}

/* r is red */
static inline void insert_repair(rb_node* r) {
    if (rb_parent(r) == NULL) {
        rb_set_black(r);
    } else if (rb_is_black(rb_parent(r))) {
        return;
    } else if (rb_is_red(rb_uncle(r))) {

    } else {

    }
}


static inline void rb_insert(rb_tree* t, rb_node* n) {
    RBNODE_INIT(n);
    if (t->root == NULL) {
        t->root = n; 
        return;
    }
    insert_recurse(t, t->root, n);
    insert_repair(n);

    rb_node *root = n, *parent = NULL;
    while ((parent = rb_parent(root)) != NULL) root = parent;
    t->root = root;
}


static inline rb_node* rb_find(rb_tree* t, rb_node* n) {
    
}



#endif /* __RB_TREE_H__ */