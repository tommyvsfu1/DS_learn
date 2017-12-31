//
//  main.cpp
//  Quick Sort
//
//  Created by Tommy on 2017/12/31.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>


void Replace(int list[], int l, int r) {
    int tmp = list[l];
    list[l] = list[r];
    list[r] = tmp;
}
void Quick_sort(int list[], int l, int r) {
    
    int tmp[10];

    if (l >= r) return ;
    int left = l;
    int right = r;
    
    int pivot = list[l];
    
    /*
        while 條件絕對不能 "="
        因為如果等於代表你找到中介點
        既然找到中介點loop 裡面的事情就等於沒做
        會變成無窮迴圈
     */
    while(left < right) {
        for (int i = 0; i < 10; i++)
            tmp[i] = list[i];
        while(list[left] <= pivot && left < r) left++;
        /*
            為何left ++ 要設定bound 而right 可以設定或不設定(>= 改成>) 是因為
                我們的pivot 在於最左邊, right 最後一定會經過他（如果極端例子）, 那你設> 就可以避免變成0
         */
        //while(list[right] >= pivot && right>l) right--;
        while(list[right] > pivot) right--;
        
        if (left < right)
            Replace(list,left,right);
    }
    int ss[10];
    for (int i = 0; i < 10; i++)
        ss[i] = list[i];
    Replace(list, l, right);
    Quick_sort(list, l, right-1);
    Quick_sort(list, right+1, r);
}




int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int list[10] = {23,44,55,2,112,54,-34,55,33,2};
    Quick_sort(list, 0, 9);
    for (int i = 0; i < 10; i++)
        std::cout << list[i] << " ";
    return 0;
}
