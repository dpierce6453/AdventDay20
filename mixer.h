//
// Created by Dan on 12/22/2022.
//

#ifndef ADVENTDAY20_MIXER_H
#define ADVENTDAY20_MIXER_H


#include <vector>

class mixer {

    std::vector<int64_t> & vec;
    std::vector<int64_t> positions;

public:
    explicit mixer(std::vector<int64_t> &vec);
    void mix( size_t pos );
};


#endif //ADVENTDAY20_MIXER_H
