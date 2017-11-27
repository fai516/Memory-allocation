#include <ctime>
#include <cmath>
#include <map>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;


/*
Best fit: the region that has closest size (must equal or larger than) <--scan the whole pool
First fit: the first region have the fit size from begining <--not need to be scan the rest, find the first fit
Next fit: the first regin have the fit size starting from the last allocation
*/

/*
Note:
1.How to make the upcoming process random in size and end time:
  -random in whether either alloc or delloc will decide end time
    -if [vector].size == 0 OR rand() % 2 == 0 {even number} => alloc
    -otherwise delloc

2. how to do opperation in HEX?

*/
class Clock{
  clock_t begin;
public:
  Clock(){}
  inline void start(){
    begin=clock();
  }
  double getElapsed(){
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    return elapsed_secs* pow(10,3);
  }
};

class BestFit{
  static const size_t pool_size=1024;
  char pool[pool_size];
  map<void*,int> memory_map;
  vector<int> region_size;

  size_t first_free;
public:
  void* alloc(size_t bytes){
    if(first_free + bytes <= pool_size){
      cout << "Allocating " << bytes << " bytes" << endl;
      size_t allocated = first_free;
      first_free += bytes;
      cout << "out1 -- " << &pool[allocated] << endl;
      return &pool[allocated];
    }
    else{
      //cout << "Could not allocate " << bytes << " bytes" << endl;
      throw bad_alloc();
    }
  }

  void dealloc(void* thing)
  {
    cout << "Deallocating address " << thing << endl;
    // If we did deallocation, the code would go here
  }
};

class FirstFot{
  static const size_t pool_size=1024;
  char pool[pool_size];
};

class NextFit{
  static const size_t pool_size=1024;
  char pool[pool_size];
};




int main() {
  using namespace std;
  Clock clock;
  clock.start();

  char a = 'a';
  char b = 'b';
  char *p = &a;
  char *q = &b;
  cout << &p << endl << &q << endl;
  cout << "gg" << __SIZEOF_POINTER__ << "gg" << endl;

  cout << clock.getElapsed() << endl;
  return 1;
}

