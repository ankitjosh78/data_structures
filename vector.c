// C++ STL std::vector translates to a dynamic array
// () -> initialize
// push_back(), pop_back(), back(), insert(idx,value), erase(idx) 
// capacity (memory representation or memory allocation in bytes), size (logical representation of elements)
// even if size is zero, capacity may not be zero.
// O(1) amoritzed TC for push_back
// vector needs to have my elements, so i need a array, size, capacity

#include<stdio.h>
#include<stdlib.h>

// Vector struct
typedef struct Vector{
  int *data;
  int size;
  int capacity;
} Vector;

// vector<int>arr(10)
// Vector* arr = initVector(10)
Vector* initVector(int initialCapacity){
  Vector* arr = malloc(sizeof(Vector));
  arr->capacity = initialCapacity > 0? initialCapacity: 1;
  arr->size = 0; // tells the logical size of the array and also points to the next index where a new element can be appended
  arr->data = malloc(arr->capacity*sizeof(int));
  return arr;
}

// push_back
// idx: 0 1 2
// ele: 1 2 3
// push_back(4)
// idx: 0 1 2 3
// ele: 1 2 3 4
void push_back(Vector* arr, int value){
  if(arr->size == arr->capacity){
    arr->capacity *= 2;
    int *temp = realloc(arr->data, arr->capacity*sizeof(int));
    if(temp==NULL){
      printf("Memory allocation failed\n");
      exit(1);
    }
    arr->data = temp;
  }
  //*(arr->data + arr->size) = value; same thing
  arr->data[arr->size] = value;
  arr->size++;
}

// pop_back
// idx: 0 1 2
// ele: 1 2 3
// pop_back()
// idx: 0 1
// ele: 1 2
void pop_back(Vector* arr){
  if(arr->size==0) return;
  arr->size--;
  return;
}

// back
int back(Vector* arr){
  if(arr->size == 0) return -1;
  return arr->data[arr->size - 1];
}

// front
int front(Vector* arr){
  if(arr->size == 0) return -1;
  return arr->data[0];
}
// idx: 0 1 2 3 4
// ele: 1 2 3 4 5
// insert(2, 7)
// idx: 0 1 2 3 4 5
// ele: 1 2 7 3 4 5
void insert(Vector* arr, int index, int value){
  // index needs to be valid
  if(index < 0 || index > arr->size){
    printf("Index out of bounds\n");
    return;
  }
  if(index==arr->size){
    push_back(arr, value);
    return;
  }
  // insert means. insert at the given index. shift all the elements after the index to right by 1.
  // making sure we have enough space
  if(arr->size == arr->capacity){
    arr->capacity*=2;
    int *temp = realloc(arr->data, arr->capacity*sizeof(int));
    if(temp==NULL){
      printf("Memory allocation failed\n");
      exit(1);
    }
    arr->data = temp;
  }
  // Shifting elements to the right of (index) by 1.
  for(int i=arr->size;i>index;i--){
    arr->data[i] = arr->data[i-1];
  }
  arr->data[index] = value;
  arr->size++;
}

// erase(idx)
// idx: 0 1 2 3 4
// ele: 1 2 3 4 5
// erase(2)
// idx: 0 1 2 3
// ele: 1 2 4 5
void erase(Vector* arr, int index){
  // index needs to be valid
  if(index < 0 || index >= arr->size){
    printf("Index out of bounds\n");
    return;
  }
  if(index == arr->size-1){
    pop_back(arr);
    return;
  }
  for(int i=index;i<arr->size - 1;i++){
    arr->data[i] = arr->data[i+1];
  }
  arr->size--;
}

void freeVector(Vector* arr){
  if(arr==NULL) return;
  free(arr->data);
  free(arr);
}

void printVector(Vector* arr){
  for(int i=0;i<arr->size;i++){
    printf("Element at index: %d is: %d\n", i, arr->data[i]);
  }
}
int main(){
  Vector* arr = initVector(1);
  push_back(arr, 1);
  push_back(arr, 2);
  push_back(arr, 3);
  push_back(arr, 4);
  push_back(arr, 5);
  // 1 2 3 4 5
  printVector(arr);
  
  // insert (2,7)
  // 1 2 7 3 4 5
  insert(arr, 2, 7);
  printVector(arr);
  // erase (1)
  // 1 2 7 3 4 5 -> 1 7 3 4 5
  erase(arr, 1);
  printVector(arr);
}

