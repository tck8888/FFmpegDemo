//
// Created by tck on 2020/11/27.
//

#ifndef MYMUSICPLAYER_MYPLAYERSTATUS_H
#define MYMUSICPLAYER_MYPLAYERSTATUS_H


class MyPlayerStatus {

public:
    bool exit= false;
    bool load= true;
    bool seek = false;
public:
    MyPlayerStatus();
    ~MyPlayerStatus();
};


#endif //MYMUSICPLAYER_MYPLAYERSTATUS_H
