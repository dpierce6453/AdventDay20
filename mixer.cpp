//
// Created by Dan on 12/22/2022.
//

#include <cstdint>
#include <algorithm>
#include <iostream>
#include "mixer.h"

mixer::mixer(std::vector<int64_t> &vec) : vec(vec)
{
    for(int i=0; i < vec.size(); i++)
    {
        positions.push_back(i);
    }
}

void mixer::mix(size_t pos) {
    // find this position in the positions vector
    auto loc = std::find(positions.begin(), positions.end(), pos);
    int64_t index = loc - positions.begin();

    int64_t save = vec[index];  // value to be mixed.
    int64_t savepos = positions[index];
    if (save == 0)
    {
        return;

    }
    else
    {
        int64_t vecsize = vec.size();
        int64_t newpos =  (index + vec[index]) % (vecsize-1);
        if (newpos <= 0)
        {
            newpos = vecsize + newpos - 1;
        }
        vec.erase(vec.begin()+index);
        positions.erase(positions.begin()+index);
        vec.insert(vec.cbegin() + newpos, save);
        positions.insert(positions.begin() + newpos, savepos);
    }
}
