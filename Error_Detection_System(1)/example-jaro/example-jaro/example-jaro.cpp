//
//  main.cpp
//  example-jaro
//
//  Created by 松尾静一郎 on 2018/01/21.
//  Copyright © 2018年 松尾静一郎. All rights reserved.
//

#include <iostream>

// valid_distance = -1 : not consider distance between characters
unsigned int getNumRangeMatchChar( const std::string &s1, const std::string &s2, const int distance = -1 ){
    unsigned int l1 = s1.size();
    unsigned int l2 = s2.size();
    bool ignore_distance = false;
    
    if( distance < 0 ){ ignore_distance = true; }
    
    unsigned int counter = 0;
    for( unsigned int i = 0; i < l1; ++i ){
        
        // setting search range
        unsigned int from = i;
        unsigned int under = l2;
        if(! ignore_distance ){
            from = ( i < (unsigned int)distance ) ? 0 :  i - (unsigned int)distance;
            under = ( i +(unsigned int)distance >= l2 ) ? l2 : i + (unsigned int)distance;
        }
        for( unsigned int j = from; j < under; ++j ){
            if( s1[i] == s2[j] ){ ++counter; }
            // NOTICE : this code consider the case i == j ( both place and character match )
        }
    }
    return counter;
}

std::string getRangeMatchChar( const std::string &s1, const std::string &s2, const int distance = -1 ){
    unsigned int l1 = s1.size(), l2 = s2.size();
    bool ignore_distance = false;
    
    if( distance < 0 ){ ignore_distance = true; }
    
    std::string ret = "";
    
    for( unsigned int i = 0; i < l1; ++i ){
        // setting search range
        unsigned int from = i;
        unsigned int under = l2;
        if(! ignore_distance ){
            from = ( i < distance ) ? 0 :  i - distance;
            under = ( i + distance >= l2 ) ? l2 : i + distance;
        }
        for( unsigned int j = from; j < under; ++j ){
            if( s1[i] == s2[j] ){ ret += s1[i]; }
            // NOTICE : this code consider the case i == j ( both place and character match )
        }
    }
    return ret;
}

unsigned int getNumTransposition( const std::string &s1, const std::string &s2 ){
    unsigned int c = 0;
    for( unsigned int i = 0; i < s1.size() && i < s2.size(); ++i ){
        if( s1[i] != s2[i] ){ ++c; }
    }
    return c;
    
}

// Error the case  s1 & s2 are empty
double getJaroDistance( const std::string &s1, const std::string &s2 ){
    int distance = ( s1.size() > s2.size() ) ? s1.size() : s2.size();
    if( distance < 0 ){ return -1; }
    distance = distance / 2 - 1;
    if( distance < 0 ){ return -1; }
    
    int match = getNumRangeMatchChar( s1, s2, distance );
    int trans = getNumTransposition( getRangeMatchChar( s1, s2, distance ), getRangeMatchChar( s2, s1, distance ) );
    double m = (double)match;
    double t = ( (double)trans ) / 2.;
    
    return ( m / (double)s1.size() + m / (double)s2.size() + ( m - t ) / match ) / 3.;
}

unsigned int getLengthOfCommonPrefix( const std::string &s1, const std::string &s2 ){
    unsigned int c = 0;
    for( unsigned int i = 0; i < s1.size() && i < s2.size(); ++i ){
        if( s1[i] == s2[i] ){ ++c; } else { return c; }
    }
    return c;
}

double getJaroWinklerDistance( const std::string &s1, const std::string &s2, const double scaling = 0.1 ){
    if( scaling < 0 ){ return -1; }
    double j = getJaroDistance( s1, s2 );
    return j + getLengthOfCommonPrefix( s1, s2 ) * scaling * ( 1 - j );
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    double result;
    
    result = getJaroWinklerDistance("Taro", "Tono", 0.1);
    
    std::cout << result << std::endl;
    
    return 0;
}
