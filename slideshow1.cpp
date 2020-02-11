#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//global var
short int nPhoto; // <= 10,000
short int nHorPhotos;
short int nSlide;

bool dM ;

//classes

class Photo
{
	public:
	bool isHor ; // 
	short int nTags;  // 1-100
	vector<string> tags; //	string tags[nTags];can it be sort of used .... or vector last option
	Photo(short int n, string* tag, bool isH = true) // constructor
	{
		isHor = isH ;
		nTags = n;
		for(int i=0; i<n; i++)
		{
			tags[i] = *(tag + i) ;
		}
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
	
	short int interestF(Slide * slide2) //interest Factor
	{
		
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

int createSlideshow1(Photo *photos, Slide *slideshow)		// create straight Show
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
	
	if(dM && curIndex == nSlide) cout << "Succes ! filled the slide \n" ;
	if(dM && curIndex != nSlide) cout << "~~~~~~~~~~~~~~Failure ! couldnt fill the all slides \n" ;
	
	// calculate score
	
	int score = 0 ;
	for(int i=0; i<curIndex-1; i++)
	{
		score += (slideshow + i)->interestF( slideshow + i + 1 ) ;
	}
	
	return score ;
}

int optimizeScore1(Slide *slideshow)
{
	int scoreTemp;
	for(int i = 0; i<nSlide-1; i++ )
	{
		//loop for each slide execpt last
		scoreTemp = ( slideshow + i)->interestF( slideshow + i + 1) ;
		for(int j = i+2; j<nSlide; j++)
		{
			// each slide after i indexed slide
			if( ( slideshow + i)->interestF( slideshow + j) > scoreTemp ) 
			{
				scoreTemp = ( slideshow + i)->interestF( slideshow + j)  ;
				if(dM) cout << "swapping "<< i + 1 << "th and " << j "th slide \n"  ;
				( slideshow + i + 1)->swap( slideshow + j)  ;
			}
		}
	}
	
	
	int score = 0 ;
	for(int i=0; i<nSlide-1; i++)
	{
		score += (slideshow + i)->interestF( slideshow + i + 1 ) ;
	}
	
	return score ;
}


int main()
{
	
	//Photo photos[nPhoto] ;// array 
	
	string sr[4] ;
	sr[1] = "123456" ;
	sr[2] = "123451234512" ;
	
	cout << sr[2].size()  ;
	 
	nSlide = nPhotos - (nPhotos - nHorPhotos) / 2 ;
	 //Slide slideshow[nSlide] ;
	 
	 int score = 0 ; // we have to max the score
	 
	 score += slideshow[ i ].interstF( &slideshow[ i+1] ) ;
	 
}