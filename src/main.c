#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"
#include "command_parser.h"
#include "Introduction.c"

#define INPUT_BUFFER_SIZE 256

int main() {
    int shouldExit = 0;
    
    while (!shouldExit) {
        GameState gameState;
        char input[INPUT_BUFFER_SIZE];
        int scenarioChoice = 0;
        gameIntroduction();

        while (scenarioChoice < 1 || scenarioChoice > 3) {
            printf("시나리오 : ");
            fgets(input, INPUT_BUFFER_SIZE, stdin);
            scenarioChoice = atoi(input);
        }

        gameState.scenarioNumber = scenarioChoice;
        switch (scenarioChoice) {
            case 1: CaseIntroduction1(); init_game_state1(&gameState); break;
            case 2: CaseIntroduction2(); init_game_state2(&gameState); break;
            case 3: CaseIntroduction3(); init_game_state3(&gameState); break;
        }

        saveEvidenceToFile(&gameState, "../game/assets/evidence.txt");
        saveSuspectsToFile(&gameState, "../game/assets/suspect_profiles.txt");
        printf("게임을 시작합니다.\n\n");
        printf("명령어를 입력하여 게임을 진행하세요. (명령어 확인: !도움말)\n");
        printf("현재  (%s)에 있다. 주변 장소를 탐색해보자.\n", gameState.currentLocationName);

        while (1) {
            printf("\n>(%s) ", gameState.currentLocationName);
            if (!fgets(input, INPUT_BUFFER_SIZE, stdin)) {
                printf("입력 오류 발생. 종료합니다.\n");
                shouldExit = 1;
                break;
            }
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "!종료") == 0 || strcmp(input, "exit") == 0) {
                printf("게임을 종료합니다.\n");
                shouldExit = 1;
                break;
            }

            int pointOutResult = parseCommand(&gameState, input);
            if (pointOutResult == 1) {
                break;
            } else if (pointOutResult == 0) {
                shouldExit = 1;
                break;
            }
        }
    }

    return 0;
}
