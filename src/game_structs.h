#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#define MAX_SUSPECTS 4
#define MAX_LOCATIONS 3
#define MAX_EVIDENCE 6
#define MAX_INTERROGATIONS 10
#define MAX_PRESS_CHANCES 5

// 증거 구조체
typedef struct {
    char name[64];
    char description[256];
    char location[64]; // 발견된 장소
} Evidence;

// 장소 구조체
typedef struct {
    char name[64];
    int hasEvidence[MAX_EVIDENCE]; // 이 장소에 있는 증거의 인덱스
    int evidenceCount;
} Location;

// 용의자 구조체
typedef struct {
    char name[32];
    char job[64];
    char personality[128];
    char relationWithVictim[128];
    char alibi[256];
    char suspicious_points[256];
    int isCulprit; // 1이면 범인
    int interrogationCount;
} Suspect;

// 전체 게임 상태 구조체
typedef struct {
    int evidenceCount; // 실제 증거 개수
    int suspectCount;  // 실제 용의자 수
    Location locations[MAX_LOCATIONS];
    Suspect suspects[MAX_SUSPECTS];
    Evidence evidences[MAX_EVIDENCE];
    int currentLocationIndex;
    int foundEvidence[MAX_EVIDENCE]; // 플레이어가 발견한 증거 여부
    int pressChances; // 추궁 기회
    Suspect interrogationCount[MAX_INTERROGATIONS]; // 심문 횟수
    char currentLocationName[64]; // 현재 위치 이름
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
