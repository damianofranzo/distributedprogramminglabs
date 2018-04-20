typedef  struct  circbuff* Circbuff;

Circbuff cirbuff_cinit(int n);
int circbuff_destroy(Circbuff c);
int searchinsert(Circbuff c,char *client);
