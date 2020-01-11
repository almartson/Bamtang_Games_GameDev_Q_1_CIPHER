/******************************************************************************
	Bamtang Games Entrance Test.

	Question number 1.
	1. CIPHER

	[Spanish original Question:]

		Desencripta el siguiente mensaje... ( _myOriginalMessage )

		Implementar la función: decryptMessage( message, freqLang )

		* Tu programa debe imprimir el texto desencriptado en pantalla.
		* No uses archivos ni pidas ingresar datos.
		* Mantener las mayúsculas y minúsculas del mensaje, así como los saltos de linea.

*******************************************************************************/

#include <iostream>
/////#include <bits/stdc++.h>     // C++ program to convert whole string to: uppercase or lowercase using STL. //AND// Sort an array according to other using pair in STL. // Not to use in Visual Studio C++, only in G++ GCC in Linux.
//
#include <string>
#include <algorithm>

using namespace std;


//********************HARDCODED CONSTANTS************************//

const string _myOriginalMessage = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";


const string _freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";

//End of********************HARDCODED CONSTANTS************************//


// SOLUTION:   THE ALGORTIHM:

/*1-*************************************************/

/*** 
1-  Discover HOW MANY DIFFERENT CHARACTERS are there in the Message: get the Char Count (an int): 
OBS: 1- IGNORE CASE.

RETURNS: The Chars Count.
**/
void CountHowManyCharsAtoZ( const string message, string* charListNotSorted, size_t* myCharsAtoZCount )
{

	// Auxiliar:
	//
	size_t auxACharOcurrencesCount = 0;

	// Initialize the Char List:  
	//
	(*charListNotSorted) = "";


	// Go through the Loop in each char of the STRING 'charListNotSorted', and check IF IT IS SORTED.
	//
	size_t messageLength = message.size();
	//
	for (size_t i = 0; i < messageLength; i++)
	{

		// Check to see if it is EMPTY:
		//
		if ((*charListNotSorted) == "")
		{


			if ( (message[ i ] >= 'a') && (message[ i ] <= 'z') )
			{

				(*charListNotSorted) += message[i];

			}//End if  if ((message[ i ] >= 'a') && (message[ i ] <= 'z') )

		}//
		else
		{

			// RE-USE: Count ocurrences of Char "charListNotSorted[ i ]" inside list: message.
			//
			auxACharOcurrencesCount = std::count((*charListNotSorted).begin(), (*charListNotSorted).end(), message[ i ]);


			// Check to see if it is in the range: 'a'..'z', and IF it is not in the String...
			//
			if ((auxACharOcurrencesCount == 0) && ((message[ i ] >= 'a') && (message[ i ] <= 'z') ) )
			{

				// EnQeue:
				//
				(*charListNotSorted) += message[ i ];

			}//End if ((auxACharOcurrencesCount == 0) && ((message[ i ] >= a) && (message[ i ] <= z) ) )

		}//End else

	}//End for


	// Now we should be able to COUNT the SIZE of the String, and it SHOULD be the number of DIFFERENT CHARs from a to z.
	// We return as Pointers : myCharsAtoZCount & charListNotSorted
	//
	(*myCharsAtoZCount) = (*charListNotSorted).size();

}//End Procedure



/*2-********************************************************/

/** Compares two intervals according to staring times. 
*   Use it with 'PairSortStrings'.
*/
bool compareGreaterOrEqual(pair<int, char> p1, pair<int, char> p2) 
{ 
	return (p1.first > p2.first);

}//End compareGreaterOrEqual


/* Utility: Function to sort string (of char's) b
** according to the order defined by a[]
*/
void PairSortStrings(int a[], string* b, const int &n, bool ascending)
{

	// Dual Array with: Numbers (Freuqncies) & Char (the Letters)
	//
	// Original implementation with no Heap Allocations:	pair<int, char> pairt[ sizeof(*b) ];	 // Note: It does'nt work in VC++, only in GCC in Linux.
	//
	pair<int, char>* pairt = new pair<int, char>[ n ];


	// Storing the respective array
	// elements in pairs.
	//
	for (int i = 0; i < n; i++)
	{
		pairt[i].first = a[i];
		pairt[i].second = (*b)[i];
	}

	// Ascending: 1000, 100, 1.
	// Descending: 1, 100, ...1000000
	//
	if (ascending)
	{

		// Sorting the pair array.
		//
		sort(pairt, pairt + n);

	}//End if (ascending)
	else
	{

		// Sorting the pair array.
		//
		sort(pairt, pairt + n, compareGreaterOrEqual);

	}//End else


	// Updating the original arrays:
	//
	for (int i = 0; i < n; i++)
	{

		a[i] = pairt[i].first;
		(*b)[i] = pairt[i].second;

	}

	// Unallocate the var in Heap Memory:
	//
	delete[] pairt;

}//End Procedure




