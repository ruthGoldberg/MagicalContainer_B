#include "MagicalContainer.hpp"
#include "iostream"
using namespace ariel;
using namespace std;

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container , size_t index):
Iterator(container,index){}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& iterator):
Iterator(iterator.container,iterator.index){}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator:: begin(){
    return SideCrossIterator(this->container);
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator:: end(){
    return SideCrossIterator (this->container , this->container.size());
    
}
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
    if(end().getIndex() == index)
        throw runtime_error("you have reached the limit");
    ++index;
    return *this;
}
int MagicalContainer::SideCrossIterator:: operator*()const{
    return *container.crossPointers[index];
}

