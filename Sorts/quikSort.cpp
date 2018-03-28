//
//  main.cpp
//  quikSort
//
//  Created by Mikaela Schaefer on 3/26/18.
//  Copyright © 2018 Mikaela Schaefer. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class ArrBuilder {
private:
    int n;
    shared_ptr<vector<int> > myArr;

public:
    ArrBuilder();
    shared_ptr<vector<int> > getArr(){return myArr;};
};

ArrBuilder::ArrBuilder(){
    cout << "How large do you want your array to be? ";
    cin >> n;
    myArr = std::make_shared<std::vector<int> >(n);

    int i = 0;
    while ( i < n){
        int inVal;
        cin >> inVal;
        (*myArr)[i] = std::move(inVal);
        i++;
    }
}

void swap(vector<int>& arr, int x, int y){
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void QuickSortHelper(std::vector<int>& arr, const int low, const int high){
    int i, j, mid, pivot;
    i = low;
    j = high;
    mid = low + (high - low) / 2;
    pivot = arr[mid];
    while ( i < high || j > low) {
        while (arr[i] < pivot){
            i++;
        }
        while (arr[j] > pivot){
            j--;
        }
        if (i <= j) {
            swap(arr, i, j);
            i++;
            j--;
        }
        else{
            if (i < high){
                QuickSortHelper(arr, i, high);
            }
            if (j > low) {
                QuickSortHelper(arr, low, j);
            }
            return;
        }
    }
}

void QuickSort(shared_ptr<vector<int> > theArr){
    //SplitAndRecurse
    std::vector<int> anotherArray = (*theArr);
    const int size = anotherArray.size();
    QuickSortHelper(anotherArray, 0, size-1);
    (*theArr) = std::move(anotherArray);
}

int main(int argc, const char * argv[]) {
    ArrBuilder arr;

    QuickSort(arr.getArr());

    int n = (*arr.getArr()).size();
    for (int i =0; i < n; i++){
        cout << (*arr.getArr())[i] << " ";
    }
    return 0;
}

