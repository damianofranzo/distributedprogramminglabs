#include <stdlib.h>
#include <stdio.h>
#include "circbuff.h"
#include <string.h>
#include <strings.h>

#define N 30

typedef  struct node * Node;


struct node{
    int i;
    char client[N];
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
        nod->i=0;
        strcpy(nod->client,"");
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

/*int insert(Circbuff c,Node node){
    Node head=c->head;
    c->head=c->head->next; // i change the head

    free(head);

    Node n=c->head;
    for(int i=0;i<c->n-2;i++){
        n=n->next;
    }
    n->next=node;

    return 0;

}*/

int searchinsert(Circbuff c,char *client){
    Node node=c->head;
    for(int i=0;i<c->n-1;i++){
/*        if(node->next->client==NULL)
            break;
        if(strcmp(client,node->client)==0){
            node->i++;
        }
        if(i!=c->n-1)
            node=node->next;*/
            if(strcmp("",node->client)==0){
                strcpy(node->client,client);
                node->i=1;
                return 1;
            }
            else if(strcmp(node->client,client)){
                node->i++;
                return node->i;
            }
            node=node->next;
    }

    //check the last node
    if(strcmp("",node->client)==0){
        strcpy(node->client,client);
        node->i=1;
        return  1;
    }
    else if(strcmp(node->client,client)){
        node->i++;
        return node->i;
    }
    else {
        node->next = malloc(sizeof(struct node));
        strcpy(node->next->client, client);
        node->next->i=1;
        node->next->next=NULL;

        Node head=c->head;
        c->head=head->next;
        free(head);
    }




    /*node->next=malloc(sizeof(struct node));
    strcpy(node->next->client,client);
    node->next->i=1;*/

    return 1;

}
