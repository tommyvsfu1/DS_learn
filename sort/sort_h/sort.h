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


//==============================Quick sort

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


//============================Merge Sort
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

//=====================================Heap Sort
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