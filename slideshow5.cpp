
/*
Algo1 is inefficient
Maybe .... transfer all data of photo array to slides and delete photos array ...?
find better way to use search algorithm
................. or to count common elements
....... or totally new concept ???
.....using dynamic memory allocation for arrays
..... or using advanced data structure ?
... first sort all photo tag vectors (nPhoto times sort )
.... then use binary search
*/



#include <iostream>
#include <sstream>

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Macro and Constants

#define SCORE cout<< "\nTotal Score is now " << totScore << endl<<endl ;
#define MIN(x,y,z) ( (x)<=(y) ) ? ( ( (x)<=(z) ) ? (x) : (z) ) : ( ( (y)<=(z) ) ? (y) : (z) )
#define SWAP(x,y) (x) = (( (x)^(y) )^( (y)==(x) ))

//global var
int nPhotos=0; // <= 100,000
int nHorPhotos=0;
int nSlides=0;
int totScore = 0 ;

bool dM =  1       ;		// debug mode
bool sM = 1    ;  		// signal mode
bool creat1Debug = 1 ;


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

	void addTag(string tag)
	{

		nTags ++ ;
		tags.push_back(tag) ;

	}
	void printDetails()
	{
		if(isHor)
			cout << "Horizontal Photo nTags = " << nTags << endl;
		else
			cout << "Vertical Photo nTags = " << nTags << endl;
	}

};



class Slide
{
	public:
	int photo1; //index
	int photo2; // index ... extra var .... how to stop wastage
	bool isHor;
	short int nTags1;
	short int nTags2;


	Slide()
	{
		photo2 = -1;
		nTags1 = 0 ;
		nTags2 = 0 ; // default value
	}

	short int interestF(Slide * slide2, Photo * photos) ; //interest Factor function declaration

	short int interestF_bin(Slide * slide2, Photo * photos) ; //interest Factor function declaration ... binarysearch
	short int interestF2(Slide * slide2, Photo * photos) ; //interest Factor function declaration ...

	void printToFile(ofstream file)
	{
		if(isHor)
			file << photo1 << endl;
		else
			file << photo1 << " "<<photo2 << endl;
	}
	void printDetails()
	{
		cout << "isHor = "<< isHor << " photo1 = " << photo1 << " photo2 = " << photo2 << " nTags1 = "<< nTags1 << " nTags2 = " << nTags2 << endl;
	}
	void swap(Slide * slide2)
	{

		// swap all
		isHor = (isHor ^ slide2->isHor ) ^ (slide2->isHor = isHor) ;  // XOR swapping
		photo1 = (photo1 ^ slide2->photo1) ^ (slide2->photo1 = photo1) ;
		photo2 = (photo2 ^ slide2->photo2) ^ (slide2->photo2 = photo2) ;
		nTags1 = (nTags1 ^ slide2->nTags1) ^ (slide2->nTags1 = nTags1 ) ;
		nTags2 = (nTags2 ^ slide2->nTags2) ^ (slide2->nTags2 = nTags2 ) ;

	}
};

template <class type>
bool binSearchVector( vector<type> &vect , type search )
{
	if (dM) cout << "Bin Srch Called\n"  ;

	short int first = 0;
	short int last = vect.size() -1 ;
	short int mid = ( first + last )/2  ;

	while (first < last -1 )
	{
		if ( vect[mid] == search )
		{
			// found
			return true ;
		}
		else if (vect[mid] > search  )
		{
			last = mid  ;
		}
		else
		{
			first = mid ;
		}
		mid = ( first + last )/2  ;

	}



	return (search == vect[ first ] || search == vect[last] );
}

