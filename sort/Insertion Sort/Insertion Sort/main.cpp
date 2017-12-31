//
//  main.cpp
//  Insertion Sort
//
//  Created by Tommy on 2018/1/1.
//  Copyright © 2018年 Tommy. All rights reserved.
//

#include <iostream>

void InsertList(int* list, int element, int j) {
    // insert a element into a list[1:j]
    // from j to 1
    // 0 is MININT
    int i = j;
    while(element < list[i]) {
        list[i+1] = list[i];
        i--;
    }
    list[i+1] = element;
}

void InsertionSort(int* list, int l, int r) {
    list[0] = INT_MIN;
    for(int i = 2; i<=r; i++)
        InsertList(list, list[i], i-1);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int a[6] = {1,10,5,3,4,7};
    //InsertList(a, 1, 4);
    InsertionSort(a, 0, 5);
    for (int i = 0; i < 6; i++)
        std::cout << a[i] << " ";
    std::cout << "Hello, World!\n";
    return 0;
}
