#include <stdio.h>
#include <stdlib.h>

//There are some "debuging coments" in every function. Very useful to find mistakes in code.

// Struct to store tree element
typedef struct tree_element
{
	int value;			// Element value
	struct tree_element* left;	// Pointer to left subtree
	struct tree_element* right;	// Pointer to right subtree
	//struct tree_element* parent;
} tree_element;

// Create new element, set its value to 'i', return pointer to new element
tree_element* create_tree_element(int i)
{
     tree_element* p =(tree_element*) malloc(sizeof(tree_element));
     p ->value = i;
     p -> left = NULL;
     p->right = NULL;
     return p;
}

// Insert element 'elem' into tree 'root'
tree_element* insert_into_tree(tree_element* root, tree_element* elem)
{
    if (root == NULL)
    {
        //printf("Inserting into NULL\n");
        root = elem;
        return root;
    }

    if (elem == NULL)
    {
        //printf("Tree + NULL = Tree\n");
        return root;
    }

    if (elem->value < root->value)
    {
        root->left = insert_into_tree(root->left,elem);
    }
    else
    {
        root->right = insert_into_tree(root->right,elem);
    }
 return root;
}


// Print tree
void print_tree(tree_element* cur)
{
    if (cur == NULL)
    {
    //printf("I can not print root = NULL\n");
    }
    else
    {
        if (cur->left != NULL)
        {
            print_tree(cur->left);
        }
        printf("%d ",cur->value);
        if (cur->right != NULL)
        {
            print_tree(cur->right);
        }
    }
}


// Search for given value in the tree
// Returns pointer to found element and NULL otherwise
tree_element* search_by_value(tree_element* root, int value)
{
    if (root == NULL)
    {
        //printf("Not found\n");
        return NULL;
    }

    if (root->value == value)
    {
        //printf("Value found\n");
        return root;
    }

    if (value < root->value)
    {
        root = search_by_value(root->left,value);
    }
    if (value > root->value)
    {
        root = search_by_value(root->right,value);
    }
    return root;
}
//searching for parent
tree_element* Umka (tree_element* root, tree_element* elem)
{
    if (root == NULL)
    {
        //printf("Umka: root = NULL\n");
        return NULL;
    }

    if (elem == NULL)
    {
        //printf("Umka: elem = NULL\n");
        return NULL;
    }

    if ((root->left == elem) | (root->right == elem))
    {
        return root;
    }

    if (elem == root)
    {
        //printf("Your element is a root element, so he don't have any parents\n");
        return NULL;
    }

    if (elem->value < root->value)
    {
        root = Umka(root->left,elem);
    }
    if (elem->value > root->value)
    {
        root = Umka(root->right,elem);
    }
    return root;


}

// Deletes element from the tree
tree_element* delete_from_tree(tree_element* root, tree_element* elem)
{
    if ((root == NULL) | (elem == NULL))
    {
        //printf("Deleating error\n");
        return root;
    }

    tree_element* parent = Umka(root,elem);
    if (parent == NULL)
    {
        //printf("Root element was deleated\n");

        root->right = insert_into_tree(root->right,root->left);
        tree_element* Newroot = root->right;

        free(root);
        return Newroot;
    }

    if ((elem->left == NULL) && (elem->right == NULL))
    {
        if (elem->value < parent->value)
        parent->left = NULL;
        else
        parent->right = NULL;

        free(elem);
        return root;
    }


    if (elem->value < parent->value)
    parent->left = elem->right;
    else
    parent->right = elem->right;

    insert_into_tree(parent,elem->left);

    free(elem);
    return root;
}

//Deleates whole tree
void Burn_this_tree(tree_element* root)
{
    if ((root->left == NULL) && (root->right == NULL))
    free(root);
    else
    {
        if (root->left != NULL)
        {
            Burn_this_tree(root->left);
        }
        if (root->right != NULL)
        {
            Burn_this_tree(root->right);
        }
    }

}

int main()
{
    int a[7] = {-3, -1, -5, 3, 1, 5, 6};
	int i;
	char F = 'Y';
    int val;

	tree_element* root = create_tree_element(0);
	for(i = 0; i < 7; i++)
	{
		root = insert_into_tree(root, create_tree_element(a[i]));
	}

	printf("Tree after creation:\n");
	print_tree(root);
	printf("\n");

    tree_element* elem = create_tree_element(100);
    tree_element* par;
	while (F == 'Y')
	{
        F = 'N';
        printf("What do you want to deleate?\n");
        scanf("%d",&val);
        elem = search_by_value(root,val);
        par = Umka(root,elem);
        if (elem != NULL)
        printf("Value founded = %d\n",elem->value);

        if (par != NULL)
        printf("Value of parent = %d\n",par->value);

        root = delete_from_tree(root,elem);
        printf("Elem deleated\n");

        printf("Tree after searching:\n");
        print_tree(root);
        printf("\n");

        printf("Do you want to try again?\n");
        scanf("%s",&F);
	}

    Burn_this_tree(root);
    printf("Tree is burnt\n");

    return 0;
}