/*** 
2-  Populate a String with each Char Frequency <myFrequencyCharTable>; sorted from Maximum to Minimum.
OBS: 1- IGNORE CASE.

(You get): Updated Pointers to 'myFrequencyCharTable' & 'myFrequencyNumbersSorted[]'
**/
void CreateFrequencyCharTableAtoZSortedFromFrequentToInfrequent( const string &_myOriginalMessageLowercase, string* myFrequencyCharTable, int* myFrequencyNumbersSorted[] )
{

	const size_t messageLength = (*myFrequencyCharTable).size();
	//
	for (size_t i = 0; i < messageLength; i++)
	{

		// Count ocurrences of Char "charListNotSorted[ i ]" inside list: message.
		//
		(*myFrequencyNumbersSorted)[i] = std::count(_myOriginalMessageLowercase.begin(), _myOriginalMessageLowercase.end(), (*myFrequencyCharTable)[ i ]);

	}//End for


	// At this point we have a unsorted pair of Lists: <CHAR IN THE MESSAGE : of the Type :  char> and <CHAR FREQUENCY NUMBERS : of the Type : int[]>
	//
	// Size of : <CHAR FREQUENCY NUMBERS : of the Type : int[]>
	//
	//////Not necessary, it is better to use: messageLength, because 'sizeOfMyFrequencyNumbersSorted' is giving 1 as a (wrong) result.	 // const int sizeOfMyFrequencyNumbersSorted = (sizeof( (*myFrequencyNumbersSorted) ) / sizeof( (*myFrequencyNumbersSorted)[0] ) );
	//
	// Function calling
	//
	PairSortStrings( (*myFrequencyNumbersSorted), &(*myFrequencyCharTable), messageLength, false );

}//End Procedure




/*** 
3-  Replace each Letter/Char (from a to z & A to Z... ONLY, IGNORING AL OTHER CHARS, such as: !@#$%^&*() spaces, \n, etc.), creating a NEW variable: the DECRYPTED MESSAGE.
OBS: 1- IT RESPECTS CASE.

(You Get): The Decrypted Message (via a Pointer to  'myNewMessageDecrypted' ) + It prints it to Console.

**/
void SubstituteCharsOptimizedV3( string* myNewMessageDecrypted, string myFrequencyCharTable, string freqLang, int mycountOfDifferentCharsInMessage )
{

	// 0- Get the size of the original std::string
	//
	const string myMessage = (*myNewMessageDecrypted);
	const int myMessageSize = myMessage.size();

	// Auxiliar Char variables for not ignoring CASE:
	//
	char up1Compare = toupper('a');
	char down1Compare = tolower('A');
	//
	char up2Assign = toupper('a');
	char down2Assign = tolower('A');


	// 2- Replace all occurrences of CHAR: myFrequencyCharTable... | by CHAR:  freqLang | IN Message: myNewMessageDecrypted  (or  _myOriginalMessageLowercase..., but the CASE-SENSITIVE one is: myNewMessageDecrypted )
	//
	for (int i = 0; i < mycountOfDifferentCharsInMessage; i++)
	{

		// Initialize auxilliars (chars), for respecting UPPER and lower (case):
		// .1-  To compare
		//
		up1Compare = toupper( myFrequencyCharTable[ i ] );
		down1Compare = tolower( myFrequencyCharTable[ i ] );
		//
		//  .2- To assign / substitute:
		//
		up2Assign = toupper( freqLang[ i ] );
		down2Assign = tolower( freqLang[ i ] );


		// Loop going through a 'char[]' copy the Main String:   myNewMessageDecryptedCharArray[ box ]: beacuse it respects the \n and strange characters:
		//
		for (int box = 0; box < myMessageSize; box++)
		{

			// Note: I had to struggle (IN LINUX) with a great Bug. It is in the include: '#include <bits/stdc++.h>'.
			//...It happens when running this Line:
			//
			// myNewMessageDecrypted[ box ] = 'a';
			//
			// GCC Compiler says:
			//
			/*      Program received signal SIGSEGV, Segmentation fault.                                   
			0x00007ffff7b89ee2 in std::string::operator=(char) ()                                  
			from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
			*/
			// It means: "I cannot change the value of a basic string with a char". (But it is not a BASIC STRING!!! It is a CHAR ARRAY ( i.e.: char[size] = { 'a', 'b', ... 'z'} ))
			//
			// I solved it by using the char[] array JUST for Querying in the If, and by using the string Pointer (*myNewMessageDecrypted)[ box ]) for changing each value (char, letter, etc.) directly. If I use some Strings in this Script, it may, (or may not), run into Bugs beecause of the '#include <bits/stdc++.h>' override over the std::string Type..... (AND I can't delete this INCLUDE because I need it for the (Pair) Sorting and Char Counting 'std::count' in Step (2) of the Main Algorithm), which I have Tested very carefully, by the way.
			//

			// If it is a letter:  a..z   or  A..Z :
			//
			if ( (isalpha ( myMessage[ box ] ) > 0) )
			{

				// Replace UPPERCASES
				//
				if ( myMessage[ box ] == up1Compare )
				{

					(*myNewMessageDecrypted)[ box ] = up2Assign;

				}//End if
				//
				else if ( myMessage[ box ] == down1Compare )
				{

					(*myNewMessageDecrypted)[ box ] = down2Assign;

				}//End else if ( myMessage[ box ] ==..

			}//End if ( (isalpha ( myMessage[ box ]..

		}//End for2  for (int box = 0; box < myMessageSize; box++)

	}//End for

}//End Procedure





