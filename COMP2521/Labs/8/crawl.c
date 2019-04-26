// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "queue.h"
#include "html.h"
#include "url_file.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	//char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		//if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit(1);
	}
	
	Graph webG = newGraph(maxURLs);
	Queue toDo = newQueue();
	enterQueue(toDo, firstURL);
	Set seens = newSet();
	
	int nVisited = 0;
	while (!emptyQueue(toDo) && nVisited < maxURLs) {
	
	
	    char *curr = leaveQueue(toDo);  //current node whose neighbours are to be examined
	    insertInto(seens, curr);
	    
	    printf("current page %s\n", curr);
	    //open page for reading URLs
	    if (!(handle = url_fopen(curr, "r"))) {
		    fprintf(stderr,"Couldn't open %s\n", curr);
		    continue;
	    }
	    
	    while(!url_feof(handle)) {
	    //for each line on the page
		    url_fgets(buffer,sizeof(buffer),handle);
		    //fputs(buffer,stdout);
		    int pos = 0;
		    char result[BUFSIZE];
		    memset(result,0,BUFSIZE);
		    
		    while ((pos = GetNextURL(buffer, curr, result, pos)) > 0) {
			    //each URL on line --> result
			    
			    printf("\tchecking url %s\n", result);
			    addEdge(webG, curr, result);
			    
			    if(!isElem(seens, result)){
			    //if haven't traversed before
			        insertInto(seens, result);  //mark as seen
			        enterQueue(toDo, result);   //put in queue to examine later
			        
			        printf("\tnew: '%s'\n",result);
			        
			    }
			    memset(result,0,BUFSIZE);
			
		    }
	    }
	    
	    nVisited++;
	    url_fclose(handle);
	    sleep(1);
	}
	
	showGraph(webG, 0);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}
