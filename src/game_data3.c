#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"

void CaseIntroduction3() {
    printf("=====================================================================\n");
    printf("☕ CODE 404: Unknown Coffee\n");
    printf("=====================================================================\n");
    printf("당신은 특수사건 전담 수사팀의 베테랑 형사입니다. 이번 사건은 평화로운 서울 종로구의 한 카페에서 벌어졌습니다.\n");
    printf("2025년 7월 5일 밤, 유명한 디자인 카페에서 의문의 사망 사건이 발생했습니다.\n");
    printf("피해자는 카페의 사장이자 전직 바리스타인 최서준(33세). 평소처럼 마감 후 커피를 즐기던 그는, 커피를 마신 직후 갑작스러운 발작을 일으키고 11시 20분경 사망했습니다.\n");
    printf("사인은 심정지. 원인은 그가 마신 커피에 들어간 수제 시럽 속 독성 물질이었습니다.\n");
    printf("사건 현장과 주변의 CCTV, 그리고 용의자들의 엇갈린 진술 속에서 진실은 점점 미궁으로 빠져듭니다.\n");
    printf("당신의 임무는 이 정적의 공간 속에 숨겨진 치밀한 계획과 복잡한 감정을 꿰뚫어 보는 것입니다.\n");
    printf("누가, 왜, 그리고 어떻게 이 작은 카페를 죽음의 무대로 만들었는지 밝혀내십시오.\n");

    printf("\n<용의자 목록>\n");

    printf("\n1. 정윤아 (29세, 아르바이트생)\n");
    printf("- 성격: 명랑하지만 감정 기복이 있으며 다소 충동적\n");
    printf("- 관계: 피해자의 직원, 최근 스케줄 문제로 다툰 적 있음\n");
    printf("- 알리바이: 11시경 카운터에서 계산 마무리 중\n");
    printf("- 의심 정황:\n");
    printf("    · 피해자의 커피를 마지막으로 준비한 인물\n");

    printf("\n2. 윤지석 (31세, 카페 공동 운영자)\n");
    printf("- 성격: 이성적이고 계산적인 성격\n");
    printf("- 관계: 피해자와 수익 분배 문제로 갈등\n");
    printf("- 알리바이: 11시경 뒷골목에서 통화 중이라 주장 (확인 불가)\n");
    printf("- 의심 정황:\n");
    printf("    · 시럽 재고를 독점적으로 관리\n");

    printf("\n3. 장세진 (35세, 단골 손님)\n");
    printf("- 성격: 깔끔하고 예민한 성격\n");
    printf("- 관계: 과거 연인이었으며 최근 관계 회복 시도\n");
    printf("- 알리바이: 10시 반경 카페를 나갔다고 주장 (목격자 없음)\n");
    printf("- 의심 정황:\n");
    printf("    · 마지막 문자에서 피해자와 감정적 다툼\n");
    printf("    · 연구원으로 독성 물질 관련 논문 작성 경력 있음\n");

    printf("\n<주변 장소>\n");
    printf("- 카페 주방\n");
    printf("- 카페 옆 창고\n");
  
    printf("\n커피 향기에 가려진 진실을 밝혀내고, 피해자의 죽음에 얽힌 비밀을 파헤치세요.\n");
    printf("당신의 선택이 이 사건의 결말을 좌우할 것입니다.\n");
    printf("============================================================\n\n");
}

