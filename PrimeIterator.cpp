#include "MagicalContainer.hpp"
#include "iostream"
using namespace ariel;
using namespace std;


MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container , size_t index):
Iterator(container,index){}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& iterator):
Iterator(iterator.container,iterator.index){}



MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator:: begin(){
    return PrimeIterator(this->container);
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator:: end(){
    return PrimeIterator (this->container , this->container.primeSize);
}
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
    if(end().getIndex() == index)
        throw runtime_error("you have reached the limit");
    ++index;
    return *this;
}
int MagicalContainer::PrimeIterator:: operator*()const{
    return *container.primePointers[index];
}




