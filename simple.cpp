#include<iostream>
#include<stdexcept>
#include<vector>
#include <utility>

using namespace std;

/* A simple allocator that just allocates memory from a pool
 * and does no deallocation whatsoever.
 *
 * Your allocator classes should do both allocation and deallocation.
 * Furthermore, they need to have some means of gathering statistics
 * and recording them to a file.
 */

 void placement_new_demonstration();
class Simple
{
  private:
    static const size_t pool_size = 1024;
    char pool[pool_size];
    size_t first_free;

  public:
    Simple(): first_free(0) {}

    void* alloc(size_t bytes)
    {
      if(first_free + bytes <= pool_size)
      {
        //cout << "Allocating " << bytes << " bytes" << endl;
        size_t allocated = first_free;
        first_free += bytes;
        //cout << "out1 -- " << &pool+allocated << endl;
        //return &pool[allocated];
        return &pool+allocated;
      }
      else
      {
        //cout << "Could not allocate " << bytes << " bytes" << endl;
        throw bad_alloc();
      }
    }

    void dealloc(void* thing)
    {
      //cout << "Deallocating address " << thing << endl;
      // If we did deallocation, the code would go here
    }
};


int main()
{
  // In here, need to run through a trace of allocations and deallocations,
  // then record allocator efficiency stats.
  vector<void*> allocations;
  Simple allocator;

  for(unsigned int i = 0; i < 1000; i++)
  {
    cout << allocations.size() << endl;
    if(allocations.size() == 0 || rand() %2) // Allocate something
    {
      try
      {
        size_t size = rand() % 127 + 1; // Allocate between 1 and 128 bytes
        void* p = allocator.alloc(size);
        //cout << "Current " << size << " bytes - " << p << endl;
        allocations.push_back(p);
        
      }
      catch(const bad_alloc& b) {}
    }
    else // Free something
    {
      size_t to_free = rand() % allocations.size(); // Randomly select something to free
      allocator.dealloc(allocations[to_free]); // Free it
      allocations.erase(allocations.begin() + to_free); // Remove it from our list of allocated blocks
    }
  }
  //placement_new_demonstration();

  // Write statistics out to a CSV file
  return 0;
}

/* BEGIN DIVERSION */
/* The following three functions are needed for the
 * 'placement new' syntax and associated deletes.
 * You do not have to implement them for this assignment,
 * but if you wanted to use your allocator in practice,
 * you would want them.
 */
inline void* operator new(size_t nbytes, Simple& pool)
{
    return pool.alloc(nbytes);
}
inline void operator delete(void* p, Simple& pool)
{
    pool.dealloc(p);
}
template<class T>
inline void destruct(T* p, Simple& pool)
{
  p->~T();
  operator delete(p, pool);
}

void placement_new_demonstration()
{
  Simple s;
  int* x;

  // Just allocate as much memory as we can
  try
  {
    for(int i = 1;;i++)
    {
      // allocation happens in our custom allocator instead of on the heap
      x = new(s) int(i);
      cout << *x << endl;
    }
  }
  catch(const bad_alloc& b)
  {
    cout << "Yup, no good " << b.what() << endl;
  }

  // Instead of calling delete, call destruct
  destruct(x, s);

  // Technically this should leak a bunch of memory,
  // but because our allocator object is deallocated when
  // this function returns, we have no memory leaks!
}

/* END DIVERSION */

