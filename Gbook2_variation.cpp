#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h> 
using namespace std ;

//  Macros

#define SWAP(x,y) (x) = (( (x)^(y) )^( (y)==(x) ))


//global Var
bool dM = 0         ;
bool sM = 1         ;
bool error = 1      ;
int totScore = 0   ;
char stop = 'a' ;



// classes
class Library
{
	public:  // 
	int maxScore;
	int tSU;
	int limPerDay;
	int nBooks;
	int nScanned ;
	int origID ;
	double omRatio;		
	vector<int> bookID ;
	
	Library() // Constructor
	{
		//def values 
		maxScore = 0 ;
		tSU=0 ;
		limPerDay=0 ;
		nBooks=0 ;	
		nScanned=0  ;
		omRatio=0.0 ;	
		origID = 0;
	}
	void printData(bool all = false)
	{
		cout << "nBooks = " << nBooks << "   tSU = " << tSU << " limPerday = " << limPerDay<< "\n"  ; 
		if (all) printf("origID = %d, maxScore = %d, nScanned = %d, omRatio = %f", origID, maxScore, nScanned, omRatio) ;
		
		cout << "IDs of books : \n" ;
		for(int i=0; i<nBooks; i++)
			cout << bookID[i] << " " ;	
		cout << endl ;
	}
	
	void printBookData(short int * bookScores)
	{
		cout << "nBooks = " << nBooks << "\n";
		for(int j=0; j<nBooks; j++)
		{
			cout << "ID - " << bookID[j] << " Score - " << *(bookScores + bookID[j]) << endl ;
		}
	}
	
	void setMaxScore(short int * bookScores)
	{
		if(dM) cout << "setMaxScore called ....\n" ;
		for(int j=0; j<nBooks; j++)
		{
			maxScore += *(bookScores + bookID[j] ) ;
		}
		if(dM) cout << "MaxScore was set = " << maxScore << " \n" ;
	}
	
	void setOmRatio()
	{
		if(dM) cout << "setOmRatio called ....\n" ;
		omRatio = maxScore;
		
		omRatio /=    (double)(tSU + nBooks/limPerDay + (nBooks%limPerDay==0 ? 0 : 1) )  ;
		
		
		if(dM) cout << "omRatio was set = " << omRatio << " \n" ;
	}
	
	void sortBookID_bubble(short int * bookScores)
	{
		if (dM) 
		{
			cout <<"  sortBookID_bubble called (descending order) \n " ;
			printBookData(bookScores) ;
		}
		
		int temp = 0  ;
		for(int i=0; i<nBooks-1 ; i++)
		{
			for(int j=0; j<nBooks - i - 1; j++)
			{
				if ( *(bookScores + bookID[j] ) <     *(bookScores + bookID[j+1] )  )
				{
					
			//1		SWAP(bookID[j], bookID[j+1]) ;
					temp = bookID[j+1] ;
					bookID[j+1] = bookID[j] ;
					bookID[j] = temp ;
				}
			}
		}
		
		if (dM) 
		{
			cout <<"  After sortBookID_bubble  (descending order) \n " ;
			printBookData(bookScores) ;
		}
	}
	
};


//functions 

void sortAccOmRatio_bubble(Library * libraries,int nLibs)
{
	if (dM) 
		{
			cout <<"  sortAccOmRatio_bubble called (descending order) \n " ;
			
		}
		
		Library temp;
		for(int i=0; i<nLibs-1 ; i++)
		{
			if(sM) cout << "Library " << i << " being placed \n" ;
			for(int j=0; j<nLibs - i - 1; j++)
			{
				if ( (libraries + j)->omRatio < (libraries + j + 1)->omRatio  )
				{
					
			//1		SWAP lib j and j+1  ;
					if(dM) cout << "Swapping Lib " << i << " & " << j << endl ;
					temp = *(libraries + j ) ;
					*(libraries + j ) = *(libraries + j +1 ) ;
					*(libraries + j +1 ) = temp ;
				}
			}
		}
		
}

void sortAccMaxScore_bubble(Library * libraries,int nLibs)
{
	if (dM) 
		{
			cout <<"  sortAccMaxScore_bubble called (descending order) \n " ;
			
		}
		
		Library temp;
		for(int i=0; i<nLibs-1 ; i++)
		{
			if(sM) cout << "Library " << i << " being placed \n" ;
			for(int j=0; j<nLibs - i - 1; j++)
			{
				if ( (libraries + j)->maxScore < (libraries + j + 1)->maxScore )
				{
					
			//1		SWAP lib j and j+1  ;
					if(dM) cout << "Swapping Lib " << i << " & " << j << endl ;
					temp = *(libraries + j ) ;
					*(libraries + j ) = *(libraries + j +1 ) ;
					*(libraries + j +1 ) = temp ;
				}
			}
		}
		
}

