#include<iostream>
#include<stdexcept>
#include<forward_list>
#include<list>
#include<tuple>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
  char t[10];
  void* yo = t;
  cout << (void*)&t[0] << endl << (void*)((char*)yo + 16) << endl;
  return 0;
}

