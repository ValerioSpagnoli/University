#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct tree tree;

tree * build_tree_1();
tree * build_tree_2();
tree * build_tree_3();
void tree_delete(tree * t);

int tree_is_bst(tree * t);
int tree_is_balanced(tree * t);
int tree_is_avl(tree * t);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