void sortAccTSU_bubble(Library * libraries,int nLibs)
{
	if (dM) 
		{
			cout <<"  sortAccTSU_bubble called (descending order) \n " ;
			
		}
		
		Library temp;
		for(int i=0; i<nLibs-1 ; i++)
		{
			if(sM) cout << "Library " << i << " being placed \n" ;
			for(int j=0; j<nLibs - i - 1; j++)
			{
				if ( (libraries + j)->tSU > (libraries + j + 1)->tSU )
				{
					
			//1		SWAP lib j and j+1  ;
					if(dM) cout << "Swapping Lib " << i << " & " << j << endl ;
					temp = *(libraries + j ) ;
					*(libraries + j ) = *(libraries + j +1 ) ;
					*(libraries + j +1 ) = temp ;
				}
			}
		}
		
}

void processFile(string inpName, string outName)
{
	static char file = 'a' ;
	file ++ ;
	// Input from FIle
	cout << "Processing File " << inpName << "\n" ;
	
	ifstream inpFile(inpName) ;
	
	if(! inpFile)
	{
	 	cout << "~~~Error~~~~Could not open the file " << inpName << "\n" ;
	 	stop = getchar() ;
	 	stop = getchar() ;
	 	return ;
	}
	// INPUT DATA ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(sM) cout << "Inputting Data ...............\n" ;
	
	int nBooks=0, nLibs = 0, nDays=0, today=0 ;
	inpFile >> nBooks >> nLibs >> nDays ;
	if(sM) printf("nBooks = %d, nLibs = %d, nDays = %d \n",nBooks, nLibs, nDays) ;
	
	short int bookScores[nBooks] ;
	bool isScanned[nBooks] ;
	for(int i=0; i<nBooks; i++)
	{
		isScanned[i] = false ;
		inpFile >> bookScores[i] ;
	}
	Library libraries[nLibs] ;

	if(sM) cout << nLibs << " Library objects Created Succesfully .....\n" ;
	int temp = 0 , count = 0 ; // for libraries books id input
	for(int i=0; i<nLibs; i++)
	{
		count = 0;
		inpFile >> libraries[i].nBooks >> libraries[i].tSU >> libraries[i].limPerDay ;
		libraries[i].origID = i ;
		for(int j=0; j< libraries[i].nBooks ; j++ )
		{
			inpFile >> temp;
			libraries[i].bookID.push_back(temp) ;
			count ++ ;		
		}
		if( count != libraries[i].nBooks && error)
		{	
			cout << "~~~~~Error~~~~~~~ For Library - " << i << "nBooks = " << libraries[i].nBooks << " But we filled only "<< count << " bookID \n"	;
			stop = getchar() ;		
			stop = getchar() ;	
		}
	}
	// Input Complete
	inpFile.close() ;	
	if(sM) cout << "Input Completed ................. \n" ;		
	
	if(dM)
	{
		
		cout << ".. Scores of Books - \n" ;
		for(int i=0; i<nBooks; i++)
			cout << bookScores[i] << " " ;
		cout << endl ;
		
		for(int i=0; i<nLibs; i++)
		{
			cout << "For Library - " << i << endl ;
			libraries[i].printData() ;
		} 
	}
	
	// Processing of Data
	
	if(dM)
	{
		//  stoping point
		cout << "Next......Setting Max Scores  " ;
		stop = getchar() ;
		stop = getchar() ;
	}
	
	for (int i=0; i<nLibs; i++)
		libraries[i].setMaxScore(bookScores) ;
		
	if(dM)
	{
		//  stoping point
		cout << "Next......Setting omRatio " ;
		stop = getchar() ;
		stop = getchar() ;
	}
	
	for (int i=0; i<nLibs; i++)
		libraries[i].setOmRatio() ;
	

	
	if(dM)
	{
		//  stoping point
		cout << "Next......Sorting bookId in all libraries " ;
		stop = getchar() ;
		stop = getchar() ;
	}
	
	for (int i=0; i<nLibs; i++)
	{
		libraries[i].sortBookID_bubble(bookScores) ;
		if(sM) cout << "Sorting BookID for Library - " << i << endl;
	}
	
	// Final Signup
	
	if(sM)
	{
		//  stoping point
		cout << "Press any key to .....Sort Acc om r" ;
		stop = getchar() ;
		stop = getchar() ;
	}
	
	if(dM)
	{
		cout << "Initially \n" ;
		for(int i=0; i<nLibs; i++)
		{
			cout << "Library - " << i << " OmRatio - " << libraries[i].omRatio << endl ;
		}
	}
	
	
	
	sortAccOmRatio_bubble(libraries, nLibs) ;
	
	if(dM)
	{
		cout << "Finally \n" ;
		for(int i=0; i<nLibs; i++)
		{
			cout << "Library - " << i << " OmRatio - " << libraries[i].omRatio << endl ;
		}
	}
	
	
	if(sM)
	{
		cout << "Press any key to sign up libraries \n" ;
		stop = getchar() ;
		stop = getchar() ;
	}
	int nLibSU = 0 ;
	today = 0;
	unsigned long long int tempNScanned = 0 ;
	
	for(int i=0; i<nLibs; i++)
	{
		if (today + libraries[i].tSU < nDays)
		{
			if(dM) cout << "Library " << libraries[i].origID << " will be signed up having tSU = " << libraries[i].tSU << endl ;
			nLibSU ++ ;
			today+= libraries[i].tSU ;
			if(dM) cout << "Now Day - " << today << " started   -   " << nDays - today + 1 << "*24 hours left \n" ;
			// means day no taday has started now
			// Signed it up 
			
			// Scanning days are nDays - (today + 1)
			tempNScanned= (nDays - today + 1 ) * libraries[i].limPerDay ;  // max possible books can be scanned
			
			if(dM) 
			{
				cout << "(nDays - today + 1 ) = " <<(nDays - today + 1 ) << "libraries[i].limPerDay = " << libraries[i].limPerDay << endl ;
				cout << "tempNScanned = " <<tempNScanned << " nBooks = " <<libraries[i].nBooks << endl;
			}
			
			if (tempNScanned > libraries[i].nBooks )
				libraries[i].nScanned = libraries[i].nBooks ;
			else
				libraries[i].nScanned = tempNScanned ;
					
			if(dM) cout << "Library " << libraries[i].origID << " will scan " << libraries[i].nScanned << " books - having nBooks = " << libraries[i].nBooks <<" limPerDay = " << libraries[i].limPerDay << endl ;
					
			
			
		}
		else
		{
			break ;
		}
	}
	
	if(sM) cout << nLibSU << " Libraries will be signed up \n" ;
	if (dM) cout << "today & nDays = " << today << "  " << nDays << endl ;
	
	if(dM)
	{
		//  stoping point
		cout << "Next......" ;
		stop = getchar() ;
		stop = getchar() ;
	}																	
																																																				
	// Ouput Writing
	if(sM) cout << "Generating Output Files ......\n " ;
	ofstream outFile(outName) ;
	if(! outFile)
	{
	 	cout << "~~~Error~~~~Could not create the file " << outName << "\n" ;
	 	stop = getchar() ;
	 	stop = getchar() ;
	 	return ;
	}
	

	outFile << nLibSU << endl;
	for(int i=0; i<nLibSU; i++)
	{
		outFile << libraries[i].origID << " " << libraries[i].nScanned << endl;
		for(int j=0; j<libraries[i].nScanned; j++)
		{
			outFile << libraries[i].bookID[j] << " " ;
		}
		outFile << endl ;
	}
	
	outFile.close() ;																								
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{


	cout << "Debug Mode(0/1)  and sM (0/1) \n" ;
	cin >> dM ;
	cin >> sM ;

	
	bool next = 1;
	
	if(sM)
		{
			cout << "Process first File(0.047MB) or Not \n";
			cin >> next  ;
		}
	if(next) processFile("a.txt", "a_out.txt") ;	
	
	if(sM)
	{
		cout << "Process Next File(0.9MB) or Not \n";
		cin >> next  ;
	}

	if(next) processFile("b.txt", "b_out.txt") ;
	if(sM)
	{	
		cout << "Process Next File(1.4MB) or Not \n";
		cin >> next  ;
	}
	if(next) processFile("c.txt", "c_out.txt") ;
	if(sM)
	{
		
		cout << "Process Next File(1.7MB) or Not \n";
		cin >> next  ;
		
	}

	if(next) processFile("d.txt", "d_out.txt") ;
	if(sM )
	{
		cout << "Process Next File(3.1MB) or Not \n";
		cin >> next  ;
	}
	if(next) processFile("e.txt", "e_out.txt") ;
	if(sM)
	{
		
		
		cout << "Process Next File(3.2MB) or Not \n";
		cin >> next  ;
		
	}
	
	if(next)
	{
		processFile("f.txt", "f_out.txt") ;
	}
	
	
	
	return 0;
}