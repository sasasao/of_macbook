//
//  MemeData.hpp
//  oc_poster01
//
//  Created by 佐藤栞 on 2016/06/23.
//
//

#include "ofMain.h"

struct meme_data{
    string data;
    
};

class Meme {
public:
    void setup();
    void update();
    
    string user_id;
    string zone_date;
    float zone_focus;
    float zone_calm;
    float zone_posture;
    
    
};

