#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"
#include "command_parser.h"

#define INPUT_BUFFER_SIZE 256

int main() {
    GameState gameState;
    char input[INPUT_BUFFER_SIZE];

    // (1) 게임 상태 초기화
    init_game_state(&gameState);

    // (2) 초기 증거 및 용의자 정보를 텍스트 파일로 저장 (GPT 시스템 프롬프트용)
    saveEvidenceToFile(&gameState, "/Users/sienna/Cworkspace/game/assets/evidence.txt");
    saveSuspectsToFile(&gameState, "/Users/sienna/Cworkspace/game/assets/suspect_profiles.txt");

    printCaseIntroduction();
    printf("게임을 시작합니다.\n명령어를 입력하세요. (명령어 확인: !도움말)\n");

    // (3) 명령어 입력 루프 시작
    while (1) {
        printf("\n> ");
        if (!fgets(input, INPUT_BUFFER_SIZE, stdin)) {
            printf("입력 오류 발생. 종료합니다.\n");
            break;
        }

        // 개행 문자 제거
        input[strcspn(input, "\n")] = '\0';

        // 종료 명령 처리
        if (strcmp(input, "!종료") == 0 || strcmp(input, "exit") == 0) {
            printf("게임을 종료합니다.\n");
            break;
        }

        // 명령어 파싱 및 처리
        parseCommand(&gameState, input);
    }

    return 0;

}