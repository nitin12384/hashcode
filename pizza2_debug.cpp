#include <iostream>
#include <fstream>
using namespace std;


#define SCORE cout<< "------------------------------  \nScore after processing file = "<< score << "  --------------------------------\n" 
#define PIZZA cout << "Pizzas are :" ; \
  					for(int i = 0; i<nPizzaMax ; i++ ) \
  					cout << pizza[i] << " " ; \
  					cout << endl ;
#define PIZZA_IND cout << "Ordered Pizzas Index are :" ; \
  					for(int i = 0; i<nPizza ; i++ ) \
  					cout << pizzaIndex[i] << " " ; \
  					cout << endl ;	
  					
#define PIZZA_M cout << "Pizzas memory location are :" ; \
  					for(int i = 0; i<nPizzaMax ; i++ ) \
  					cout << pizza + i << " " ; \
  					cout << endl ;
#define PIZZA_IND_M cout << "Ordered Pizzas Index memory location are :" ; \
  					for(int i = 0; i<nPizza ; i++ ) \
  					cout << pizzaIndex + i << " " ; \
  					cout << endl ;					

bool dM = 0    ;



int processFile(string name, string outname = "def.out")
{
	
  cout << "--------------  Processing File : " << name << "   --------------\n" ;
  
  ifstream file(name) ;
  
  if(file && dM) cout << "File opened Successfully" << endl;
  
  long int maxSlice ;
  file >> maxSlice ;
  int nPizzaMax; // how many type of pizza
  file >> nPizzaMax ;
  
  int pizza[nPizzaMax] ;
  
  for(int i = 0; i<nPizzaMax ; i++ ) 
  	file >> pizza[i] ;
  
  if(dM) 
  {
  	cout << "input : maxSlice = " << maxSlice << "\nnPizzaMax = " << nPizzaMax << "\n" ;
  
  	PIZZA
  
  }
  
  
  //final result variables
  long int sliceSum = 0 ;
  int nPizza = 0 ;
  int pizzaIndex[nPizzaMax] ;
  
  // calculation
 
  for(int i = nPizzaMax - 1; i >=0; i--) 
  {
  	 
  	 
  	if(dM)
  	{
  		cout << "------------------------Check for i = " << i << "  pizza[i] = " << pizza[i] << endl ;
  		
  		cout << "If we order pizza-" << i <<"(" << pizza[i] << " slices )" <<" then, total slice would be " <<  sliceSum + pizza[i] << endl ;
  		 
  	}
  	// loop through all pizza
  	if (sliceSum + pizza[i] < maxSlice)
  	{
  		//we are going to order this pizza
  		if(dM) cout << "We order it...Slices += " << pizza[i] << endl ;
  		
  		sliceSum += pizza[i] ;
  		pizzaIndex[nPizza] = i ;
  		nPizza++ ;
  		
  		
  	}
  	/*
  	PIZZA
  	PIZZA_IND
  	
  	PIZZA_M
  PIZZA_IND_M
  		*/
  }
  
  /*
  printing ouput var to ouput file
  */
  file.close() ;
  
  ofstream file2(outname ) ;
  cout << "--------------  Generating Ouput File : " << outname << "   --------------\n" ;
  
  if(file2 && dM) cout << "File created Successfully" << endl;
  
  file2 << nPizza <<endl ;
  
  for(int i = 0; i<nPizza ; i++ ) 
  	file2 << pizzaIndex[i] << " " ; 
  
  
  file2.close() ;
  return sliceSum ;
	
}
int main() 
{
  long int score = 0;
  score += processFile("a.in", "a.out") ;
  SCORE ;
  score += processFile("b.in", "b.out") ;
  SCORE ;
  
  score += processFile("c.in", "c.out") ;
  SCORE ;
  score += processFile("d.in", "d.out") ;
  SCORE ;
  score += processFile("e.in", "e.out") ;
  SCORE ;
  
  return 0;
}