void sortPhotoTags(Photo *photos)
{
	if(sM) cout << "Sorting Photo Tags.... \n" ;

	for(int i=0; i<nPhotos; i++)
	{
		if(dM) cout << "Sorting Photo - "<<i<<endl;
		sort(  (photos+i)->tags.begin() , (photos+i)->tags.end() ) ;
	}
}
void createSlideshow1(Slide *slideshow, Photo *photos )		// create straight Show
{

	if(sM) cout << "Creating Straight Slideshow \n" ;
	if(sM) cout << "Slideshow should have nSlides = " << nSlides << endl;

	int curIndex = 0;
	bool queue = false;
	int curQueueIndex ;



	for(int i=0; i<nPhotos; i++)
	{

		if (dM)
		{
			cout << "Processing photo[" << i << "] curIndex = " << curIndex << endl ;

			(photos+i)->printDetails() ;
		}

		if( (photos+i)->isHor )
		{
			if(dM) cout << "Going to be filled in a Hor Slide\n" ;
			(slideshow + curIndex)->isHor = true;
			(slideshow + curIndex)->photo1 = i ;
			(slideshow + curIndex)->nTags1 = (photos+i)->nTags ;

			if(dM) (slideshow + curIndex)->printDetails() ;
			curIndex ++ ;
		}
		else
		{
			if(queue)
			{
				// a slide is in the queue already .....fill that slide with second vertical photo
				if(dM) cout << "Going to be filled in a Queued Ver Slide\n" ;
				(slideshow + curQueueIndex)->photo2 = i ;
				(slideshow + curQueueIndex)->nTags2 = (photos+i)->nTags ;

				if(dM) (slideshow + curQueueIndex)->printDetails() ;

				curIndex++ ;
				queue = false ;
			}
			else
			{
				//create a slide and a queue for the vertical photo
				if(dM) cout << "Going to be filled in a Ver Slide and creating a queue\n" ;
				curQueueIndex = curIndex ;
				(slideshow + curIndex)->isHor = false ;
				(slideshow + curIndex)->photo1 = i ;
				(slideshow + curIndex)->nTags1 = (photos+i)->nTags ;

				if(dM) (slideshow + curIndex)->printDetails() ;
				queue = true;
			}
		}


	}




	if(dM)
	{
		for(int i=0; i<nSlides; i++)
			(slideshow + i)->printDetails();

	}


	if(sM && curIndex == nSlides) cout << "Succes ! filled the slide \n" ;
	if(sM && curIndex != nSlides) cout << "~~~~~~~~~~~~~~Failure ! couldnt fill the all slides curIndex = "<< curIndex <<endl; ;



}

void optimizeScore1(Slide *slideshow, Photo* photos)
{

	if(sM) cout << "Score Optimizer 1 is called ...............\n" ;
	short int scoreTemp;
	short int scoreNew;
	for(int i = 0; i<nSlides-1; i++ )
	{

		//loop for each slide execpt last
		if(dM) cout << "Checking interestF for slide-"<<i<<" >and slide-"<<i+1<<endl;

		scoreTemp = ( slideshow + i)->interestF2( slideshow + i + 1, photos) ;
		for(int j = i+2; j<nSlides; j++)
		{
			if(dM) cout << "Checking interestF for slide-"<<i<<" and slide-"<<j<<endl;

			// each slide after i indexed slide

			scoreNew = ( slideshow + i)->interestF2( slideshow + j, photos) ;
			if( scoreNew > scoreTemp )
			{
				scoreTemp = scoreNew  ;

				if(dM) cout << "swapping "<< i + 1 << "th and " << j << "th slide \n"  ;

				( slideshow + i + 1)->swap( slideshow + j)  ;
			}
		}

		if(sM) cout << "Slide " << i+1 << "successfully optimised\n" ;
	}



}

int calcScore(Slide* slideshow, Photo* photos)
{
	if(dM) cout << "calcScore called \n" ;
	int score = 0 ;
	for(int i=0; i<nSlides-1; i++)
	{
		if(dM) cout << "Checking interestF for slide-"<<i<<" and slide-"<<i+1<<endl;
		score += (slideshow + i)->interestF( slideshow + i + 1 , photos) ;
	}

	return score ;
}

