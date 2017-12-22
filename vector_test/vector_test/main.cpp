//
//  main.cpp
//  vector_test
//
//  Created by Tommy on 2017/12/8.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>
#include <vector>


void k(std::vector<int>* s) {
    
    std::cout << s[0][0];
    std::cout << s[0][1];
    std::cout << s[0][2];
    return ;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<int> list;
    int qq = 1;
    list.push_back(qq);
    qq++;
    list.push_back(qq);
    qq++;
    list.push_back(qq);
    k(&list);
   // std::cout << "Hello, World!\n";
    return 0;
}
