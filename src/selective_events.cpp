#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define MAX_CLIPS 5   // number of highlight clips

// ---------------- STRUCT ----------------
typedef struct {
    int ball_number, over;
    double ball_speed, impact_force, shot_speed;
    int boundary_crossed;
    double shot_distance;
    double crowd_noise_level;
    int is_wicket;
    int runs;
    double score;
} BallEvent;

// ---------------- EVENT SCORE ----------------
double computeScore(BallEvent *e) {
    double score = 0;

    if (e->is_wicket) score += 120;

    if (e->boundary_crossed) {
        if (e->shot_distance > 90) score += 100;
        else score += 70;
    }

    if (e->ball_speed > 145) score += 40;
    if (e->shot_speed > 130) score += 40;
    if (e->impact_force > 50) score += 30;

    if (e->crowd_noise_level > 100) score += 120;
    else if (e->crowd_noise_level > 90) score += 80;

    return score;
}

// ---------------- SORT ----------------
int compare(const void *a, const void *b) {
    BallEvent *e1 = (BallEvent *)a;
    BallEvent *e2 = (BallEvent *)b;

    if (e2->score > e1->score) return 1;
    else if (e2->score < e1->score) return -1;
    return 0;
}

// ---------------- MAIN ----------------
int main() {
    FILE *fp = fopen("match.csv", "r");
    if (!fp) {
        printf("Cannot open match.csv\n");
        return 0;
    }

    BallEvent events[MAX];
    int count = 0;
    char line[512];

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp)) {
        BallEvent e;
        char *token;

        token = strtok(line, ","); if (!token) continue; e.ball_number = atoi(token);
        token = strtok(NULL, ","); if (!token) continue; e.over = atoi(token);
        token = strtok(NULL, ","); if (!token) continue; e.ball_speed = atof(token);
        token = strtok(NULL, ","); if (!token) continue; e.impact_force = atof(token);
        token = strtok(NULL, ","); if (!token) continue; e.shot_speed = atof(token);
        token = strtok(NULL, ","); if (!token) continue; e.boundary_crossed = atoi(token);
        token = strtok(NULL, ","); if (!token) continue; e.shot_distance = atof(token);
        token = strtok(NULL, ","); if (!token) continue; e.crowd_noise_level = atof(token);
        token = strtok(NULL, ","); if (!token) continue; e.is_wicket = atoi(token);
        token = strtok(NULL, ","); if (!token) continue; e.runs = atoi(token);

        e.score = computeScore(&e);
        events[count++] = e;
    }

    fclose(fp);

    if (count == 0) {
        printf("No valid data found!\n");
        return 0;
    }

    // -------- SORT EVENTS BY SCORE DESC --------
    qsort(events, count, sizeof(BallEvent), compare);

    // -------- PRINT TOP 5 HIGHLIGHT BALLS --------
    printf("\n===== TOP %d HIGHLIGHT CLIPS =====\n", MAX_CLIPS);

    int clips = count < MAX_CLIPS ? count : MAX_CLIPS;

    for (int i = 0; i < clips; i++) {
        printf("\n--- Clip %d ---\n", i + 1);
        printf("Over %d Ball %d | Score: %.2lf\n",
               events[i].over,
               events[i].ball_number,
               events[i].score);
    }

    return 0;
}
