#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#define MAX_NAME_LENGTH 64
#define MAX_JOB_LENGTH 64
#define MAX_PERSONALITY_LENGTH 128
#define MAX_RELATION_LENGTH 128
#define MAX_ALIBI_LENGTH 256
#define MAX_SUSPICIOUS_LENGTH 256

// 증거 구조체 (연결리스트)
typedef struct Evidence {
    char name[MAX_NAME_LENGTH];
    char description[256];
    char location[MAX_NAME_LENGTH]; // 발견된 장소
    int found;
    struct Evidence* next;
} Evidence;

// 장소 구조체 (연결리스트)
typedef struct Location {
    char name[MAX_NAME_LENGTH];
    Evidence* evidences; // 해당 장소의 증거 연결리스트
    struct Location* next;
} Location;

// 용의자 구조체 (연결리스트)
typedef struct Suspect {
    char name[32];
    char job[MAX_JOB_LENGTH];
    char personality[MAX_PERSONALITY_LENGTH];
    char relationWithVictim[MAX_RELATION_LENGTH];
    char alibi[MAX_ALIBI_LENGTH];
    char suspicious_points[MAX_SUSPICIOUS_LENGTH];
    int isCulprit;
    int interrogationCount;
    struct Suspect* next;
} Suspect;

// 전체 게임 상태 구조체
typedef struct GameState {
    Location* locations;
    Suspect* suspects;
    Evidence* allEvidences;  // 전체 증거 목록 (장소 외부에서도 관리 가능)
    int pressChances;
    char currentLocationName[MAX_NAME_LENGTH];
    int scenarioNumber;
} GameState;


void CaseIntroduction1();
void CaseIntroduction2();
void CaseIntroduction3();
void init_game_state1(GameState *game);
void init_game_state2(GameState *game);
void init_game_state3(GameState *game);
void saveEvidenceToFile(GameState *game, const char *filename);
void saveSuspectsToFile(GameState *game, const char *filename);
void ending1(int isCorrect);
void ending2(int isCorrect);
void ending3(int isCorrect);

#endif // GAME_STRUCTS_H
