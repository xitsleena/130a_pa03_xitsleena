#include "avl.h"
#include <string>
#include <sstream>
#include <iostream> 

using namespace std; 

int main(int arc, char* argv[]){

    string str = argv[1];
    
    istringstream iss(str);
	string t;
	string tt;

    int num; 


    while(iss >> t){
		
		if (t == "insert"){
		    // cout << t << endl;
		    iss >> tt;  
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
            
		    // cout << tt << endl; 
		}
		else if (t == "access"){
		    // cout << t << endl;
		    iss >> tt; 
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
            
		    // cout << tt << endl; 
		}
		else if (t == "delete") {
		    // cout << t << endl;
		    iss >> tt; 
		    if (tt.back() == ','){
		       tt.pop_back();
		    }
            num = stoi(tt);
		    // cout << tt << endl; 
		}
		else {
		    if (t.back() == ','){
		       t.pop_back();
		    }
           
            if (t == "print"){
                //quash->print();
            }
		   // cout << t << endl;
		}
		
	}

    return 0; 


}