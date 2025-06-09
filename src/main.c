#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"
#include "command_parser.h"
#include "gpt_queue.h"
#include "Introduction.c"

#define INPUT_BUFFER_SIZE 256
#define MAX_GPT_QUEUE 10
#define MAX_PROMPT_LEN 512
#define MAX_RESPONSE_LEN 1024

GPTQueue gptQueue;

int main() {
    while (1) {
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
            case 1:
                CaseIntroduction1();
                init_game_state1(&gameState);
                break;
            case 2:
                CaseIntroduction2();
                init_game_state2(&gameState);
                break;
            case 3:
                CaseIntroduction3();
                init_game_state3(&gameState);
                break;
        }
        // 초기 증거 및 용의자 정보를 텍스트 파일로 저장 (GPT 시스템 프롬프트용)
        saveEvidenceToFile(&gameState, "../AI_DetectiveGame/assets/evidence.txt");
        saveSuspectsToFile(&gameState, "../AI_DetectiveGame/assets/suspect_profiles.txt");
        printf("게임을 시작합니다.\n\n");
        printf("명령어를 입력하여 게임을 진행하세요. (명령어 확인: !도움말)\n");
        printf("현재  (%s)에 있다. 주변 장소를 탐색해보자.\n", gameState.currentLocationName);
        

        while (1) {
            printf("\n>(%s) ", gameState.currentLocationName);
            if (!fgets(input, INPUT_BUFFER_SIZE, stdin)) {
                printf("입력 오류 발생. 종료합니다.\n");
                break;
            }
            input[strcspn(input, "\n")] = '\0'; //개행문자 제거

            if (strcmp(input, "!종료") == 0 || strcmp(input, "exit") == 0) {
                printf("게임을 종료합니다.\n");
                exit(0);
            }

            int pointOutResult = parseCommand(&gameState, input);
            
            FILE* fp = fopen("output.txt", "r");
            if (fp) {
                char buffer[MAX_RESPONSE_LEN];
                if (fgets(buffer, sizeof(buffer), fp)) {
                    // 아직 처리 안된 큐에 응답 저장
                    for (int i = 0; i < MAX_GPT_QUEUE; i++) {
                        if (gptQueue.queue[i].handled == 0) {
                            strncpy(gptQueue.queue[i].response, buffer, MAX_RESPONSE_LEN);
                            gptQueue.queue[i].handled = 1;
                            printf("%s\n", buffer);
                            break;
                        }
                    }
                }
                fclose(fp);
            }






            if (pointOutResult == 1) {
                break;  // pointOut에서 1 리턴 → 루프 종료 → 시나리오 재시작
            }
        }
    }
    return 0;
}
