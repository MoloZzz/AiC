#include <iostream>
//#include"Calc.h"
#include"MargeSort.h"
#include<vector>
#include<random>

//void demo_lab1(){
//	ComplexMatrix square_m1(6, 6);
//	ComplexMatrix square_m2(6, 6);
//
//	square_m1.auto_gen(2, 6, 2, 6);
//	square_m2.auto_gen(1, 10, 1, 10);
//
//	square_m1.print();
//	std::cout << "----------------------" << std::endl;
//	square_m2.print();
//	std::cout << "----------------------" << std::endl;
//	Strassen(&square_m1, &square_m2)->print();
//}

void random_array(int arr[],int size) {
    int i = 0;
    srand(time(NULL));
    while (i < size) {
        arr[i] = rand() % 1000;
        i++;
    }


}

int main()
{
    /*int arr1[] = { 12, 11, 13, 5, 6, 7 };*/

    int arr2[100] = {};

    random_array(arr2, 100);
    auto arr_size = sizeof(arr2) / sizeof(arr2[0]);

    cout << "Our array:" << endl;

    for (auto i = 0; i < arr_size; i++)
        cout << arr2[i] << ",";
    cout << endl;

    mergeSort(arr2, 0, arr_size - 1);

    cout << "Sorted array:" << endl;
    for (auto i = 0; i < arr_size; i++)
        cout << arr2[i] << " ";
    cout << endl;

}

