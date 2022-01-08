//
//  Record.hpp
//  testing
//
//  Created by Thai Nam Hoang on 08/01/2022.
//

#ifndef Record_hpp
#define Record_hpp

#include <stdio.h>
#include "Item.hpp"

using namespace std;

class Record: public Item
{
protected:
    string genre;
public:
    // Constructor
    Record();
    Record(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre);
    
    // Destructor
    ~Record();
    
    // Getter
    string getGenre();
    
    // Setter
    void setGenre(string genre);
    
    // Other functions
    void print();
    //    string toString();
};

#endif /* Record_hpp */
