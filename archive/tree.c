#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TNode{
  char* val;
  struct TNode* left;
  struct TNode* right;
} TNode;

TNode* makeEmptyTree()
{
   return NULL;
}

TNode* insertIntoTree(TNode* root,char* string)
{
  /*
    TODO: Insert the string into the tree. First, check if the root is NULL. If it is, then create a new TNode, copy the string into it, and return the pointer to the new TNode. 

    If root is not NULL, then compare root->val and string using strcmp. If root->val < string, then call insertIntoTree again on root->left. Keep in mind that root->left might be NULL. If root->val > string, then call insertIntoTreeAgain on root->right. Again, root->right might be NULL. If root->val is equal to string, then the string is already in the tree, and you don't need to do anything. In any case, return root.
   */

  if (!root)
  {
    int len = strlen(string);
    //printf("Len = %d\n", len);
    root = (TNode*) malloc(sizeof(TNode));
    root->val = malloc(len * sizeof(char) + 1);
    root->val[len] = 0;

    root->left = makeEmptyTree();
    root->right = makeEmptyTree();

    for(size_t i = 0; i < len; i++)
    {
      root->val[i] = string[i];
    }

    return root;
  }

  //printf("Compare %s to %s \n", root->val, string);
  //printf("%d \n", strcmp(root->val, string));

  if (strcmp(root->val, string) < 0)
  {
    root->left = insertIntoTree(root->left, string);
  }
  else if (strcmp(root->val, string) > 0)
  {
    root->right = insertIntoTree(root->right, string);
  }

  return root;
}

TNode* searchTree(TNode* root, char* string)
{
  if(root)
  {
    if (strcmp(root->val, string) < 0)
      return searchTree(root->left, string);

    if (strcmp(root->val, string) > 0)
      return searchTree(root->right, string);

    return root;
    /*
      TODO: Search the tree for the string. First, use strcmp to compare root->val to string. 

      If string == root->val, return the root. 

      If string < root->val, then call searchTree on the right child of root.

      If string > root->val, then call searchTree on the left child of root.
     */
  }
  else
    return NULL;
}

void printTree(TNode* root)
{
   if (root == NULL)
      return;
   else {
      printf("(");
      printTree(root->left);
      printf(" %s ",root->val);
      printTree(root->right);
      printf(")");      
   }
}

void destroyTree(TNode* root)
{
  /*
    TODO: Free the nodes in the tree, and the strings stored in those nodes. This is easier to do recursively. 
   */

  if(root)
  {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root->val);
    free(root);
  }

}




int main(int argc, char* argv[])
{
  if(argc != 2){
    printf("Usage: ./tree wordList\n");
    return 1;
  }
  TNode* tree = makeEmptyTree();
  /*
    TODO: The path to the file containing the words is stored in argv[1]. Call fopen to open it. 
   */
  FILE *fp = fopen(argv[1], "r");
  char word[200];
  size_t length;
  /*
    TODO: Use fscanf to read a word at a time from the file, and call insertIntoTree to insert the word into the tree.
   */

  while (EOF != fscanf(fp, "%[^\n]\n", word))
  {
    tree = insertIntoTree(tree, word);
  }

  //printTree(tree);

  /*
    TODO: fclose the file.
   */
  fclose(fp);

  while(1){
    printf("word: ");
    int r = scanf("%s", word);
    if(r != 1)
      break;
    length = strlen(word);
    if(length < 1)
      break;
    TNode* node = searchTree(tree, word);
    if(node){
      printf("PRESENT\n");
    }else{
      printf("ABSENT\n");
    }    
  }
  destroyTree(tree);
  return 0;
}
