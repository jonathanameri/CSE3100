#include "huffman.h"
#include "file.h"
#include "compression.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct FileData {
   long int size;       // file size in bytes
   char* contents;      // actual bytes
   unsigned long *freq; // frequency table.
   Node* root;          // root of huffman tree
   Code* codeWords;     // collection of code words.
} FileData;

typedef struct HuffData {
   FileData* source;
   ByteArray data;
} HuffData;
   
FileData* readFile(char* fName)
{
  /*
    TODO: Allocate space for a FileData struct, read the file, and fill in the size, contents and freq fields of the FileData struct. 
   */
}

void releaseFile(FileData* fd)
{
  /*
    TODO: Free the memory for the file. This includes the contents, freq, the codeWords, and the associated huffman tree. 
   */
}

void huffmanSetup(FileData* fd)
{
  /*
    TODO: Call the necessary functions to construct the huffman tree, and extract the codes. 
  */
}

HuffData* huffmanCompress(FileData* fd)
{
  /*
    TODO: Use the compress and packBits functions to compress the file, and pack the bits into bytes. 
   */
}

void dumpHuffData(HuffData* hd,char* fName)
{
   FILE* fp = fopen(fName, "wb");
   CompressionHeader ch = {hd->source->freq, hd->source->size, hd->data.numBytes, hd->data.padding};
   printVerbose(hd->source->codeWords, ch);
   writeCompressionHeader(fp,ch);
   fwrite(hd->data.bytes, sizeof(char), hd->data.numBytes, fp);
   fclose(fp);
}

void releaseHuffData(HuffData* hd)
{
   free(hd->data.bytes);
   free(hd);
}

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("Usage: ./compress input output\n");
    return 1;
  }
  FileData* theFile = readFile(argv[1]);
  huffmanSetup(theFile);
  HuffData* theData = huffmanCompress(theFile);
  dumpHuffData(theData,argv[2]);
  releaseHuffData(theData); 
  releaseFile(theFile);
  return 0;
}