void processFile(const char * inpName = "def.in" , const char * outName = "def.out")
{

	// Take File ********************************

	if(sM) cout << "--------------  Processing File : " << inpName << "   --------------\n" ;

	ifstream file(inpName) ;

	if (! file && sM) cout << "File \" " << inpName << " \" Not Found ........................" ;

	nPhotos = 0;
	nHorPhotos = 0;
	//Input Start **************************************
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
	if(sM) cout << "Input was succesful\n" << "File has nPhotos = " << nPhotos << " and Horizontal Photos = " << nHorPhotos << endl ;

	sortPhotoTags(photos);
	if(dM)
	{

		for(int i=0; i<nPhotos; i++)
		{
			cout << "Photo no "<< i <<" \nisHor = " << photos[i].isHor << " nTags is " << photos[i].nTags << " Tags are : \n" ;

			for(auto j : photos[i] .tags)
				cout << j << " " ;

			cout << endl ;
		}
	}


	// input complete ************************************************
	file.close() ;


	nSlides = nPhotos - (nPhotos - nHorPhotos) / 2 ;

	Slide slideshow[nSlides] ;	 // final slide show
	if(sM) cout << "Final Slideshow Array created of "<<nSlides << " Slide objects \n" ;
	// Create a straight slide show
	createSlideshow1(slideshow, photos) ;
	int scoreNow = calcScore(slideshow, photos) ;
	if(sM) cout << "--------------------\nSlideshow has score = " << scoreNow <<"\n--------------------\n" ;		// Redundant ********

	//optimize via sort
	bool toOptimize = 1;
	if(sM)
	{
		cout << "Want to use Bin Search Optimiser - It may take some while (Enter 1 or 0) " ;
		cin >> toOptimize ;
	}
	if(toOptimize)
	{
		 cout << "what abt dM \n" ;
		 cin >> dM  ;
		 optimizeScore1(slideshow, photos) ;
		 scoreNow = calcScore(slideshow, photos) ;
	 }

	if(sM) cout << "--------------------\nNow Slideshow has score = " << scoreNow << "\n--------------------\n" ;

	totScore += scoreNow;

	if(sM) SCORE ;
}

short int Slide :: interestF(Slide* slide2, Photo* photos)
{

	if(dM) cout << "interestF is called \n" ;
	// interestF = min (s1.tags - s2.tags , s1.tags ^ s2.tags , s2.tags - s1.tags )
	short int nCommonTags = 0;
	string search;
	bool found = 0;
	// ******************* Try to get better algo for counting common tags *********************

	for(int i=0; i<nTags1; i++) // all tags in slide1 and photo1
	{
		search = (photos + photo1)->tags[i] ;		// photos + photo1 -> photo1 in array
		found = 0;

		for(int j=0; j< (slide2->nTags1) ; j++) // all tags of photo1 of slide2
		{
		 	if( search == ( (photos + slide2->photo1)->tags[j] ) )
		 	{
		 		// found a tag of s1 in s2
		 		if(dM) cout << "A Common Tag of photo1 was found in photo1 !! \n" ;
		 		nCommonTags++ ;
		 		found = 1;
		 		break;
		 	}

		}

		if(!(slide2->isHor) && (!found)) // slide 2 is vertical its got more tags and we didn't found our search till yet
		{
			for(int j=0; j< (slide2->nTags2) ; j++) // all tags of photo2 of slide2
			{
			 	if( search == ( (photos + slide2->photo2)->tags[j] ) )
			 	{
			 		// found a tag of s1 in s2
		 			if(dM) cout << "A Common Tag of photo1 was found in photo 2!! \n" ;
			 		nCommonTags++ ;
			 		found = 1;
			 		break;
			 	}

			}
		}
		// searching all common tags of slide1's photo1 in whole slide2 completed
	}


	if( !isHor ) // slide1 has got photo2 also
	{
		for(int i=0; i<nTags2; i++) // all tags in slide1 and photo2
		{
			search = (photos + photo2)->tags[i] ;		// photos + photo2 -> photo2 in array
			found = 0;

			for(int j=0; j< (slide2->nTags1) ; j++) // all tags of photo1 of slide2
			{
			 	if( search == ( (photos + slide2->photo1)->tags[j] ) )
			 	{
			 		// found a tag of s1 in s2
			 		if(dM) cout << "A Common Tag of photo2 was found in photo1 !! \n" ;
			 		nCommonTags++ ;
			 		found = 1;
			 		break;
			 	}

			}

			if(!(slide2->isHor) && (!found)) // slide 2 is vertical its got more tags and we didn't found our search till yet
			{
				for(int j=0; j< (slide2->nTags2) ; j++) // all tags of photo2 of slide2
				{
				 	if( search == ( (photos + slide2->photo2)->tags[j] ) )
				 	{
				 		// found a tag of s1 in s2
			 			if(dM) cout << "A Common Tag of photo2 was found in photo 2!! \n" ;
				 		nCommonTags++ ;
				 		found = 1;
				 		break;
				 	}

				}
			}
		// searching all common tags of slide1's photo1 in whole slide2 completed
		}
	}

	if(dM) cout << "Finally nCommonTags = " << nCommonTags << endl;

	short int res = MIN( (nTags1+nTags2)-nCommonTags, nCommonTags, (slide2->nTags1 + slide2->nTags2)-nCommonTags ) ;

	if(dM) cout << "Finally Interest factor  = " << res << endl ;
	return res;
}


