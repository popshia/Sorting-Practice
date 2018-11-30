// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋 // CodeBlocks 17.12
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>

using namespace std ;

typedef struct DataStruct {
    string schoolNum = "\0" ;
    string schoolName = "\0" ;
    string departmentNum = "\0" ;
    string departmentName = "\0" ;
    int student = 0 ;
    int teacher = 0 ;
    int graduated = 0 ;
    string wholeSentence = "\0" ;
} DataStruct ;

static ifstream input ;
static ofstream output ;
static string FileN = "0" ;

class DestroyDickDecember {
    vector<DataStruct> dataBase ;
    vector<DataStruct> sorted ;
    
public:
    void inputData() {
        dataBase.clear() ;
        sorted.clear() ;
        DataStruct tempData ;
        string sentence = "\0" ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;
        
        while ( getline( input, sentence ) ) {
            // cout << sentence << endl ;
            tempData.wholeSentence = sentence ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( sentence ) ;
            
            while ( getline( cutStream, token, '\t' ) ) // cut the token one by one
                cut.push_back( token ) ;
            
            tempData.schoolNum = cut[0] ;
            tempData.schoolName = cut[1] ;
            tempData.departmentNum = cut[2] ;
            tempData.departmentName = cut[3] ;
            
            if ( cut[6].size() > 3 ) {
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), ',' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.student = atoi( cut[6].c_str() ) ;
            
            if ( cut[8].size() > 3 ) {
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), ',' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.graduated = atoi( cut[8].c_str() ) ;
            dataBase.push_back( tempData ) ;
        } // get the whole file
    } // input the data
    
    int FindLargest() {
        int largestIndex = 0 ;
        for ( int i = 0 ; i < dataBase.size() ; i++ ) {
            if ( dataBase[i].graduated > dataBase[largestIndex].graduated ) largestIndex = i ;
        }
        return largestIndex ;
    } // find the largest
    
    int FindSmallest() {
        int smallestIndex = 0 ;
        for ( int i = 0 ; i < dataBase.size() ; i++ ) {
            if ( dataBase[i].graduated < dataBase[smallestIndex].graduated ) smallestIndex = i ;
        }
        return smallestIndex ;
    } // find the smallest
    
    void SelectionSort() {
        while ( ! dataBase.empty() ) {
            int largestIndex = FindLargest() ;
            // cout << dataBase[largestIndex].graduated << endl ;
            sorted.push_back( dataBase[largestIndex] ) ;
            dataBase.erase( dataBase.begin()+largestIndex ) ;
        } // add to new vector and erase
    } // function 1: Selection Sort (done)
    
    void BubbleSort() {
        for ( int one = 0 ; one < dataBase.size() ; one++ ) {
            // cout << "one: " << dataBase[one].graduated << endl ;
            for ( int two = one ; two < dataBase.size() ; two ++ ) {
                // cout << "two: " << dataBase[two].graduated << endl ;
                if ( dataBase[two].graduated > dataBase[one].graduated ) swap( dataBase[two] ,dataBase[one] ) ;
            } // for
        } // for
        for ( int i = 0 ; i < dataBase.size() ; i++ ) output << dataBase[i].wholeSentence << endl ;
    } // function 1: Bubble Sort (done)

    int InsertedIdx( int* arr, int eleIdx, int(*compar)(int, int) ) {
        int i ;
        for ( i = 0 ; i < eleIdx ; i++ ) if( compar( arr[i], arr[eleIdx] ) > 0 ) {
            break ;
        }
        return i ;
    }
    
    void Insert(int* arr, int eleIdx, int inserted) {
        int ele = arr[eleIdx] ;
        int i ;
        for ( i = eleIdx ; i > inserted ; i-- ) arr[i] = arr[i - 1] ;
        arr[inserted] = ele ;
    }
    
    void InsertionSort( int* arr, int len, int(*compar)(int, int) ) {
        int i ;
        for ( i = 0 ; i < len ; i++ ) {
            int inserted = InsertedIdx(arr, i, compar) ;
            if ( inserted != i ) Insert(arr, i, inserted);
        }
    }
    
    void Print() { for( int i = 0 ; i < sorted.size() ; i++ ) output << sorted[i].wholeSentence << endl ; }
} ; // DestroyDickDecember

