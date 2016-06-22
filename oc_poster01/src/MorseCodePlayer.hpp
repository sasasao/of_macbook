//
//  MorseCodePlayer.hpp
//  oc_poster01
//
//  Created by 佐藤栞 on 2016/06/21.
//
//

#include "ofMain.h"

struct MorseCodeSymbol {
    string character;
    string code;
};


class MorseCodePlayer {
public:
    MorseCodePlayer();
    void setup();
    void update();
    void playCode(string morseCode);
    
    
    ofSoundPlayer dotPlayer;
    ofSoundPlayer dashPlayer;
    
    int currentSoundIndex;
    
    vector<char> codes;
    string currentCode;
    
    bool isReady;
};