///*****************-*



short int nCommonVector(vector<string> &vect1  ,  vector<string> &vect2 )
{
	if(dM) cout << "nCommonVector is called \n" ;
	short int i=0, j=0 ;
	short int res = 0 ;

	while(i < vect1.size() &&  j <  vect2.size()   )
	{

		if(dM) cout << "Loop for i&j = " << i << "    " << j << "\n" ;

		if ( vect1.at(i)== vect2.at(j)   )
		{
			if(dM) cout <<" A common string found ! \n" ;
			i++;
			j++;
			res++;
		}
		else if ( vect1.at(i) > vect2.at(j)  )
			j++;
		else
			i++;
	}

	return res;
}

//**************

short int Slide :: interestF2(Slide* slide2, Photo* photos)
{

	if(dM) cout << "interestF2 is called \n" ;
	// interestF = min (s1.tags - s2.tags , s1.tags ^ s2.tags , s2.tags - s1.tags )
	short int nCommonTags = 0;

	nCommonTags += nCommonVector((photos + photo1)->tags , (photos + (slide2->photo1))->tags ) ;
	if(! (slide2->isHor)) nCommonTags += nCommonVector((photos + photo1)->tags , (photos + (slide2->photo2))->tags ) ;

	if (! isHor)
    {

        nCommonTags += nCommonVector((photos + photo1)->tags , (photos + (slide2->photo1))->tags ) ;
        if(! (slide2->isHor)) nCommonTags += nCommonVector((photos + photo1)->tags , (photos + (slide2->photo2))->tags ) ;
    }


	if(dM) cout << "Finally nCommonTags = " << nCommonTags << endl;

	short int res = MIN( (nTags1+nTags2)-nCommonTags, nCommonTags, (slide2->nTags1 + slide2->nTags2)-nCommonTags ) ;

	if(dM) cout << "Finally Interest factor  = " << res << endl ;
	return res;
}



//*************

