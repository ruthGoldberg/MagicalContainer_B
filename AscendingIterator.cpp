#include "MagicalContainer.hpp"
#include "iostream"
using namespace ariel;
using namespace std;


MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container , size_t index):
Iterator(container,index){}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& iterator):
Iterator(iterator.container , iterator.index)
{}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator:: begin(){
    return AscendingIterator(this->container);
}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator:: end(){

    return AscendingIterator(this->container , this->container.size());
    
}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
    if(end().getIndex() == index) 
        throw runtime_error("you have reached the limit");
    ++index;
    return *this;
}
int MagicalContainer::AscendingIterator:: operator*()const{
    return container.magicContainer[index];
}



