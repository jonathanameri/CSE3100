#include "analyze.h"
#include <string.h>
#include <assert.h>


#include <stdio.h>

void analyzeURL(char* url,char* host,int* port,char* doc)
{
	int len = strlen(url);
	int s = 0;
	if(url[4] == ':' && url[5] == '/' && url[6] == '/')
		s = 7;
	for (int i = s; i < len; i++){
		if(url[i] != ':')
			host[i-s] = url[i];
		else{
			host[i-s] = '\0';
			s = i+1;
			break;
		}
	}
	printf("s = %d\n", s);
   /* TODO: Implement the URL decomposition.
    * input: URL the given url
      output: host : where you place the host part of the URL
              port : where you place the port number (if any)
              doc  : where you place the document name
   */
}
