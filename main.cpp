#include <ctime>
#include <cmath>
#include <map>
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <utility>
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
  int free_space;
  map<void*,int> 
  vector< pair<int,int> > record;

  int getFreeSpaceAmount(int pos){
    int count=0;
    while(pool[pos+count]==' '){
      count++;
    }
    return count;
  }

  bool isTheBest(int min_bound,int max_bound,int n){ //[min_bound,max_bound)
    if(n>=min_bound && n<max_bound){
      return true;
    }
    return false;
  }

  void fill(int start,int amount){
    for(int i=0;i<amount;i++){
      pool[start+i]='@';
    }
  }

  void insertRecord(int position,int amount){
    fill(position,amount);
    pair<int,int> tmp (position,amount);
    record.push_back(tmp);
  }
  void deleteRecord(int position){}
public:
  BestFit(): free_space(pool_size) {
    for(int i=0;i<pool_size;i++){
      pool[i] = ' ';
    }
  }

  void* alloc(size_t bytes){
    int best = INT_MAX;
    int ideal_pos = -1;
    for(int i=0;i<pool_size;i++){
      int count = 0;
      if(pool[i]!=' '){
        int freeSpace = getFreeSpaceAmount(i);
        if(isTheBest(bytes,best,freeSpace))
          ideal_pos = i;
        i += freeSpace;
      }
    }
    if(ideal_pos>=0){
      free_space -= bytes;
      cout << "Allocating " << bytes << " bytes" << endl;
      insertRecord(ideal_pos,bytes);
      return &pool+ideal_pos;
    }
    else{
      cout << "Could not allocate " << bytes << " bytes" << endl;
      throw bad_alloc();
    }
  }

  void dealloc()
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


  cout << clock.getElapsed() << endl;
  return 1;
}

