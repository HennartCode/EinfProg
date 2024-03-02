#include <stdio.h>
#include <stdlib.h>

void swap(int* A, int a, int b){
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

void merge(int* A,int p,int q,int len){
int *OUT = (int*)malloc(sizeof(int)*len);
int o = 0;
int i = p;
int j = q;
while (i < q && j<len){
    if (A[i] < A[j]){
        OUT[o] = A[i];
        i++;
    }
    else{
        OUT[o] = A[j];
        j++;
    }
    o++;
}
while (i==q && j<len)
{
    OUT[o] = A[j];
    o++;
    j++;
}
while (j==len && i<q)
{
    OUT[o] = A[i];
    o++;
    i++;
}
for (int i = 0; i<len; i++){
    A[i] = OUT[i];
}
free(OUT);
return;
}

void printarr(int*arr,int len){
    printf("\n[");
    for (int i = 0; i<len; i++){
        printf("%d",arr[i]);
        if (i+1 < len){
            printf(" ");
        }
    }
    printf("]");
}


typedef struct arrHeap{
    int *Array; 
    int height;
    int len;
}arrHeap;

arrHeap* AHeap_newroot(int key){
    arrHeap* New = malloc(sizeof(arrHeap));
    New->Array = malloc(sizeof(int));
    New->height = 1;
    New->len = 1;
    New->Array[0] = 17;
    return New;
}

void AHeap_min_Heapify(arrHeap* A, int ix){
    int lc = ((ix+1)*2)-1;
    int rc = (ix+1)*2;
    int largest;
    if (lc < A->len && A->Array[lc] < A->Array[ix]){
        largest = lc;
    }else{
        largest = ix;
    }
    if (rc < A->len && A->Array[rc] < A->Array[largest]){
        largest = rc;
    }

    if (largest != ix){
        swap(A->Array,ix,largest);
        AHeap_min_Heapify(A,largest);
    }

}

void AHeap_make_minHeap(arrHeap* A){
    int lastparent = (int)((A->len/2)-1);
    for (int i = lastparent; i>=0; i--){
        AHeap_min_Heapify(A,i);
    }
}

void AHeap_add(arrHeap* A, int key){
    int* old = A->Array;
    int* new = malloc(sizeof(int)*(A->len+1));
    for (int i = 0; i<A->len; i++){
        new[i] = old[i];
    }
    free(old);
    new[A->len] = key;
    A->Array = new;
    A->len++;
} 

int AHeap_isminHeap(arrHeap* A){
    for (int i = 1; i<A->len; i++){
        int parent = A->Array[(int)(((i+1)/2)-1)];
        if (A->Array[i] < parent){
            return 0;
        }
    }
    return 1;
}





int main(){
    int A[9] = {2,6,7,8,4,7,16,16,20};
    int B[3] = {1,2,3};
    // printarr(A,9);
    // merge(A,0,4,9);
    // printarr(A,9);


    arrHeap* myheap = AHeap_newroot(17);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    AHeap_add(myheap,15);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    AHeap_add(myheap,13);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    AHeap_add(myheap,4);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));
    
    AHeap_make_minHeap(myheap);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    AHeap_add(myheap,20);
    AHeap_add(myheap,16);
    AHeap_add(myheap,14);
    AHeap_add(myheap,4);
    AHeap_add(myheap,2);
    AHeap_add(myheap,1);

    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    AHeap_make_minHeap(myheap);
    printarr(myheap->Array,myheap->len);
    printf("ISMINHEAP?: %d" ,AHeap_isminHeap(myheap));

    for (int i = (myheap->len)-1; i>=0; i--){
        printf("\nKEY: %d  |  PARENT: %d",myheap->Array[i], myheap->Array[(int)(((i+1)/2)-1)]);
    }

    return 0;
}