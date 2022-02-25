#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "tree.h"

void print_help() {
    printf("Richiesto argomento: {bst, predecessor, tree, balanced, avl}\n");
}

int main(int argc, char** argv) {

    if (argc != 2) {
        print_help();
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "bst") == 0) {
        
        bst * b = bst_new(6, "Pisa");

        bst_insert(b, 3, "Roma");
        bst_insert(b, 12, "Milano");
        bst_insert(b, 7, "Bologna");
        bst_insert(b, 5, "Firenze");
        bst_insert(b, 1, "Torino");
        bst_insert(b, 15, "Siracusa");
        bst_insert(b, 8, "Bari");

        bst_print(b);

        printf("Valore associato a 5: %s\n", (char *) bst_find(b, 5));

        printf("remove(5)\n");
        bst_remove(b, 5);

        printf("Valore associato a 5: %s\n", (char *) bst_find(b, 5));

        bst_print(b);

        printf("remove(6)\n");
        bst_remove(b, 6);

        bst_print(b);

        printf("remove(3)\n");
        bst_remove(b, 3);

        bst_print(b);
        
        bst_delete(b);
        
    } else if (strcmp(argv[1], "predecessor") == 0) {
        
        bst * b = bst_new(6, "Pisa");

        bst_insert(b, 3, "Roma");
        bst_insert(b, 12, "Milano");
        bst_insert(b, 7, "Bologna");
        bst_insert(b, 5, "Firenze");
        bst_insert(b, 1, "Torino");
        bst_insert(b, 15, "Siracusa");
        bst_insert(b, 8, "Bari");

        bst_print(b);

        printf("Nodo associato a predecessor(8): ");
        printf("[chiave: %d, valore: %s]\n", bst_predecessor(b, 8), (char *) bst_find(b, bst_predecessor(b, 8)));

        printf("remove(7)\n");
        bst_remove(b, 7);

        printf("Nodo associato a predecessor(8): ");
        printf("[chiave: %d, valore: %s]\n", bst_predecessor(b, 8), (char *) bst_find(b, bst_predecessor(b, 8)));

        bst_delete(b);

    } else if (strcmp(argv[1], "tree") == 0) {

        tree * t = build_tree_1();
        int is_bst = tree_is_bst(t);
        if (is_bst == 1)
            printf("L'albero 1 è effettivamente un BST. OK.\n");
        else
            printf("L'albero 1 è un BST ma non viene riconosciuto come tale. KO.\n");            

        tree_delete(t);

        t = build_tree_2();
        is_bst = tree_is_bst(t);
        if (is_bst == 0)
            printf("L'albero 2 non è effettivamente un BST. OK.\n");
        else
            printf("L'albero 2 NON è un BST ma viene riconosciuto come tale. KO.\n");

        tree_delete(t);        

    } else if (strcmp(argv[1], "balanced") == 0) {

        tree * t = build_tree_1();
        int is_bst = tree_is_balanced(t);
        if (is_bst == 1)
            printf("L'albero 1 è effettivamente bilanciato. OK.\n");
        else
            printf("L'albero 1 è bilanciato ma non viene riconosciuto come tale. KO.\n");            

        tree_delete(t);

        t = build_tree_3();
        is_bst = tree_is_balanced(t);
        if (is_bst == 0)
            printf("L'albero 3 non è effettivamente bilanciato. OK\n");
        else
            printf("L'albero 3 non è bilanciato ma non viene riconosciuto come tale. KO.\n");            

        tree_delete(t); 
        
    } else if (strcmp(argv[1], "avl") == 0) {

        tree * t = build_tree_1();
        int is_bst = tree_is_avl(t);
        if (is_bst == 1)
            printf("L'albero 1 è effettivamente un AVL. OK.\n");
        else
            printf("L'albero 1 è un AVL ma non viene riconosciuto come tale. KO.\n");            

        tree_delete(t);

        t = build_tree_2();
        is_bst = tree_is_avl(t);
        if (is_bst == 0)
            printf("L'albero 2 non è effettivamente un AVL. OK.\n");
        else
            printf("L'albero 2 NON è un AVL ma viene riconosciuto come tale. KO.\n");

        tree_delete(t);  

        t = build_tree_3();
        is_bst = tree_is_avl(t);
        if (is_bst == 0)
            printf("L'albero 3 non è effettivamente un AVL. OK\n");
        else
            printf("L'albero 3 non è AVL ma non viene riconosciuto come tale. KO.\n");            

        tree_delete(t);  
        
    } else {

    	print_help();
    	return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
