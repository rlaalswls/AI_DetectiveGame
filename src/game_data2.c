//게임 데이터 초기화 시나리오2

#include <stdio.h>
#include <string.h>
#include "game_structs.h"

// 사건 개요
void CaseIntroduction2() {
    printf("=====================================================================\n");
    printf("🔭 CODE 404: Observatory Unavailable\n");
    printf("=====================================================================\n");
    printf("당신은 특수사건 수사팀의 베테랑 형사입니다. 이번 사건은 한적한 산 중턱에 위치한 외딴 관측소에서 발생했습니다.\n");
    printf("2025년 5월 14일 밤, 천체물리학자인 윤지훈 박사가 관측실에서 숨진 채 발견되었습니다.\n");
    printf("사망 시각은 밤 11시 15분경, 사인은 목 뒤를 둔기로 가격당한 충격에 의한 즉사였습니다.\n");
    printf("범행 장소는 관측소의 메인 관측실로 추정되며, 외부인의 침입 흔적은 발견되지 않았습니다.\n");
    printf("관측소 내부 인물들의 진술은 엇갈리고 있으며, 현장에는 수상한 증거들이 남겨져 있습니다.\n");
    printf("당신의 임무는 이 고요한 밤하늘 아래에서 벌어진 진실을 파헤치는 것입니다.\n");
    
    printf("\n<용의자 목록>\n");

    printf("\n1. 장유진 (39세, 기상 데이터 분석가)\n");
    printf("- 성격: 차분하고 논리적이나 말수가 적음\n");
    printf("- 관계: 피해자의 전 연인, 최근 사이가 악화됨\n");
    printf("- 알리바이: 밤 10시~12시 기상 장비실에서 데이터 정리 중\n");
    printf("- 의심 정황:\n");
    printf("    · 피해자와 말다툼 목격담 존재\n");
    printf("    · 장비실은 사건 현장과 멀지 않음\n");

    printf("\n2. 이준호 (28세, 견습 연구원)\n");
    printf("- 성격: 조심스럽고 예의 바르나, 피해자 앞에서는 위축된 태도\n");
    printf("- 관계: 피해자의 멘티로 자주 질책당함\n");
    printf("- 알리바이: 11시경 야외 전망대에서 별 사진 촬영 중\n");
    printf("- 의심 정황:\n");
    printf("    · 소유 삼각대에서 피해자의 혈흔 발견\n");
    printf("    · 촬영한 사진의 타임스탬프가 실제 시간과 불일치\n");

    printf("\n3. 오미경 (45세, 행정팀장)\n");
    printf("- 성격: 사무적이고 완고하며 책임감 강함\n");
    printf("- 관계: 피해자와 프로젝트 예산 관련 갈등\n");
    printf("- 알리바이: 밤 11시 연구소 사무실에서 예산 정리 중\n");
    printf("- 의심 정황:\n");
    printf("    · 피해자의 예산 삭감 요청 메일과 충돌\n");
    printf("    · 사무실은 관측실과 인접함\n");

    printf("\n<주변 장소>\n");
    printf("- 관측실\n");
    printf("- 야외 전망대\n");

    printf("\n밤하늘 아래, 별보다 더 복잡한 인간 관계 속에서 진실은 흐려져 갑니다.\n");
    printf("당신은 날카로운 직관과 증거 분석을 통해 이 어두운 진실을 밝혀내야 합니다.\n");
    printf("============================================================\n\n");
}

