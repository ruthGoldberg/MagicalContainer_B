
#pragma once
#include <cstddef>
#include <vector>

namespace ariel{
    class MagicalContainer
    {
    private:
        static constexpr size_t DEFAULT_INITIAL_CAPACITY = 2;
        int* magicContainer;
        int** primePointers;
        int** crossPointers;
        size_t ContainerSize;
        size_t capacity;
        size_t primeSize;
        void destructor();
        void resize();
        bool isExists(int element);
        void addPointerCross();
        void addPointerPrime();
    public:
        
        MagicalContainer(size_t initialcapacity = DEFAULT_INITIAL_CAPACITY);
        ~MagicalContainer();
        MagicalContainer(const MagicalContainer &other){}
        MagicalContainer(MagicalContainer &&other) noexcept{}
        MagicalContainer &operator=(const MagicalContainer &other);
        MagicalContainer &operator=(MagicalContainer &&other) noexcept ;
        void addElement(int);
        void removeElement(int);
        size_t size()const;
    
        class Iterator{
            public:
                const MagicalContainer& container;
                size_t index;
                
                Iterator(const MagicalContainer& container , size_t index = 0);
                Iterator(const Iterator& iterator);
                virtual ~Iterator() = default;
                Iterator& operator=(const Iterator& other);
                virtual Iterator &operator++() = 0;
                virtual int operator*() = 0;
                bool operator!=(const Iterator &other)const;
                bool operator==(const Iterator &other)const;
                bool operator>(const Iterator &other)const;
                bool operator<(const Iterator &other)const;
                size_t getIndex()const{ return index;}
                
                
        
        };
        class AscendingIterator: public Iterator{
            
            public:
                AscendingIterator(const MagicalContainer& container , size_t index = 0);
                AscendingIterator(const AscendingIterator& iterator);
                ~AscendingIterator()override = default;
                AscendingIterator begin();
                AscendingIterator end();
                AscendingIterator &operator++()override;
                int operator*()override;
                
                
        
        };

        class SideCrossIterator:public Iterator
        {
             
        public:
            SideCrossIterator(const MagicalContainer& container , size_t index = 0);
            SideCrossIterator(const SideCrossIterator& iterator);
            ~SideCrossIterator()override = default;
            SideCrossIterator begin();
            SideCrossIterator end();
            SideCrossIterator &operator++()override;
            int operator*()override;
            
            
        };

        class PrimeIterator:public Iterator
        {
       
        public:
            PrimeIterator(const MagicalContainer& container , size_t index = 0);
            PrimeIterator(const PrimeIterator& iterator);
            ~PrimeIterator() override = default;
            PrimeIterator begin();
            PrimeIterator end();
            PrimeIterator &operator++()override;
            int operator*()override;
            
            
        };
        
    };
    
}