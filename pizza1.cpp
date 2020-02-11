#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
	string line;
  ifstream MyFile("e.in");
  

hile ( getline (MyFile, line) ) {
   cout << line << '\n';
  }
  MyFile.close();
  
  //input variable
  long int maxSlice ;
  int nPizzaMax; // how many type of pizza
  int pizza[numPizza] ;
  
  //final result variables
  long int sliceSum = 0 ;
  int nPizza = 0 ;
  int pizzaIndex[nPizza] ;
 
  /*
  input goes here
  
  */
  
  for(int i = nPizzaMax - 1; i >=0; i--) 
  {
  	// loop through all pizza
  	if (sliceSum + pizza[i] < maxSlice)
  	{
  		//we are going to order this pizza
  		sliceSum += pizza[i] ;
  		pizzaIndex[nPizza] = i ;
  		nPizza++ ;
  		
  	}
  }
  
  /*
  print ouput var to ouput file
  */
  return 0;
}