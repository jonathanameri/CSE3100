#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"
#include "heap.h"

void extractCodesAux(Node* node, Code* codes,unsigned long long path, char nbits)
{
	/*
TODO: Check if node->c == 0. If it is, then node is an internal node, so call extractCodesAux on the children of it. For the left child, append a zero to the path. For the right child, append a 1 to the path. For example, if path is 01, then the left child would be passed 010 as the path, and the right child would be passed 011 as the path. Also, add 1 to nbits.

If node->c != 0, then it is a leaf node. Set the bits field of codes[node->c] to the path, and the nbits field to nbits.
*/
}

Code* extractCodes(Node* root)
{

	/*
TODO: Allocate space for NUM_SYMBOLS codes. Use calloc so that all elements are initailized to zero first. Then, call extractCodesAux.
*/
}

char* codeToString(Code code)
{
	/*
TODO: Convert the code to a string. For example, if the code is 011, return the string "011". You'll have to actually manipulate the of the code to create this string. 
*/

}


void freeHuffmanTree(Node* root)
{
	if(root){
		if(root->left)
			freeHuffmanTree(root->left);
		if(root->right)
			freeHuffmanTree(root->right);
		free(root);
	}
	/*
TODO: call freeHuffmanTree on the left and right children of root, if they exist. Then, free the root.
*/
}

Node* createHuffmanTree(unsigned long* freq)
{
	Heap* h = makeHeap(2*NUM_SYMBOLS - 1);
	for(int i = 0; i < NUM_SYMBOLS; i++){
		if(freq[i] > 0){
			Node *node = (Node*)malloc(sizeof(Node));
			node->freq = freq[i];
			node->c = i;
			node->left = NULL;
			node->right = NULL;
			insertHeap(h, node);
			/*
TODO: Allocate space for a node, and set the fields of it, and insert it into the heap. 
*/
		}
	}
	while(h->sz > 1){
		Node *u = extractMin(h);
		Node *v = extractMin(h);
		Node *t = (Node*)malloc(sizeof(Node));
		t->freq = u->freq + v->freq;
		t->c = 0;
		t->left = u;
		t->right = v;
		insertHeap(h, t);
	}
	return h->t[1];
	/*
TODO: Implement the algorithm to build the huffman tree. Return the root node of the tree. 
*/
}
