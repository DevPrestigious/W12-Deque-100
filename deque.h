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
 *    Alexander Dohms, Stephen Costigan
 ************************************************************************/

#pragma once

// Debug stuff
#include <cassert>


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
   ~deque()
   { 
   }

   //
   // Assign
   //
   deque<T> & operator = (const deque <T> & rhs);

   //
   // Iterator
   //
   class iterator;
   iterator begin() { return iterator(); }
   iterator end()   { return iterator(); }

   //
   // Access - Shaun
   //
   T& front();
   T& back();
   const T & front() const;
   const T & back()  const;
   const T & operator[](size_t index) const; // Steve
         T & operator[](size_t index); // Steve

   // 
   // Insert - Alex
   //
   void push_front(const T& t);
   void push_back(const T& t);

   //
   // Remove - Jon
   //
   void clear()
   { 
   }
   void pop_front();
   void pop_back();

   // 
   // Status
   //
   size_t size() const { return numElements; }
   bool empty() const  { return numElements > 0; }

   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
   // fetch array index from the deque index - Shaun
   int iaFromID(int id) const
   {
      return -99;
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
   iterator()
   {
   }
   iterator(custom::deque<T> *pDeque, int id)
   {
   }
   iterator(const iterator& rhs)
   {
   }

   //
   // Assign
   //
   iterator& operator = (const iterator& rhs)
   {
      return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator& rhs) const { return true; }
   bool operator != (const iterator& rhs) const { return true; }

   // 
   // Access
   //
   const T & operator * () const
   {
      return *(new T);
   }
   T& operator * () 
   {
      return *(new T);
   }

   // 
   // Arithmetic
   //
   int operator - (iterator it) const
   {
      return 99;
   }
   iterator& operator += (int offset)
   {
      return *this;
   }
   iterator& operator ++ ()
   {
      return *this;
   }
   iterator operator ++ (int postfix)
   {
      return *this;
   }
   iterator& operator -- ()
   {
      return *this;
   }
   iterator  operator -- (int postfix)
   {
      return *this;
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
    numCapacity = rhs.numCapacity;
    numElements = rhs.numElements;
    iaFront = rhs.iaFront;
    data = new T[numCapacity];
    if (numElements > 0)
        for (int i = 0; i < numElements; i++)
            data[i] = rhs.data[i];
   
   //*this = rhs;
}


/****************************************************
 * DEQUE : ASSIGNMENT OPERATOR
 ***************************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
   return *this;
}


/**************************************************
 * DEQUE :: FRONT
 * Fetch the item that is at the beginning of the deque
 *************************************************/
template <class T>
const T & deque <T> :: front() const 
{
   return *(new T);
}
template <class T>
T& deque <T> ::front()
{
   return *(new T);
}

/**************************************************
 * DEQUE :: BACK
 * Fetch the item that is at the end of the deque
 *************************************************/
template <class T>
const T & deque <T> :: back() const 
{
   return *(new T);
}
template <class T>
T& deque <T> ::back()
{
   return *(new T);
}

/**************************************************
 * DEQUE :: SUBSCRIPT
 * Fetch the item in the deque
 *************************************************/
template <class T>
const T& deque <T> ::operator[](size_t index) const
{
   return *(new T);
}
template <class T>
T& deque <T> ::operator[](size_t index)
{
   return *(new T);
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
}

/******************************************************
 * DEQUE : PUSH_FRONT
 ******************************************************/
template <class T>
void deque <T> :: push_front(const T & t) 
{
}

/****************************************************
 * DEQUE :: GROW
 * If the deque is currently empty, allocate to size 2.
 * Otherwise, double the size
 ***************************************************/
template <class T>
void deque <T> :: resize(int newCapacity) // - Steve 
{
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
