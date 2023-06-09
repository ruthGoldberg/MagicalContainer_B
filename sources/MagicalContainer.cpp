#include "MagicalContainer.hpp"
#include <cstddef>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace ariel;
using namespace std;

bool isPrime(int number){
    if (number == 0 || number == 1 || number < 0)
        return false;
    for(int i = 2 ; i<= sqrt(number); i++){
        if (number % i == 0)
            return false;
    }
    return true;
}

bool MagicalContainer::isExists(int element){
    for(int i = 0; i < ContainerSize ; i++){
        if(magicContainer[i] == element){
            return true;
        }
    }
    return false;
}

MagicalContainer :: MagicalContainer(size_t initialcapacity ):
capacity(initialcapacity), ContainerSize(0), magicContainer(new int[initialcapacity]),
crossPointers(new int*[initialcapacity]),primePointers(new int*[initialcapacity]),primeSize(0){}

MagicalContainer:: ~MagicalContainer(){
    destructor();
}

void MagicalContainer::destructor(){
    delete[] magicContainer;
    delete[] crossPointers;
    delete[] primePointers;
    
}
MagicalContainer & MagicalContainer ::operator=(const MagicalContainer &other){
    if (this != &other){
        this->magicContainer = other.magicContainer;
        this->crossPointers = other.crossPointers;
        this->primePointers = other.primePointers;
    }
    return *this;
}
MagicalContainer & MagicalContainer::operator=(MagicalContainer &&other) noexcept {
    if (this != &other){
        this->magicContainer = move(other.magicContainer);
        this->crossPointers = move(other.crossPointers);
        this->primePointers = move(other.primePointers);
    }
    return *this;
}
void MagicalContainer::addElement(int element){
    if(isExists(element))
        return;
    if (ContainerSize == capacity) 
        resize();
    size_t insertIndex = 0;
    while (insertIndex < ContainerSize && magicContainer[insertIndex] <= element) {
        insertIndex++;
    }

    for (size_t i = ContainerSize ; i > insertIndex; i--) {
        magicContainer[i] = magicContainer[i - 1];
    }
    magicContainer[insertIndex] = element;
    ContainerSize++;
    addPointerCross();
    if(isPrime(element)){
        primeSize++;
    }
    addPointerPrime();
}

void MagicalContainer :: resize(){
    capacity *= 2;
    int* newContainer = new int[capacity];
    int** newCrossPointers = new int*[capacity];
    int** newPrimePointers = new int*[capacity];
    for (int i = 0; i < ContainerSize; i++) {
            newContainer[i] = magicContainer[i];
    }
    destructor();
    magicContainer = newContainer;
    crossPointers = newCrossPointers;
    primePointers = newPrimePointers;
}

void MagicalContainer::removeElement(int element){
    int index = -1;
    int crossIndex = -1;
    int primeIndex = -1;
    for (int i = 0; i < ContainerSize; i++) {
        if (magicContainer[i] == element) {
            index = i;
            //break;
        }
        if(*crossPointers[i] == element)
            crossIndex = i;
  
    }
    for (int i = 0; i < primeSize; i++) {
        if(*primePointers[i] == element)
            primeIndex = i;  
    }

    if (index == -1) {
        throw runtime_error("element doen not exists");
    }
    if(primeIndex != -1)
        primeSize--;
    if(index == ContainerSize-1){
        magicContainer[index] = 0;
    }
    if(crossIndex == ContainerSize)
        crossPointers[crossIndex] = nullptr;

    if(primeIndex == primeSize)
        primePointers[primeIndex] = nullptr;
    

    for (int i = index ; i < ContainerSize - 1; i++) {
        magicContainer[i] = magicContainer[i + 1];
    }
    for (int i = crossIndex ; i < ContainerSize - 1; i++) {
        crossPointers[i] = crossPointers[i + 1];
    }
    for (int i = primeIndex ; i < primeSize - 1; i++) {
        primePointers[i] = primePointers[i + 1];
    }

    ContainerSize--;
}

size_t MagicalContainer:: size()const{
    return ContainerSize;
    int c_size;
}

void MagicalContainer::addPointerCross(){
    for(size_t i = 0 , j = 0; i < ContainerSize ; i+=2 , j++){
        crossPointers[i] = &magicContainer[j];
    }
    for(size_t i = 1 , j = ContainerSize - 1; i < ContainerSize ; i+=2 , j--){
        crossPointers[i] = &magicContainer[j];
    }
    
}

void MagicalContainer:: addPointerPrime(){
    for(size_t i = 0 , j = 0; i < ContainerSize ; i++){
        if(isPrime(magicContainer[i])){
            primePointers[j++] = &magicContainer[i];
        }
    }
    
}


//Iterator implementation

MagicalContainer::Iterator::Iterator(const MagicalContainer& container , size_t index):
container(container),index(index){}

MagicalContainer::Iterator::Iterator(const Iterator& iterator):
container(iterator.container) , index(iterator.index)
{}

MagicalContainer::Iterator& MagicalContainer ::Iterator ::operator=(const Iterator& other) {
    if (this == &other) {
        return *this;  // Self-assignment, no need to perform further actions
    } 
    if(container.magicContainer != other.container.magicContainer)
        throw runtime_error("Not the same container!");
    
    index = other.index;    
    return *this;
}


bool MagicalContainer::Iterator::operator>(const Iterator &other)const{
    return index > other.getIndex();
}
bool MagicalContainer::Iterator::operator<(const Iterator &other)const{
    return index < other.getIndex();
}
bool MagicalContainer::Iterator::operator==(const Iterator &other)const{
    return index == other.getIndex();
}
bool MagicalContainer::Iterator::operator!=(const Iterator &other)const{
    return !(*this == other);
}