short int Slide :: interestF_bin(Slide* slide2, Photo* photos)
{
	// calculate interest factor with binary search ......... currently buggy !!!!
	if(dM) cout << "interestF_bin is called \n" ;
	// interestF = min (s1.tags - s2.tags , s1.tags ^ s2.tags , s2.tags - s1.tags )
	short int nCommonTags = 0;
	string search;
	bool found = 0;
	// ******************* Try to get better algo for counting common tags *********************

	for(int i=0; i<nTags1; i++) // all tags in slide1 and photo1
	{
		search = (photos + photo1)->tags[i] ;		// photos + photo1 -> photo1 in array
		found = 0;


		if( binSearchVector( (photos + slide2->photo1 )->tags , search )	)
		{
		 		// found a tag of s1 in s2
			if(dM) cout << "A Common Tag of photo1 was found in photo1 !! \n" ;
			nCommonTags++ ;
			found = 1;
			break;
		}



		if(!(slide2->isHor) && (!found)) // slide 2 is vertical its got more tags and we didn't found our search till yet
		{
			if( binSearchVector( (photos + slide2->photo2 )->tags , search )	)
			{
				  //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		 		// found a tag of s1 in s2
				if(dM) cout << "A Common Tag of photo1 was found in photo2  !! \n" ;
				nCommonTags++ ;
				found = 1;
				break;
			}
		}
		// searching all common tags of slide1's photo1 in whole slide2 completed
	}


	if( ! isHor ) // slide1 has got photo2 also
	{
		for(int i=0; i<nTags2; i++) // all tags in slide1 and photo2
		{
			search = (photos + photo2)->tags[i] ;		// photos + photo2 -> photo2 in array
			found = 0;

			if( binSearchVector( (photos + slide2->photo1 )->tags , search )	)
		{
		 		// found a tag of s1 in s2
			if(dM) cout << "A Common Tag of photo2 was found in photo1 !! \n" ;
			nCommonTags++ ;
			found = 1;
			break;
		}



		if(!(slide2->isHor) && (!found)) // slide 2 is vertical its got more tags and we didn't found our search till yet
		{
			if( binSearchVector( (photos + slide2->photo2 )->tags , search )	)
			{
		 		// found a tag of s1 in s2
				if(dM) cout << "A Common Tag of photo2 was found in photo2  !! \n" ;
				nCommonTags++ ;
				found = 1;
				break;
			}
		}
		// searching all common tags of slide1's photo2 in whole slide2 complete
		}
	}

	if(dM) cout << "Finally nCommonTags = " << nCommonTags << endl;

	short int res = MIN( (nTags1+nTags2)-nCommonTags, nCommonTags, (slide2->nTags1 + slide2->nTags2)-nCommonTags ) ;

	if(dM) cout << "Finally Interest factor  = " << res << endl ;
	return res;
}



// function defination ends ........ .......*******************************


int main()
{

    /*
	vector<string> s;
	s.push_back("aba");
	s.push_back("yhaba");
	s.push_back("ina");
	s.push_back("ijaba");
	s.push_back("akoba");


	vector<string> s1  ;
	s1.push_back("aba");
	s1.push_back("yhaba");
	s1.push_back("inka");
	s1.push_back("ihjaba");
	s1.push_back("akoba");



	cout << nCommonVector(s, s1  ) ;



    */

    ofstream file3("123.txt") ;
    file3.close();

	bool next = 1;
	if(sM)
	{
		cout << "\nWant detailed processing analysis(1/0)";
		cin >> dM ;

		cout << "Press 1 to process file a (1KB) and 0 to exit ";
		cin >> next ;
	}
	if(next) processFile("./qualification_round_2019.in/a_example.txt", "a.out") ; // 1 KB

	if(sM)
	{
		 cout << "Press 1 to process next (47KB) and 0 to exit ";
		 cin >> next ;
	}

	if(next) processFile("./qualification_round_2019.in/c_memorable_moments.txt", "c.out") ; // 47 KB

	if(sM  )
	{
		cout << "Press 1 to process next file (3866KB) and 0 to exit ";
		cin >> next ;
	}
	if(next) processFile("./qualification_round_2019.in/d_pet_pictures.txt", "d.out") ; // 3866 KB

	if(sM)
	{
		 cout << "Press 1 to process next file  (6267KB) and 0 to exit ";
		 cin >> next ;
	}
	if(next) processFile("./qualification_round_2019.in/e_shiny_selfies.txt", "e.out") ; // 6267 KB

	if(sM)
	{
		cout << "Press 1 to process next file (8828KB) and 0 to exit ";
		cin >> next ;
	}

	if(next) processFile("./qualification_round_2019.in/b_lovely_landscapes.txt", "b.out") ; // 8828 KB


	 /*

	string sr[4] ;
	sr[1] = "123456" ;
	sr[2] = "123451234512" ;

	cout << sr[2].size()  ;

	*/
	return 0;

}

