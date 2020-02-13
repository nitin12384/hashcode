#include <iostream>
#include <sstream>

#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Macro anf Constants

#define SCORE cout<< "Total Score is now " << totScore << endl ;

//global var
short int nPhotos; // <= 10,000 
short int nHorPhotos;
short int nSlides;
int totScore = 0 ;

bool dM = 1      ;

//classes

class Photo
{
	public:
	bool isHor ; // 
	short int nTags;  // 1-100
	vector<string> tags; 
	
	// default constructor
	Photo()
	{
		nTags = 0 ;
	}
	
	void addTag(string tag) // constructor
	{
		
		nTags ++ ;	
		tags.push_back(tag) ;
		
	}
	
};



class Slide
{
	public:
	short int photo1; //index 
	short int photo2; // index ... extra var .... how to stop wastage	
	bool isHor;
	
 
	Slide()
	{
		photo2 = -1; // default value
	}
	
	short int interestF(Slide * slide2, Photo * photos) //interest Factor
	{
		short int res = 0;
		return res;
	}
	void print(ofstream file)
	{
		file << photo1 << " "<<photo2 << endl;		
	}
	void swap(Slide * slide2)
	{
		
		// swap all
		isHor = (isHor ^ slide2->isHor ) ^ (slide2->isHor = isHor) ;
		photo1 = (photo1 ^ slide2->photo1) ^ (slide2->photo1 = photo1) ;
		photo2 = (photo2 ^ slide2->photo2) ^ (slide2->photo2 = photo2) ;
		
		
	}
};

void createSlideshow1(Photo *photos, Slide *slideshow)		// create straight Show
{
	short int curIndex = 0;
	bool queue = false;
	short int curQueueIndex ;
	
	for(int i=0; i<nPhotos; i++)
	{
		if( (photos+i)->isHor )
		{
			
			(slideshow + curIndex)->isHor = true;
			(slideshow + curIndex)->photo1 = i ;
			curIndex ++ ;
		}
		else
		{
			if(queue)
			{
				// a slide is in the queue already .....fill that slide with second vertical photo
				(slideshow + curQueueIndex)->photo2 = i ;
				curIndex++ ;
				queue = false ;
			}
			else
			{
				//create a slide and a queue for the vertical photo 
				curQueueIndex = curIndex ;
				(slideshow + curIndex)->isHor = false ;
				(slideshow + curIndex)->photo1 = i ;
				queue = true;
			}
		}
	}
	
	if(dM && curIndex == nSlides) cout << "Succes ! filled the slide \n" ;
	if(dM && curIndex != nSlides) cout << "~~~~~~~~~~~~~~Failure ! couldnt fill the all slides \n" ;
	
	

}

void optimizeScore1(Slide *slideshow, Photo* photos)
{
	int scoreTemp;
	for(int i = 0; i<nSlides-1; i++ )
	{
		//loop for each slide execpt last
		scoreTemp = ( slideshow + i)->interestF( slideshow + i + 1, photos) ;
		for(int j = i+2; j<nSlides; j++)
		{
			// each slide after i indexed slide
			if( ( slideshow + i)->interestF( slideshow + j, photos) > scoreTemp ) 
			{
				scoreTemp = ( slideshow + i)->interestF( slideshow + j, photos)  ;
				
				if(dM) cout << "swapping "<< i + 1 << "th and " << j << "th slide \n"  ;
				
				( slideshow + i + 1)->swap( slideshow + j)  ;
			}
		}
	}
	
	
	
}

int calcScore(Slide* slideshow, Photo* photos)
{
	int score = 0 ;
	for(int i=0; i<nSlides-1; i++)
	{
		score += (slideshow + i)->interestF( slideshow + i + 1 , photos) ;
	}
	
	return score ;
}

void processFile(const char * inpName = "def.in" , const char * outName = "def.out") 
{
	
	cout << "--------------  Processing File : " << inpName << "   --------------\n" ;
  
	ifstream file(inpName) ;
  
	if (! file) cout << "File \" " << inpName << " \" Not Found ........................" ;
	
	file >> nPhotos ; 
	Photo photos[nPhotos] ;// array created
	
	// inp in array
	
	
	stringstream lin ;
	string line;
	string tag;
	
	getline(file, line) ;
	
	char c;
	for(int i=0; i<nPhotos; i++)
	{
		getline(file, line) ;
		if(dM) cout << "Line input is " << line << endl ;
		
		stringstream lin(line) ;
		// isHor
		lin >> c ;
		
		if(c=='H')
		{
			photos[i].isHor = 1;
			nHorPhotos ++ ;
		}
		else
		 	photos[i].isHor = 0 ;
		
		lin >> photos[i].nTags ;
		for(int j=0; j<photos[i].nTags; j++)
		{
			lin >> tag ;
			photos[i].tags.push_back(tag) ;
		}
	}
	
	if(dM)
	{
		cout << " File has nPhotos = " << nPhotos << "\n" ;
		for(int i=0; i<nPhotos; i++)
		{
			cout << "Photo no "<< i <<" \nisHor = " << photos[i].isHor << " nTags is " << photos[i].nTags << " Tags are : \n" ;
			
			for(auto i : photos[i] .tags)
				cout << i << " " ;
				
			cout << endl ;
		}
	}
	
	// input complete
	
	nSlides = nPhotos - (nPhotos - nHorPhotos) / 2 ;
	Slide slideshow[nSlides] ;
	 
	totScore += calcScore(slideshow, photos) ;
	 
}

int main()
{
	
	processFile("a.txt", "a.out") ;
	SCORE;
	 
	 /*
	
	string sr[4] ;
	sr[1] = "123456" ;
	sr[2] = "123451234512" ;
	
	cout << sr[2].size()  ;
	 
	*/
	return 0;
	 
}