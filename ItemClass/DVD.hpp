//
//  DVD.hpp
//  testing
//
//  Created by Thai Nam Hoang on 07/01/2022.
//

#ifndef DVD_hpp
#define DVD_hpp

#include <stdio.h>
#include "Item.hpp"

using namespace std;

class DVD: public Item
{
protected:
    string genre;
public:
    // Constructor
    DVD();
    DVD(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre);
    
    // Destructor
    ~DVD();
    
    // Getter
    string getGenre();
    
    // Setter
    void setGenre(string genre);
    
    // Other functions
    void print();
    //    string toString();
};

#endif /* DVD_hpp */
