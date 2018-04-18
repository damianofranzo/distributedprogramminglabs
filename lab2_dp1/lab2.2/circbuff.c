#include <stdlib.h>
#include <stdio.h>
#include "circbuff.h"

typedef  struct node * Node;


struct node{
    int i;
    Node next;
};

struct circbuff{
    Node head;
    int n;
};


Circbuff cirbuff_cinit(int n){
    Circbuff c;
    c=malloc(sizeof(struct circbuff));
    c->n=n;

    Node head;
    head=malloc(sizeof(struct node));
    Node nod=head;
    for(int i=0;i<n;i++){
        nod->next=malloc(sizeof(struct node));
        if(i==n-1) nod->next=NULL; //just to be sure
        nod=nod->next;
      //  printf("%d\n",i);
    }
    c->head=head;
    nod=NULL;
    return c;
}

int circbuff_destroy(Circbuff c){
   // int i=0;
    if(c==NULL) return 0;
    if(c->head==NULL) return 0;

    Node nod1=c->head;
    Node nod2=c->head->next;
    for(;nod1!=NULL;nod2=nod2->next){
        //printf("%d\n",i); test
        free(nod1);
        nod1=nod2;
        //i++;
    }
    return 0;
}
