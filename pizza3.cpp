#include <iostream>
#include <fstream>
using namespace std;

#define SCORE cout<< "------------------------------  \nScore after processing file = "<< score << "  --------------------------------\n" 

long int score = 0 ;
void processFile(string name, string outname = "def.out")
{
	
  cout << "--------------  Processing File : " << name << "   --------------\n" ;
  
  ifstream file(name) ;
  
  long int maxSlice ;
  file >> maxSlice ;
  int nPizzaMax; // how many type of pizza
  file >> nPizzaMax ;
  
  int pizza[nPizzaMax] ;
  
  for(int i = 0; i<nPizzaMax ; i++ ) 
  	file >> pizza[i] ;
  
  //final result variables
  long int sliceSum = 0 ;
  int nPizza = 0 ;
  int pizzaIndex[nPizzaMax] ;
  
  // calculation
 
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
  printing ouput var to ouput file
  */
  file.close() ;
  
  ofstream file2(outname ) ;
  cout << "--------------  Generating Ouput File : " << outname << "   --------------\n" ;
  file2 << nPizza <<endl ;  
  
  for(int i = 0; i<nPizza ; i++ ) 
  	file2 << pizzaIndex[i] << " " ; 
  
  file2.close() ;
  score += sliceSum ;
  SCORE ;
}
int main() 
{
  
  processFile("a.in", "a.out") ;
  processFile("b.in", "b.out") ;
  processFile("c.in", "c.out") ; 
  processFile("d.in", "d.out") ;
  processFile("e.in", "e.out") ;
 
  return 0;
}