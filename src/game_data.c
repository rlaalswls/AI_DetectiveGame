//게임 데이터 초기화 시나리오1

#include <stdio.h>
#include <string.h>  // memset
#include "game_structs.h"

//사건 개요
void printCaseIntroduction() {
    printf("============================================================\n");
    printf("🕵️‍♀️ AI 추리 게임: CODE 404 - 진실을 찾을 수 없음\n");
    printf("============================================================\n");
    printf("- 사건 장소: 상명대학교 제1공학관 옥상\n");
    printf("- 피해자: 김시훈 (24세, 컴퓨터공학과 4학년)\n");
    printf("- 사망 시각: 2025년 6월 10일 밤 10시 30분 ~ 11시 사이\n");
    printf("- 사인: 옥상에서 추락사 (추락 전 다툼 흔적, 방어흔 없음)\n");
    printf("- 특이사항: 졸업 프로젝트와 벤처 프로젝트를 동시에 진행 중,\n");
    printf("            전기공학과와 협업 중이었음\n\n");

    printf("용의자 목록:\n");

    printf("\n1. 이유빈 (23세, 컴퓨터공학과 3학년)\n");
    printf("- 성격: 분석적, 내성적, 완벽주의 성향\n");
    printf("- 관계: 졸업 프로젝트 후배이자 공동 개발자\n");
    printf("- 알리바이: 10시 전후로 3층 세미나실에서 코드 수정 중\n");
    printf("- 의심 정황:\n");
    printf("    · 피해자에 대한 불만을 SNS에 게시\n");
    printf("    · 3층 복도 CCTV에 서성이는 모습 포착\n");

    printf("\n2. 정승훈 (25세, 전기공학과 4학년)\n");
    printf("- 성격: 자존심 강하고 직설적\n");
    printf("- 관계: 공동 연구 프로젝트 회로 설계 담당\n");
    printf("- 알리바이: 10시경 전자실험실에서 회로 테스트 중 (혼자)\n");
    printf("- 의심 정황:\n");
    printf("    · 테스트보드에 피해자 이름 존재\n");
    printf("    · 리더 자리를 두고 피해자와 다툼\n");

    printf("\n3. 박정민 (26세, 제1공학관 조교)\n");
    printf("- 성격: 무뚝뚝하고 말이 없음\n");
    printf("- 관계: 자주 실험실 배정을 도와줌\n");
    printf("- 알리바이: 10시 이후 기숙사에 있었다고 주장 (증인 없음)\n");
    printf("- 의심 정황:\n");
    printf("    · 사건 당일 늦게까지 공학관에 있었던 것으로 추정\n");
    printf("    · 과거 피해자와의 마찰 (장비 정리 문제)\n");

    printf("\n4. 서지호 (24세, 전기공학과 졸업생)\n");
    printf("- 성격: 급하고 감정 기복 있음\n");
    printf("- 관계: 벤처 프로젝트 조언자 역할\n");
    printf("- 알리바이: 근처 카페에 있었다고 주장 (CCTV 없음)\n");
    printf("- 의심 정황:\n");
    printf("    · 자금 투자 문제로 갈등\n");
    printf("    · 공학관 출입 기록에 무단 출입 흔적\n");

    printf("\n장소 정보:\n");
    printf("- 옥상\n");
    printf("- 전자실험실\n");

    printf("\n사건의 증거와 추궁을 통해 범인을 밝혀내세요!\n");
    printf("============================================================\n\n");
}

