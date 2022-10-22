#include <iostream>
#include <random>
#include <chrono>

void mergeSort(int *input,int arraySize);
void mergeSort(int *input, int *temp, int leftStart, int rightEnd);
void merge(int *input, int *temp, int leftStart, int rightEnd);
void printArray(int *array, int size);


int main() {

    
    int ARRAY_SIZE = 1e7;
    int *randomArray= new int[ARRAY_SIZE];

    std::mt19937_64 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(INT32_MIN,INT32_MAX);

    for(int i=0;i<ARRAY_SIZE;i++){
        randomArray[i] = distribution(generator);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    mergeSort(randomArray,ARRAY_SIZE);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " Milliseconds" << std::endl;

    std::cout<<"Done";



    return 0;

}

//Helper method to print out the array.
void printArray(int* array,int size){
    for(int i=0;i<size;i++){
        std::cout<<array[i]<<" ";
    }
    std::cout<<std::endl;
}


//Helper method that will call do some preliminary checks and then call the recursive mergesort.
void mergeSort(int *input, int arraySize){
    if(input==nullptr || arraySize == 1){ //check if the array is already sorted and save work.
        return;
    }
    int* temp = new int[arraySize]; //make 1 auxiliary array where we can store temp values.
    mergeSort(input,temp,0,arraySize-1);
    delete[] temp;
}

//split the array until there is only 1 element left and then merge them back together in order.
void mergeSort(int *input, int *temp,int leftStart, int rightEnd){
    //if there is more than 1 element in the array.
    if(leftStart < rightEnd){
        int middle = leftStart + (rightEnd-leftStart)/2;
        mergeSort(input,temp,leftStart,middle); //split the left side recursively
        mergeSort(input,temp,middle+1,rightEnd); //split the right side recursively
        merge(input,temp,leftStart,rightEnd); //after we split everything into indexes of 1, merge them together.
    }
}



//merge the 2 arrays together into a sorted array.
void merge(int *input, int *temp, int leftStart, int rightEnd){
    int leftEnd = leftStart + (rightEnd-leftStart) / 2;
    int rightStart = leftEnd+1;
    int size = rightEnd - leftStart + 1;

    int left = leftStart;
    int right = rightStart;
    int index = leftStart;


    while(left <= leftEnd && right <= rightEnd){ //walk through the input and check both right and left and copy the smaller value and increment the pointer.
        if(input[left] <= input[right]){ //if the element in the left input is smaller than the one in the right one, copy that to the temp.
            temp[index] = input[left];
            left++;
        }else{ //otherwise, the element in the right input is smaller, so move that to the temp and increment the pointer.
            temp[index] = input[right];
            right++;
        }
        index++; //increment index of the temp input.
    }

    //We reached out of bounds of one of the elements, so copy over the rest of the elements.
    std::copy(input + left, input + leftEnd + 1, temp + index);
    std::copy(input + right, input + rightEnd + 1, temp + index);
    std::copy(temp + leftStart, temp + size+leftStart, input + leftStart);
}