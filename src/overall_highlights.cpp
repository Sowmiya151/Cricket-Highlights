#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

// ---------------- DATA STRUCT ----------------
struct BallEvent {
    int ball_number;
    int over;

    double ball_speed, bat_acceleration, bat_rotation_speed;
    double impact_force, shot_speed, shot_angle;

    bool boundary_crossed;
    double shot_distance;

    double fielder_speed, distance_covered, reaction_time;

    double crowd_noise_level;
    bool crowd_spike;

    double wind_speed, temperature;

    bool stump_hit;
    double stump_vibration;
};

// ---------------- EVENT SCORE ----------------
double getEventScore(const BallEvent &e) {
    double score = 0;

    if (e.boundary_crossed) {
        if (e.shot_distance > 100) score += 110;
        else if (e.shot_distance > 80) score += 90;
        else score += 70;
    }

    return score;
}

// ---------------- PHYSICS SCORE ----------------
double getPhysicsScore(const BallEvent &e) {
    double score = 0;

    if (e.ball_speed > 150) score += 60;
    else if (e.ball_speed > 145) score += 40;

    if (e.shot_speed > 140) score += 40;

    if (e.impact_force > 60) score += 40;

    if (e.bat_acceleration > 30) score += 30;
    if (e.bat_rotation_speed > 2000) score += 30;

    if (e.shot_distance > 100) score += 80;

    return score;
}

// ---------------- FIELDING ----------------
double getFieldingScore(const BallEvent &e) {
    double score = 0;

    if (e.fielder_speed > 25) score += 30;
    if (e.distance_covered > 20) score += 30;
    if (e.reaction_time < 300) score += 40;

    return score;
}

// ---------------- STUMP IMPACT ----------------
double getStumpScore(const BallEvent &e) {
    double score = 0;

    if (e.stump_hit) {
        score += 100;

        if (e.stump_vibration > 60)
            score += 60;
    }

    return score;
}

// ---------------- AUDIO ----------------
double getAudioScore(const BallEvent &e) {
    double score = 0;

    if (e.crowd_noise_level > 100) score += 80;
    else if (e.crowd_noise_level > 90) score += 50;

    if (e.crowd_spike) score += 50;

    return score;
}

// ---------------- ENVIRONMENT ----------------
double getEnvironmentScore(const BallEvent &e) {
    double score = 0;

    if (e.wind_speed > 20) score += 10;
    if (e.temperature > 35) score += 5;

    return score;
}

// ---------------- TOTAL SCORE ----------------
double computeHighlightScore(const BallEvent &e) {

    double HS = 0;

    HS += getEventScore(e);
    HS += getPhysicsScore(e);
    HS += getFieldingScore(e);
    HS += getStumpScore(e);
    HS += getAudioScore(e);
    HS += getEnvironmentScore(e);

    // SPECIAL RULES

    if (e.boundary_crossed && e.shot_distance > 95 && e.crowd_noise_level > 95)
        HS += 120;

    if (e.stump_hit && e.stump_vibration > 70)
        HS += 120;

    return HS;
}

// ---------------- CLASSIFICATION ----------------
string classifyHighlight(double HS) {
    if (HS >= 300) return "PREMIUM";
    if (HS >= 180) return "STANDARD";
    if (HS >= 100) return "MINOR";
    return "IGNORE";
}

// ---------------- CSV SPLIT ----------------
vector<string> split(string line) {
    vector<string> res;
    string item;
    stringstream ss(line);

    while (getline(ss, item, ',')) {
        item.erase(remove(item.begin(), item.end(), ' '), item.end());
        res.push_back(item);
    }

    return res;
}

// ---------------- PARSER ----------------
BallEvent parseRow(vector<string> &row) {
    BallEvent e;
    int i = 0;

    e.ball_number = stoi(row[i++]);
    e.over = stoi(row[i++]);

    e.ball_speed = stod(row[i++]);
    e.bat_acceleration = stod(row[i++]);
    e.bat_rotation_speed = stod(row[i++]);

    e.impact_force = stod(row[i++]);
    e.shot_speed = stod(row[i++]);
    e.shot_angle = stod(row[i++]);

    e.boundary_crossed = stoi(row[i++]);
    e.shot_distance = stod(row[i++]);

    e.fielder_speed = stod(row[i++]);
    e.distance_covered = stod(row[i++]);
    e.reaction_time = stod(row[i++]);

    e.crowd_noise_level = stod(row[i++]);
    e.crowd_spike = stoi(row[i++]);

    e.wind_speed = stod(row[i++]);
    e.temperature = stod(row[i++]);

    e.stump_hit = stoi(row[i++]);
    e.stump_vibration = stod(row[i++]);

    return e;
}

// ---------------- MAIN ----------------
int main() {

    ifstream file("C:/Users/Sowmiya/Downloads/final project work/cricket_dataset.csv");

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 0;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {

        vector<string> row = split(line);

        if (row.size() < 21) continue;

        try {
            BallEvent e = parseRow(row);

            double score = computeHighlightScore(e);
            string type = classifyHighlight(score);

            // ONLY PREMIUM FILTER
            if (type == "PREMIUM") {
                cout << "Over " << e.over
                     << " Ball " << e.ball_number
                     << " | Score: " << score
                     << " |  PREMIUM HIGHLIGHT" << endl;
            }

        } catch (...) {
            cout << "Error parsing row" << endl;
        }
    }

    return 0;
}
