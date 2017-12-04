#include<iostream>
#include<stdexcept>
#include<vector>
#include<utility>
#include<cmath>
#include<ctime>
#include<thread>
using namespace std;



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

struct fLocator{ //Linked list
  void* address;
  size_t size;
  fLocator* next;
  fLocator* prev;
public:
  fLocator(void* ad,size_t s,fLocator* n,fLocator* p): address(ad),size(s),next(n), prev(p) {}
  void print(){
    cout << address << endl
        << size << endl;
  }
  bool removeRelation(){
    if(this->next!=NULL && this->prev!=NULL){
      fLocator* prev_obj = this->prev;
      fLocator* next_obj = this->next;
      prev_obj->next = this->next;
      next_obj->prev = this->prev;
      return true;
    }
    else if(this->next==NULL){
      this->prev->next = NULL;
      return true;
    }
    else if(this->prev==NULL){
      this->next->prev = NULL;
      return true;
    }
    else{
      this->size = 0;
      return false;
    }
  }
  fLocator* addNext(void* ad,size_t s){
    fLocator* tmp = new fLocator(ad,s,this->next,this);
    if(this->next!=NULL){
      this->next->prev = tmp;
    }
    this->next = tmp;
    return tmp;
  }
  fLocator* addPrev(void* ad,size_t s){
    fLocator* tmp = new fLocator(ad,s,this,this->prev);
    if(this->prev!=NULL){
      this->prev->next = tmp;
    }
    this->prev = tmp;
    return tmp;
  }
};

struct pLocator{
  void* address; //starting address of a process
  size_t size;     //amount of memory the process used in byte
  fLocator* prev_free; //the previous free space
public:
  pLocator(void* ad,size_t s,fLocator* prev): address(ad),size(s),prev_free(prev){}
};

pLocator* alloc(size_t bytes,fLocator* target_address){
  if(target_address!=NULL){
    pLocator* out = new pLocator(target_address,bytes,target_address->prev);
    if(bytes == target_address->size){
      //delete target
      if(target_address->removeRelation()){
        delete target_address;
      }
    }
    else{
      //adjust size and address
      target_address->size -= bytes;
      target_address->address = (void*)((char*)out->address+out->size);
    }
    return out;
  }
  else{
    cout << "Could not allocate " << bytes << " bytes" << endl;
    throw bad_alloc();
  }
}

void dealloc(pLocator* thing,fLocator* fStart){
  //begin address
  //end address+size <--free space
  void* start = thing->address;
  void* end = (void*)((char*)start + thing->size);

  fLocator* tmp = fStart;
  fLocator* result = NULL;
  while(tmp!=NULL){ //iterate the fLocator linked-list
    if(tmp->address == end){
      result = (fLocator*) end;
      break;
    }
    tmp = tmp->next;
  }
  
  if(result!=NULL){//the next of the process is a free space [?X*...]
    if(thing->prev_free != NULL){ // [*?X*...]
      if(thing->prev_free->address == start){ //sticking, merge 2 free space
        
      }
      else{ 
        
      }
    }
    else{// [X*...] or more X
      result->size += thing->size;
      result->address = thing->address;
    }
  }
  else{//the next of the process space is not free space => A)end of the pool, or B)begin of other process
    //could find free space obj
  }
}


class BestFit{
  static const size_t pool_size = 1024;
  char pool[pool_size];
  //vector< pLocator* > pLocators;
  fLocator* fLocators;
public:
  BestFit(){
    cout << (void*)pool << endl;
    fLocators = new fLocator(&pool,pool_size,NULL,NULL);
  }
  pLocator* alloc(size_t bytes){
    fLocator* tmp=fLocators;
    int min = pool_size;
    fLocator* target_address = NULL;
    while(tmp==NULL){
      int target = bytes-tmp->size;
      if(target>=0 && target<min){
        min = tmp->size;
        target_address = tmp;
      }
      tmp = tmp->next;
    }
  }



};

class FirstFit{
  static const size_t pool_size=1024;
  char pool[pool_size];
  fLocator* fLocators;
public:
  FirstFit(){
    cout << (void*)pool << endl;
    fLocators = new fLocator(&pool,pool_size,NULL,NULL);
  }
  pLocator* alloc(size_t bytes){
    fLocator* tmp=fLocators;
    fLocator* target_address = NULL;
    int target=-1;
    while(target<0){
      target=bytes-tmp->size;
      tmp=tmp->next;
    }
    target_address=tmp;
    
  }


};

class NextFit{
  static const size_t pool_size=1024;
  char pool[pool_size];
  fLocator* fLocators;
  fLocator* LastPosition;
public:
  NextFit(){
    cout << (void*)pool << endl;
    fLocators = new fLocator(&pool,pool_size,NULL,NULL);
  }
  pLocator* alloc(size_t bytes,fLocator* LastPosition){
    fLocator* tmp=LastPosition;
    fLocator* target_address = NULL;
    int target=-1;
    while(target<0){
      target=bytes-tmp->size;
      tmp=tmp->next;
    }
    target_address=tmp;
  }
};

int main(){
  BestFit instance;

  //cout << (void*)(&c[30]) << endl << (void*)(&c[0]) << endl;
  //cout << ((&c[30]-&c[0])*sizeof(char)) << endl;
  return 0;
}