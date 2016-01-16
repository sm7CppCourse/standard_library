#include <iostream>

#include <string>
#include <iostream>

using namespace std;

extern void testSTL_CppClassic();
extern void testSTL_Cpp11();
extern void concurrency_Cpp11(); 

int main()
{
   cout << "--- STL C++ 03: ---" << endl;
   testSTL_CppClassic();     
    
   cout << "\n\n--- STL C++ 11: ---" << endl;
   testSTL_Cpp11(); 
   
   //cout << "\n\n--- Concurrency C++ 11: ---" << endl;
   //concurrency_Cpp11();     

   return 0;
}

