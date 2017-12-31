//
//  main.cpp
//  Merge Sort
//
//  Created by Tommy on 2017/12/31.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>



void merge(int* list, int* rlist,int l,int m,int n) {
    /*
     list[l:m]    merge   list[m+1:n]
            to
            rlist[l:n]
     */
    int R2 = l;
    int i = l;
    int j = m+1;
    for(; i <= m && j <= n; R2++){
        if (list[i] <= list[j]) {
            rlist[R2] = list[i];
            i++;
        }
        else {
            rlist[R2] = list[j] ;
            j++;
        }
    }
    
    if (i > m) {
        for(; j <= n; j++,R2++)
            rlist[R2] = list[j];
    }
    else {
        for (; i <= m;i++,R2++)
            rlist[R2] = list[i];
    }
    
    
}


void IterativeMergeSort(int* list, int* rlist,int l, int r, int length) {
    int i ;
    for(i = l;(i+2*length-1) <= r; i+= 2*length) {
        merge(list, rlist, i, i+length-1, i+length*2-1);
    }
    if (i == l) {
        merge(list,rlist,i,i+length-1,r);
    }
    else {
        for (;i<=r;i++)
            rlist[i] = list[i];
    }
}


void Iterative(int* list, int* rlist, int l, int r) {
    for (int length=1;length < (l-r+1); length*=2) {
        IterativeMergeSort(list, rlist, l, r, length);
        length*=2;
        IterativeMergeSort(rlist,list, l, r, length);
    }
}

void RmergeSort(int* list,int* tlist, int l, int r) {
    if (l==r) return;
    
    int m = (l+r)/2;
    
    RmergeSort(list,tlist, l, m);
    RmergeSort(list,tlist, m+1, r);
    
    merge(list,tlist,l,m,r);
    
    for (int i = 0; i < r+1; i++) {
        list[i] = tlist[i];
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int tlist[6];
    int a[6] = {2,3,10,1,6,5};
    //Iterative(a, tlist, 0, 5);
    //for (int i = 0; i < 6; i++)
      //  std::cout << a[i] << " ";
    IterativeMergeSort(a, tlist, 0, 5, 1);
    IterativeMergeSort(tlist, a, 0, 5,2);
    IterativeMergeSort(a, tlist, 0, 5, 4);
    for (int i = 0; i < 6; i++)
        std::cout << tlist[i] << " ";
    return 0;
}
