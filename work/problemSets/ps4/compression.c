#include "compression.h"
#include <stdlib.h>
#include <assert.h>


unsigned long countBits(char* text, unsigned long sz, Code* codes)
{
  /*
    This takes in a string text of length sz, and a set of Codes. Each
    character corresponds to a Code consisting of nbits; this simply
    sums the number of bits for the Code of each character. 
   */
  unsigned long numBits = 0;
  /*
    TODO: Finish this function
   */
  return numBits;
}

BitStream compress(char* text, unsigned long sz, Code* codes)
{
  /*
    TODO: This compresses text into a BitStream.
   */
}

char* decompress(char* bits, unsigned long numBits, unsigned long usz, Node* root)
{
  /*
    This takes a char array, which holds the bits of the compressed
    text. A bit is stored in each char. unz is the uncompressed size
    of the text.
    
    Use the huffman tree and the bits to decompress the text, and
    return a string. Be sure to include the null terminator at the
    end!
   */
  char* text = calloc(usz + 1, sizeof(char));
  unsigned long i = 0;
  unsigned long j = 0;
  while(i < numBits){
    Node* n = root;
    while(n->c == 0 && i < numBits){
      n = bits[i] ? n->right : n->left;
      i++;
    }
    assert(n->c != 0 && j < usz);
    text[j] = n->c;
    j++;
  }
  return text;
}
