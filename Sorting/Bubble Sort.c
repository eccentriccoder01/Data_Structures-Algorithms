#include<stdio.h>
#include<stdlib.h>
void swap(int *x, int *y){
    int t=*x; *x=*y; *y=t;
}
void bubble(int a[],int n){
    for(int i=0;i<n-1;i++) for(int j=0;j<n;j++) if(a[i]>a[j]) swap(&a[i],&a[j]);
}