void init_game_state2(GameState *game) {
    memset(game, 0, sizeof(GameState));
    game->evidenceCount = 6;
    game->suspectCount = 3;

    // 장소 초기화
    strcpy(game->locations[0].name, "관측소 주차장");
    game->locations[0].evidenceCount = 0;

    strcpy(game->locations[1].name, "관측실");
    game->locations[1].hasEvidence[0] = 0;
    game->locations[1].hasEvidence[1] = 1;
    game->locations[1].hasEvidence[2] = 2;
    game->locations[1].evidenceCount = 3;

    strcpy(game->locations[2].name, "야외 전망대");
    game->locations[2].hasEvidence[0] = 3;
    game->locations[2].hasEvidence[1] = 4;
    game->locations[2].hasEvidence[2] = 5;
    game->locations[2].evidenceCount = 3;

    // 플레이어 시작 위치
    game->currentLocationIndex = 0;
    strcpy(game->currentLocationName, game->locations[0].name);

    // Evidence
    strcpy(game->evidences[0].name, "피해자의 연구 노트");
    strcpy(game->evidences[0].description, "책상 위에 있던 노트. 이준호의 아이디어가 피해자 이름으로 기록되었다.");
    strcpy(game->evidences[0].location, "관측실");

    strcpy(game->evidences[1].name, "희미한 흙자국");
    strcpy(game->evidences[1].description, "관측실 출입구 바닥에 있던 외부 흙자국.");
    strcpy(game->evidences[1].location, "관측실");

    strcpy(game->evidences[2].name, "기상 장비 보고서 출력물");
    strcpy(game->evidences[2].description, "관측 장비 사이에 낀 출력물. 장유진 서명 있음.");
    strcpy(game->evidences[2].location, "관측실");

    strcpy(game->evidences[3].name, "삼각대");
    strcpy(game->evidences[3].description, "전망대 바위 뒤에 숨겨져 있던 접이식 삼각대. 피해자의 혈흔이 묻어있다.");
    strcpy(game->evidences[3].location, "야외 전망대");

    strcpy(game->evidences[4].name, "이준호의 디지털 카메라");
    strcpy(game->evidences[4].description, "전망대 난간 위. 일부 사진 타임스탬프 조작이 의심된다.");
    strcpy(game->evidences[4].location, "야외 전망대");

    strcpy(game->evidences[5].name, "피 묻은 휴지");
    strcpy(game->evidences[5].description, "삼각대 근처 바닥에서 발견. 피를 닦은 흔적이 있다.");
    strcpy(game->evidences[5].location, "야외 전망대");

    // Suspects
    strcpy(game->suspects[0].name, "장유진");
    strcpy(game->suspects[0].job, "기상 데이터 분석가");
    strcpy(game->suspects[0].personality, "차분하고 논리적, 말수가 적음");
    strcpy(game->suspects[0].relationWithVictim, "전 연인, 최근 사이가 나빠짐");
    strcpy(game->suspects[0].alibi, "밤 10시~12시 기상 장비실에서 데이터 정리 중");
    strcpy(game->suspects[0].suspicious_points, "피해자와 말다툼 목격담 존재");
    game->suspects[0].isCulprit = 0;

    strcpy(game->suspects[1].name, "이준호");
    strcpy(game->suspects[1].job, "견습 연구원");
    strcpy(game->suspects[1].personality, "예의 바르나 위축된 태도, 조심스러움");
    strcpy(game->suspects[1].relationWithVictim, "멘토-멘티, 자주 질책당함");
    strcpy(game->suspects[1].alibi, "11시경 야외 전망대에서 별 사진 촬영");
    strcpy(game->suspects[1].suspicious_points, "촬영한 사진의 타임스탬프가 실제 시간과 불일치");
    game->suspects[1].isCulprit = 1;

    strcpy(game->suspects[2].name, "오미경");
    strcpy(game->suspects[2].job, "행정팀장");
    strcpy(game->suspects[2].personality, "사무적, 완고, 책임감 강함");
    strcpy(game->suspects[2].relationWithVictim, "프로젝트 예산 문제로 갈등");
    strcpy(game->suspects[2].alibi, "밤 11시 연구소 사무실에서 예산 정리 중");
    strcpy(game->suspects[2].suspicious_points, "사무실은 관측실과 인접");
    game->suspects[2].isCulprit = 0;

    //기본 상태
    game->foundEvidence[0] = 0;
    game->pressChances = 5;
    game->currentLocationIndex = 0;
    game->scenarioNumber=2;
    strcpy(game->currentLocationName, game->locations[0].name);  

}

void ending2(int isCorrect) {
    if (isCorrect) {
        printf("당신의 추리로 진범이 밝혀졌습니다. 윤지훈 박사를 살해한 범인은 제자 이준호였습니다. 연구 아이디어를 빼앗으려 한 피해자에게 분노하여 삼각대로 범행을 저질렀습니다.\n");
        printf("결국 이준호는 자신의 죄를 모두 자백했습니다. 윤지훈 박사의 억울한 죽음의 진상이 세상에 드러났습니다.\n");
        printf("밤하늘 아래 묻힐 뻔한 진실을 당신이 밝혀냈습니다.\n");
    } else {
            printf("안타깝게도 당신은 진범을 찾지 못했습니다. 단서들을 제대로 연결하지 못했거나, 다른 용의자에게 집중했습니다.\n");
            printf("진범인 이준호는 처벌받지 않았고, 윤지훈 박사의 죽음은 미제 사건으로 남았습니다. 당신이 놓친 증거들은 결국 빛을 보지 못했습니다.\n");
            printf("밤하늘 아래, 진실은 영원히 어둠 속에 묻히게 되었습니다.\n");
    }
}