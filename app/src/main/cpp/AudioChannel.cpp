//
// Created by tck on 2020/11/26.
//

#include "AudioChannel.h"

AudioChannel::AudioChannel(MyPlayerStatus *_playerStatus) : playerStatus(_playerStatus) {
    this->queue = new MyQueue(_playerStatus);
}

AudioChannel::~AudioChannel() {

}