void init_game_state(GameState *game) {
    memset(game, 0, sizeof(GameState));  // 전체 구조체 초기화

    // 장소 초기화
    strcpy(game->locations[0].name, "옥상");
    game->locations[0].hasEvidence[0] = 0;
    game->locations[0].hasEvidence[1] = 1;
    game->locations[0].evidenceCount = 2;

    strcpy(game->locations[1].name, "전자실험실");
    game->locations[1].hasEvidence[0] = 2;
    game->locations[1].hasEvidence[1] = 3;
    game->locations[1].hasEvidence[2] = 4;
    game->locations[1].evidenceCount = 3;

    // 증거 초기화
    strcpy(game->evidences[0].name, "신발 끌린 자국");
    strcpy(game->evidences[0].description, "옥상 난간 근처에서 발견된 신발 끌린 자국. 몸싸움의 흔적으로 보인다.");
    strcpy(game->evidences[0].location, "옥상");
    game->evidences[0].isKeyEvidence = 1;

    strcpy(game->evidences[1].name, "금속 조각");
    strcpy(game->evidences[1].description, "전기 장비에서 떨어진 것으로 보이는 금속 조각. 그러나 사건과는 무관한 것으로 추정된다.");
    strcpy(game->evidences[1].location, "옥상");
    game->evidences[1].isKeyEvidence = 0;

    strcpy(game->evidences[2].name, "회로 설계도 원본");
    strcpy(game->evidences[2].description, "정승훈의 이름으로 제출된 회로 설계도. 원래 피해자의 것이었으나 무단으로 변경된 흔적이 있다.");
    strcpy(game->evidences[2].location, "전기공학 실험실");
    game->evidences[2].isKeyEvidence = 1;

    strcpy(game->evidences[3].name, "실험용 PC의 삭제 로그");
    strcpy(game->evidences[3].description, "사건 직후 실험실 PC에서 파일 삭제 시도가 있었던 로그.");
    strcpy(game->evidences[3].location, "전기공학 실험실");
    game->evidences[3].isKeyEvidence = 0;

    strcpy(game->evidences[4].name, "출입 기록 삭제 흔적");
    strcpy(game->evidences[4].description, "서버 기록에서 사건 시각 무단 접근 및 로그 삭제 시도가 있었던 흔적.");
    strcpy(game->evidences[4].location, "전기공학 실험실");
    game->evidences[4].isKeyEvidence = 1;

    // 용의자 초기화
    strcpy(game->suspects[0].name, "이유빈");
    strcpy(game->suspects[0].job, "컴퓨터공학과 3학년");
    strcpy(game->suspects[0].personality, "분석적이고 내성적이며 완벽주의 성향");
    strcpy(game->suspects[0].relationWithVictim, "졸업 프로젝트 후배이자 공동 개발자");
    strcpy(game->suspects[0].alibi, "10시 전후로 제1공학관 3층 세미나실에서 코드 수정 중");
    strcpy(game->suspects[0].suspicious_points, "피해자에게 불만을 SNS에 토로, 3층 복도 CCTV에 서성이는 모습");
    game->suspects[0].isCulprit = 0;

    strcpy(game->suspects[1].name, "정승훈");
    strcpy(game->suspects[1].job, "전기공학과 4학년");
    strcpy(game->suspects[1].personality, "자존심 강하고 직설적");
    strcpy(game->suspects[1].relationWithVictim, "공동 연구 프로젝트 전기회로 설계 담당");
    strcpy(game->suspects[1].alibi, "10시경 전자실험실에서 회로 테스트 중 (혼자 있었음)");
    strcpy(game->suspects[1].suspicious_points, "테스트보드에 피해자 이름, 리더 자리를 두고 피해자와 다툰 전적");
    game->suspects[1].isCulprit = 1;

    strcpy(game->suspects[2].name, "박정민");
    strcpy(game->suspects[2].job, "제1공학관 조교");
    strcpy(game->suspects[2].personality, "무뚝뚝하고 사적인 말이 없음");
    strcpy(game->suspects[2].relationWithVictim, "자주 실험실 배정을 도와줌");
    strcpy(game->suspects[2].alibi, "10시 이후부터 기숙사에 있었다고 주장");
    strcpy(game->suspects[2].suspicious_points, "늦은 시간 공학관에 있었던 목격, 과거 항의 메일 존재");
    game->suspects[2].isCulprit = 0;

    strcpy(game->suspects[3].name, "서지호");
    strcpy(game->suspects[3].job, "전기공학과 졸업생");
    strcpy(game->suspects[3].personality, "급한 성격, 감정 기복 있음");
    strcpy(game->suspects[3].relationWithVictim, "벤처 프로젝트 조언자 역할");
    strcpy(game->suspects[3].alibi, "근처 카페에 있었다고 주장하나 CCTV 없음");
    strcpy(game->suspects[3].suspicious_points, "자금 투자 문제로 갈등, 사건 시각 무단 출입 흔적");
    game->suspects[3].isCulprit = 0;

    // 기본 상태
    game->currentLocationIndex = 0;
    game->foundEvidence[0] = 0;
    game->pressChances = 0;
}