/*** 
It decrypts the Message given <message>, according to the Languages specific Character Frequency <freqLang>.

1-  Discover HOW MANY DIFFERENT CHARACTERS are there in the Message: get the Char Count (an int)
2-  Create an Array, Vector or String with each Char Frequency; sorted from Maximum to Minimum.
3-  Replace each Letter/Char (from a to z & A to Z... ONLY, IGNORING AL OTHER CHARS, such as: !@#$%^&*() spaces, \n, etc.), creating a NEW variable: the DECRYPTED MESSAGE.

RETURNS: The Decrypted Message.
**/
string DecryptMessage( const string &message, const string &freqLang )
{

	// 0- Lowercase all MESSAGE =>> message
	//
	string _myOriginalMessageLowercase = message;
	//
	transform(_myOriginalMessageLowercase.begin(), _myOriginalMessageLowercase.end(), _myOriginalMessageLowercase.begin(), ::tolower);


	//1-  Discover HOW MANY DIFFERENT CHARACTERS are there in the Message: get the Char Count (an int): 
	//    OBS: 1- IGNORE CASE.
	//
	string charListInMessage = "";
	//
	size_t mycountOfDifferentCharsInMessage = 0;
	//
	CountHowManyCharsAtoZ(_myOriginalMessageLowercase, &charListInMessage, &mycountOfDifferentCharsInMessage);
	

	//2-  Create an Array, Vector or String with each Char Frequency; sorted from Maximum to Minimum.
	//
	/////int myFrequencyNumbersSorted[ mycountOfDifferentCharsInMessage ];	IT WORKS IN gcc in Linux, but not in VC++
	//
	int* myFrequencyNumbersSorted = new int[ freqLang.size() /*sizeof(charListInMessage)*/ ];
	//
	// I had several problems with this VC++ specific Bug: Error	1	error C2057: expected constant expression	...main.cpp
	//...
	//... when I try to Define and Initialize a int[] array or char[] array with a non-Global-Variable-constant SIZE (I tried with 'const int' Types too (defined between this lines), but if it isn't a Constant  at Compile Time, (such as: a #define o precompiled): I doesn't work).
	//
	int* myPointerToMyFrequencyNumbersSorted = &myFrequencyNumbersSorted[ 0 ];
	//
	CreateFrequencyCharTableAtoZSortedFromFrequentToInfrequent( _myOriginalMessageLowercase, &charListInMessage, &myPointerToMyFrequencyNumbersSorted );


	//3-  Replace each Letter/Char (from a to z & A to Z... ONLY, IGNORING AL OTHER CHARS, such as: !@#$%^&*() spaces, \n, etc.), creating a NEW variable: the DECRYPTED MESSAGE.
	//
	string myNewMessageDecrypted = message;
	//
	SubstituteCharsOptimizedV3( &myNewMessageDecrypted, charListInMessage, freqLang, mycountOfDifferentCharsInMessage );

	// Destroy and unallocate the Memory used in the Heap by the variable array[].
	//
	delete[] myFrequencyNumbersSorted;


	// Finally return the DECRYPTED Message:
	//
	return myNewMessageDecrypted;

}//End Function




int main() 
{

	std::cout << "\n\n***************************************\n";
	std::cout << "***************************************\n\n";
	std::cout << "Bamtang Games Test for Game Developers: \n\nANSWER TO THE C++ GAME DEV EXAM QUESTION: __1__ CIPHER.\n\n";
	std::cout << "OBSERVATION: The Message String is HARDCODED, meaning that It is inside the Script: main.cpp.\n";
	std::cout << "23/12/2019\n***************************************\n\n";


	// 1- Print ORIGINAL MESSAGE:
	//
	std::cout << "\nOriginal Message\n______________________:\n\n" << _myOriginalMessage << "\n\n";
	std::cout << "\nLetters Frequency String for analysis\n______________________:\n\n" << _freqLang << "\n\n";


	// 2- Decrypt Message:  
	//
	string _myDecryptedMessage = DecryptMessage( _myOriginalMessage, _freqLang );


	//3-  Print Decrypted Message:
	//
	std::cout << "\nDecrypted Message\n______________________:\n\n" << _myDecryptedMessage << "\n\n";


	// Pause Console:
	//
	std::cout << "\n\nBy: Alejandro E. Almarza Martin\n\n+++Press the <ENTER> key to Terminate this Program+++";
	//
	// Pause:
	//
	cin.get();

	return 0;
}
