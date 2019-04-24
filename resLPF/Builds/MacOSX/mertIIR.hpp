//
//  mertIIR.hpp
//  resLPF
//
//  Created by Mert Salahi on 4/22/19.
//

#ifndef mertIIR_hpp
#define mertIIR_hpp

#include <stdio.h>
#include <vector>

class mertIIR
{
public:
    mertIIR();
    ~mertIIR();
    
    std::vector<float> b;
    std::vector<float> a;
private:
};

#endif /* mertIIR_hpp */
