#include <iostream>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

int main(int argc, char * argv[]){

  int file_desc;

  if( argc == 1){
    return 0;
  }
  else {
    for ( int i = 1; i < argc; i ++){
        file_desc = open(argv[i], O_RDONLY);
        if( file_desc == -1 ){
            cout << "wcat: cannot open file "<< endl;
            return 1;
        }

        else{
            cout<<"Reading File "<< argv[i]<<endl;
            int temp;
            int traverse = 1;
            char* dynBuffer; // to store the characters that have been read

            do {
                //dynamicall allocate memory for each char 
                dynBuffer = new char[traverse];
                temp = read( file_desc, dynBuffer, traverse);
                write( STDOUT_FILENO, dynBuffer, temp );

                traverse++;

                delete[] dynBuffer;


            } while ( temp > 0);
            close( file_desc );
        }
    }
  }
  return 0;

}