int main() {
    int command = 0 ;
    bool continueOrNot = false ;
    DestroyDickDecember function1 ;
    DestroyDickDecember function2 ;
    DestroyDickDecember function3 ;
    
    do {
        cout << "*****************************************" << endl ; // welcome message
        cout << "*****        Sorting Practice       *****" << endl ;
        cout << "***** 0 : Quit                      *****" << endl ;
        cout << "***** 1 : Select & Bubble Sort      *****" << endl ;
        cout << "***** 2 : Merge & Quick Sort        *****" << endl ;
        cout << "***** 3 : Radix Sort                *****" << endl ;
        cout << "*****************************************" << endl ;
        cout << endl << "Please enter your choice :" << endl ;
        
        cin >> command ; // read in user command
        
        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit
        
        else if ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command :" << endl << endl ;
            continueOrNot = true ;
        } // wrong command
        
        else if ( command == 1 ) {
            bool function1Confirm = false ;
            
            do {
                cout << "Please enter the file you want to read and copy or [0] to quit:" << endl ;
                cin >> FileN ;
                
                if ( FileN == "0" ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit
                
                else {
                    string fileName = "input" + FileN + ".txt" ;
                    input.open( fileName.c_str() ) ;
                    // cut the input FileN, try to open
                    if ( input.is_open() ) {
                        function1.inputData() ;
                        clock_t time ;
                        // selection sort
                        time = clock() ;
                        function1.SelectionSort() ; // sort
                        string outputName = "select_sort" + FileN + ".txt" ;
                        output.open( outputName.c_str() ) ;
                        function1.Print() ; // print
                        input.close() ;
                        output.close() ;
                        time = clock() - time ;
                        cout << "Selection Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                        // bubble sort
                        input.open( fileName.c_str() ) ;
                        function1.inputData() ;
                        time = clock() ;
                        outputName = "bubble_sort" + FileN + ".txt" ;
                        function1.BubbleSort() ;
                        output.open( outputName.c_str() ) ;
                        input.close() ;
                        output.close() ;
                        time = clock() - time ;
                        cout << "Bubble Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                        // set parameters
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // successfully opened
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function1Confirm ) ;
            
            FileN = "0" ;
        } // mission 1: Select & Bubble Sort
        
        /*else if ( command == 2 ) {
            bool function1Confirm = false ;
            
            do {
                cout << "Please enter the file you want to read and copy or [0] to quit:" << endl ;
                cin >> FileN ;
                
                if ( FileN == 0 ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit
                
                else {
                    // cut the input FileN, try to open
                    if ( input.open() ) {
                        clock_t time ;
                        time = clock() ;
                        function1.SelectionSort(<#int *arr#>, <#int len#>, <#int (*compar)(int, int)#>) ;
                        time = clock() - time ;
                        cout << "Selection Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                        time = clock() ;
                        function1.BubbleSort(<#int *arr#>, <#int len#>, <#int (*compar)(int, int)#>) ;
                        time = clock() - time ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                        cout << "Bubble Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                    } // open successfully
                    else cout << "*****  input" << FileN << ".txt does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function1Confirm ) ;
            
            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 1: Select & Bubble Sort
        
        else if ( command == 3 ) {
            bool function1Confirm = false ;
            
            do {
                cout << "Please enter the file you want to read and copy or [0] to quit:" << endl ;
                cin >> FileN ;
                
                if ( FileN == 0 ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit
                
                else {
                    // cut the input FileN, try to open
                    if ( input.open() ) {
                        clock_t time ;
                        time = clock() ;
                        function1.SelectionSort(<#int *arr#>, <#int len#>, <#int (*compar)(int, int)#>) ;
                        time = clock() - time ;
                        cout << "Selection Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                        time = clock() ;
                        function1.BubbleSort(<#int *arr#>, <#int len#>, <#int (*compar)(int, int)#>) ;
                        time = clock() - time ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                        cout << "Bubble Sort cost time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
                    } // open successfully
                    else cout << "*****  input" << FileN << ".txt does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function1Confirm ) ;
            
            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 1: Select & Bubble Sort*/
    } while( continueOrNot ) ;
} // main function