void init_game_state3(GameState *game) {
    memset(game, 0, sizeof(GameState));

    // 장소 연결리스트 생성
    Location *loc1 = malloc(sizeof(Location));
    strcpy(loc1->name, "카페 주방");
    loc1->evidences = NULL;
    loc1->next = NULL;

    Location *loc2 = malloc(sizeof(Location));
    strcpy(loc2->name, "카페 창고");
    loc2->evidences = NULL;
    loc2->next = NULL;

    loc1->next = loc2;
    game->locations = loc1;

    // 증거 연결리스트 및 장소 연결
    Evidence *e1 = malloc(sizeof(Evidence));
    strcpy(e1->name, "수제 시럽 병");
    strcpy(e1->description, "피해자가 먹은 수제 시럽 병. 뚜껑이 헐겁고, 병 표면에서 정윤아의 지문이 검출되었다.");
    strcpy(e1->location, "카페 주방");
    e1->next = NULL;

    Evidence *e2 = malloc(sizeof(Evidence));
    strcpy(e2->name, "커피잔 잔여물");
    strcpy(e2->description, "피해자가 마신 커피 잔. 성분 분석 결과 미세한 침전물에서 독성 물질 성분이 검출되었다.");
    strcpy(e2->location, "카페 주방");
    e2->next = e1;

    loc1->evidences = e2;

    Evidence *e3 = malloc(sizeof(Evidence));
    strcpy(e3->name, "깨진 유리 약병");
    strcpy(e3->description, "작은 갈색 유리 약병의 깨진 조각. 커피잔에 들어간 독성 물질의 성분이 검출되었다.");
    strcpy(e3->location, "카페 창고");
    e3->next = NULL;

    Evidence *e4 = malloc(sizeof(Evidence));
    strcpy(e4->name, "CCTV 영상");
    strcpy(e4->description, "사건 당일 10시 20분경, 장세진이 주방 근처에서 잠시 머물다 가는 모습이 희미하게 보인다.");
    strcpy(e4->location, "카페 창고");
    e4->next = e3;

    loc2->evidences = e4;

    // 전체 증거 연결
    game->allEvidences = e4;

    // 용의자 연결리스트 생성
    Suspect *s1 = malloc(sizeof(Suspect));
    strcpy(s1->name, "정윤아");
    strcpy(s1->job, "카페 아르바이트생");
    strcpy(s1->personality, "명랑하지만 감정 기복 있음");
    strcpy(s1->relationWithVictim, "피해자의 커피를 준비한 마지막 인물, 스케줄 문제로 다툼");
    strcpy(s1->alibi, "11시 무렵 카운터에서 계산 마무리 중");
    strcpy(s1->suspicious_points, "시럽 병에서 정윤아의 지문 검출");
    s1->isCulprit = 0; s1->interrogationCount = 0;
    s1->next = NULL;

    Suspect *s2 = malloc(sizeof(Suspect));
    strcpy(s2->name, "윤지석");
    strcpy(s2->job, "카페 공동 운영자");
    strcpy(s2->personality, "이성적이고 계산적인 성격");
    strcpy(s2->relationWithVictim, "수익 분배 문제로 피해자와 갈등, 시럽 재고 독점 관리");
    strcpy(s2->alibi, "11시엔 뒷골목에서 통화 중");
    strcpy(s2->suspicious_points, "시럽 병 접근 가능자 중 하나, 통화 알리바이 확인 불가");
    s2->isCulprit = 0; s2->interrogationCount = 0;
    s2->next = s1;

    Suspect *s3 = malloc(sizeof(Suspect));
    strcpy(s3->name, "장세진");
    strcpy(s3->job, "연구원 (단골 손님)");
    strcpy(s3->personality, "과묵하고 침착하지만 집요한 면 있음");
    strcpy(s3->relationWithVictim, "과거 연인 관계, 다툼 있음. 독성 물질 관련 논문 작성 이력");
    strcpy(s3->alibi, "10시 반경 카페 나감 (목격자 없음)");
    strcpy(s3->suspicious_points, "주방 인근에 잠시 머문 CCTV 영상 존재");
    s3->isCulprit = 1; s3->interrogationCount = 0;
    s3->next = s2;

    game->suspects = s3;

    strcpy(game->currentLocationName, "카페 주방");
    game->pressChances = 5;
    game->scenarioNumber = 3;
}

void ending3(int isCorrect) {
    if (isCorrect) {
        printf("당신은 진범이 단골 손님 장세진임을 밝혀냈습니다. 피해자와 이별 후 분노로 수제 시럽에 독을 넣었습니다.\n");
        printf("커피 속 독극물과 쓰레기통 약병이 증거가 되었고 알리바이가 거짓임을 밝혀냈습니다.\n");
        printf("최서준 씨의 억울한 죽음은 당신의 수사 덕분에 진실이 밝혀지고, 범인이 합당한 처벌을 받게 되었습니다.\n");
    } else {
        printf("안타깝게도 당신은 '커피 한 잔에 숨겨진 진실'을 끝내 밝혀내지 못했습니다.\n");
        printf("최서준 사장의 죽음은 미제로 남았고, 진실은 영원히 숨겨졌습니다.\n");
    }
}
