#include<stdio.h>
#include<stdlib.h>
int binary(int a[], int n, int data){
    int l=0,r=n;
    while(l<=r){
        int m=l+(r-l)/2; // Find middle index
        if(a[m]==data) return m; // Element found
        if(a[m]<data) l=m+1; // Search right half
        else r=m-1; // Search left half
    }
    printf("Element Doesn't Exist in The Array!"); return -1; // Not found
}
int binaryRecursive(int a[], int l, int r, int data){
    // If array is not empty
    if(l<=r){
        int m=l+(r-l)/2;
        if(a[m]==data) return m; // Element found
        if(a[m]<data) return binaryRecursive(a, m+1, r, data); // Search right
        else return binaryRecursive(a, l, m-1, data); // Search left
    }
    printf("Element Doesn't Exist in The Array!"); return -1; // Element not found
}
int main(){
    // Input Size of Array
    printf("Enter the Size of The Array: ");
    int n; scanf("%d",&n);
    
    // Declare and Input Array
    int a[n];
    printf("Enter the Elements: \n");
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    
    // Input Element to Search
    printf("Enter the Element to be Searched: ");
    int data; scanf("%d",&data);
    
    // Start Clock
    clock_t t = clock();
    
    // Call Binary Search Function 100,000 Times
    for(int j=0;j<100000;j++) binary(a,n,data);
    
    // Calculate and Print Time Taken
    t = clock() - t; 
    double time_taken = ((double)t); // in seconds 
    printf("Took %lf seconds to execute \n", time_taken); 
}