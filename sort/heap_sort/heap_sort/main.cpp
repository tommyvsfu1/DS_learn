//
//  main.cpp
//  heap_sort
//
//  Created by Tommy on 2017/12/30.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>


void adjust(int* element, int root, int n) {
    
    int i;
    int key = element[root];
    for (i = root * 2; i<=n; i *= 2){
        if (i < n && (element[i] < element[i+1])){
            i++;
        }
        if (element[i] < key) {
            break;
        }
        element[i/2] = element[i];
    }
    element[i/2] = key;
}

void heap_sort(int* element, int root, int n) {
    
    for (int i = n/2; i>=1; i--) {
        adjust(element,i, n);
    }

    for (int i = 1; i <=n-1; i++){
        int tmp = element[n+1-i];
        element[n+1-i] = element[1];
        element[1] = tmp;
        adjust(element, 1, n-i);
    }
    for (int i = 1; i < 11; i++){
        std::cout << element[i] << " ";
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int a[11] = {-1,3,7,23,44,55,100,2,4,5,5};
    
    //adjust(a, 1, 10);
    //std::cout << a[1];
    heap_sort(a, 1, 10);
    return 0;
}
