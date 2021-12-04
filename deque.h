/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    Our custom implementation of a deque
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        deque                 : A class that represents a binary search tree
 *        deque::iterator       : An iterator through BST
 * Author
 *    Alexander Dohms, Stephen Costigan, Shaun Crook, Jonathan Colwell
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>
#include <iostream>

namespace custom
{

/******************************************************
 * DEQUE
 *   0   1   2   3   4
 * +---+---+---+---+---+
 * |   | A | B | C |   |
 * +---+---+---+---+---+
 * iaFront = 1
 * numElements = 3
 * numCapacity = 5
 *****************************************************/
template <class T>
class deque
{
public:

   // 
   // Construct
   //

   deque() : numCapacity(0), numElements(0), iaFront(0) { data = nullptr; }
   deque(int newCapacity);
   deque(const deque <T> & rhs);
   ~deque() { 
       if (numCapacity)
           delete[] data;
       clear(); 
   }

   //
   // Assign | Steve - Done
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator | Steve - still needs work
   //
   class iterator;
   iterator begin() { return iterator(this, 0); }
   iterator end()   { return iterator(this, numElements); }

   //
   // Access - Shaun
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;

   // Steve - Done
   const T & operator[](size_t index) const;
         T & operator[](size_t index);

   // 
   // Insert - Alex
   //
   void push_front(const T& t);
   void push_back(const T& t);
   //Required for push front and back
   void realloc(int num);

   //
   // Remove - Jon
   //
   void clear() 
   { 
       if (numCapacity == 0)
           return;
       if (numElements) 
           for (int id = 0; id < numElements - 1; id++)
               data[iaFromID(id)] = NULL;
       
       numElements = 0; 
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const { return numElements; }
   bool empty() const  { return numElements == 0; }

   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   // fetch array index from the deque index - Shaun
   int iaFromID(int id) const
   {
       int temp = iaFront + id;
       if (temp < 0)
           while (temp < 0)
               temp += numCapacity;
       if (id)
           return temp % numCapacity;
       return 0;
   }
   void resize(int newCapacity = 0);

   // member variables
   T * data;           // dynamically allocated data for the deque
   size_t numCapacity; // the size of the data array
   size_t numElements; // number of elements in the deque
   int iaFront;        // the index of the first item in the array
};



/**********************************************************
 * DEQUE ITERATOR
 * Forward and reverse iterator through a deque, just call
 *********************************************************/
template <typename T>
class deque <T> ::iterator
{
public:
   //
   // Construct
   //
   iterator() : id(0), pDeque(nullptr) { }
   iterator(custom::deque<T> *pDeque, int id)
   {
       this->id = id;
       this->pDeque = pDeque;
   }
   iterator(const iterator& rhs) { *this = rhs; }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
       this->id = rhs.id;
       this->pDeque = rhs.pDeque;
       return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return this->pDeque == rhs.pDeque; }
   bool operator != (const iterator& rhs) const { return this->pDeque != rhs.pDeque; }

   // 
   // Access
   //
   const T & operator * () const 
   {
      return pDeque->data[id];
   }
   T & operator * () // Don't think this is quite right
   {
      return pDeque->data[id];
   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
      return id - it.id;
      //return *this;
   }
   iterator& operator += (int offset)
   {
       this->id += offset;
       return *this;
   }
   iterator& operator ++ ()
   {
       this->id++;
       return *this;
   }
   iterator operator ++ (int postfix)
   {
       iterator i = this;
       this->id++;
       return i;
      /*return *this;*/
   }
   iterator& operator -- ()
   {
       this->id--;
       return *this;
   }
   iterator  operator -- (int postfix)
   {
       iterator i = this;
       this->id--;
       return i;
   }

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   // Member variables
   int id;             // deque index
   deque<T> *pDeque;
};


/****************************************************
 * DEQUE : CONSTRUCTOR - non-default
 ***************************************************/
template <class T>
deque <T> :: deque(int newCapacity)
{
    // Looks right, but doesn't contribute yet
    numCapacity = newCapacity;
    numElements = 0;
    iaFront = 0;

    if(newCapacity > 0)
        data = new T[newCapacity];
    else
        data = nullptr;
}

/****************************************************
 * DEQUE : CONSTRUCTOR - copy
 ***************************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs)
{  
   *this = rhs;
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
    //clear();
    iaFront = 0;
    data = new T[rhs.numCapacity];

    if (numElements < rhs.numElements)
        resize(rhs.numElements);

    numElements = rhs.numElements;

    for (int i = 0; i < numElements; ++i)
        data[i] = rhs.data[rhs.iaFromID(i)];

    return *this;
}


/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
    //assert(numElements != 0);
    //assert(nullptr != data.iaFront); //this will prbably work after the operator is done

    return data[iaFront];

   //return *(new T);
}
template <class T>
T& deque <T> ::front()
{
    //assert(numElements != 0);
    //assert(nullptr != data[iaFront]); //this will prbably work after the operator is done

    return data[iaFront];
    //return *(new T);
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
    assert(numElements != 0);
    //assert(nullptr != iaFront(numElements - 1)); //this will prbably work after the operator is done
    //iaFront = iaFront(numElements - 1);
    return data[iaFromID(numElements - 1)];
   //return *(new T);
}

template <class T>
T& deque <T> ::back()
{
    return data[iaFromID(numElements-1)];
   //return *(new T);
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
    return data[index];
   //return *(new T);
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
    return data[index];
   //return *(new T);
}

/*****************************************************
 * DEQUE : POP_BACK
 *****************************************************/
template <class T>
void deque <T> :: pop_back()
{
}

/*****************************************************
 * DEQUE : POP_FRONT
 *****************************************************/
template <class T>
void deque <T> :: pop_front()
{
}

/******************************************************
 * DEQUE : PUSH_BACK
 ******************************************************/
template <class T>
void deque <T> :: push_back(const T & t)
{
   if (numElements == numCapacity)
   {
      if (numCapacity == 0)         // Give the deque a place to live
      {
         resize(1);
      }        // Grow the array as needed
      else
      resize(numCapacity * 2);      // Give the deque more double space if it's out of space.
   }
   data[iaFromID(numElements++)] = t;      // Place the new element on the end
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t)
{
   if (numElements == numCapacity) {
      if (numCapacity == 0) {      // Give the deque a place to live
         resize(1);
      }
      else
         resize(numCapacity * 2);   // Give the deque more double space if it's out of space.
   }
   int temp = iaFront--;         // iaFront at before 0
   if (temp < 0 ) {
      temp = numCapacity - 1;
   }
   data[iaFromID(temp)] = t;
   numElements++;                   // Increment the number of elements

}
/****************************************************
 * DEQUE :: GROW
 * If the deque is currently empty, allocate to size 2.
 * Otherwise, double the size
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) // - Steve 
{
    /*pseudocode doesn't work
    if (newCapacity > size()) {
        while (newCapacity < size())
            push_back(0);
    } else if (newCapacity < size()) {
        while (newCapacity > size())
            pop_back();
    }*/
    if (newCapacity == 0){
        numCapacity = ++newCapacity;
        data = new T[numCapacity];
        return;
    }

    T* newData = new T[newCapacity];

    int dest = 0;
    for (int i = iaFront; i <= numElements; i++)
        newData[dest++] = data[i];

    numCapacity = newCapacity;
    iaFront = 0;

    delete[]data;
    data = newData;
}

} // namespace custom
