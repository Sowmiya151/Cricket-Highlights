#include <iostream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

struct Ball {
    int over;
    int ball;
    int score;
    string event;
    int crowd_spike;
};

// Function to decide event based on score
string getEvent(int score) {
    if(score >= 100) return "WICKET";
    else if(score >= 80) return "SIX";
    else if(score >= 60) return "FOUR";
    else return "NORMAL";
}

int main() {

    // Simulated input from Rule Engine
    vector<Ball> data = {
        {1,1,20,"NORMAL",0},
        {1,2,80,"SIX",1},
        {1,3,30,"NORMAL",0},
        {1,4,60,"FOUR",0},
        {1,5,100,"WICKET",1},
        {1,6,40,"NORMAL",0},

        {2,1,25,"NORMAL",0},
        {2,2,60,"FOUR",0},
        {2,3,85,"SIX",1},
        {2,4,30,"NORMAL",0},
        {2,5,110,"WICKET",1},
        {2,6,20,"NORMAL",0}
    };

    map<int, Ball> bestHighlight;

    // Step 1: Find best ball per over
    for(auto b : data) {
        if(bestHighlight.find(b.over) == bestHighlight.end() || 
           b.score > bestHighlight[b.over].score) {
            bestHighlight[b.over] = b;
        }
    }

    // Step 2: Display Timeline
    cout << "\n HIGHLIGHT TIMELINE:\n";

    for(auto h : bestHighlight) {
        cout << "Over " << h.second.over
             << " Ball " << h.second.ball
             << " → " << h.second.event;

        //  Fan highlight
        if(h.second.crowd_spike == 1) {
            cout << "  (Popular)";
        }

        cout << endl;
    }

    return 0;
}
