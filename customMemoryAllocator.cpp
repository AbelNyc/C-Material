
#include <iostream>
#include <vector>
#include <cstddef> 

using namespace std;
class CustomMemoryAllocator{
  size_t blockSize;
  size_t numBlocks;

  vector<bool> used;


  char* memoryPool;

  public: 
        CustomMemoryAllocator(size_t block_size, size_t numBlocks)
  : blockSize(block_size), numBlocks(numBlocks), used(numBlocks,false) {

      memoryPool = new char[numBlocks * blockSize];

      cout<<"Memory allocated: "<< memoryPool << endl;
  }

  void* allocate(){
    for ( size_t i = 0; i < numBlocks; i++){
        if(!used[i]){
            used[i] = true;

            cout<<"Allocated block "<< i << endl;

            return memoryPool + ( i * blockSize);

        }
    }
    throw bad_alloc();
  }

  void deallocate(void* ptr){
      if( ptr== nullptr){
        return;
      }

      ptrdiff_t index = (static_cast<char*>(ptr) - memoryPool )/ blockSize;

      if( index >= 0 && index < static_cast<ptrdiff_t> (numBlocks)){
        if(used[index]){
            used[index] = false;
           std::cout << "Deallocated block " << index << std::endl;

        }
        else{
            std::cerr << "Error: Double free detected at block " << index << "!" << std::endl;
        }
      }
      else{
        std::cerr << "Error: Attempt to deallocate an invalid pointer!" << std::endl;
      }
  }

};

int main(){

    CustomMemoryAllocator allocator(5,32);

    void* ptr1 = allocator.allocate();
    void* ptr2 = allocator.allocate();


    allocator.deallocate(ptr2);

    int x;

    allocator.deallocate(&x);




}