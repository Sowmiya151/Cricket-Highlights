#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

// Structure for a ball
struct Ball {
    int over;
    int ball;
    int runs;
    bool wicket;
};

// Structure for highlight
struct Highlight {
    int over;
    int ball;
    int runs;
    bool wicket;
};

// Scoring function
int getScore(Ball b) {
    if (b.wicket) return 10;
    if (b.runs == 6) return 8;
    if (b.runs == 4) return 6;
    if (b.runs == 3) return 3;
    if (b.runs == 2) return 2;
    return 0;
}

// Process one over
Highlight processOver(vector<Ball>& balls) {
    int maxScore = -1;
    Ball bestBall;

    for (auto &b : balls) {
        int score = getScore(b);
        if (score > maxScore) {
            maxScore = score;
            bestBall = b;
        }
    }

    return {bestBall.over, bestBall.ball, bestBall.runs, bestBall.wicket};
}

// Display highlights
void display(queue<Highlight> q) {
    cout << "\n=== Highlight Timeline ===\n";
    while (!q.empty()) {
        auto h = q.front(); q.pop();

        cout << "Over " << h.over << " → Ball " << h.ball;

        if (h.wicket)
            cout << " (WICKET)";
        else if (h.runs == 6)
            cout << " (SIX)";
        else if (h.runs == 4)
            cout << " (FOUR)";
        else
            cout << " (" << h.runs << " runs)";

        cout << endl;
    }
}

int main() {
    ifstream file("match.csv"); // your CSV file
    string line;

    queue<Highlight> highlightQueue;
    vector<Ball> currentOver;

    int currentOverNo = -1;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string val;

        Ball b;

        getline(ss, val, ','); b.over = stoi(val);
        getline(ss, val, ','); b.ball = stoi(val);
        getline(ss, val, ','); b.runs = stoi(val);
        getline(ss, val, ','); b.wicket = stoi(val);

        // New over detected
        if (currentOverNo != -1 && b.over != currentOverNo) {
            // Process previous over
            Highlight h = processOver(currentOver);
            highlightQueue.push(h);

            // Display (LIVE UPDATE)
            display(highlightQueue);

            // Clear for next over
            currentOver.clear();
        }

        currentOver.push_back(b);
        currentOverNo = b.over;
    }

    // Process last over
    if (!currentOver.empty()) {
        Highlight h = processOver(currentOver);
        highlightQueue.push(h);
    }

    // Final display
    display(highlightQueue);

    return 0;
}
