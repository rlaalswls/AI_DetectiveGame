// 명령어 파싱 및 게임 명령 처리

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"
#include "command_parser.h"


// 공통 질문 입력 함수
void getInput(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void parseCommand(GameState *game, const char *input) {
    if (strncmp(input, "!이동 ", 8) == 0) {
        char location[64];
        sscanf(input + 8, "%63[^\n]", location);
        moveToLocation(game, location);
    } else if (strcmp(input, "!조사") == 0) {
        investigateLocation(game);
    } else if (strncmp(input, "!심문 ", 8) == 0) {
        char suspect[32];
        sscanf(input + 8, "%31[^\n]", suspect);
        interrogateSuspect(game, suspect);
    } else if (strncmp(input, "!추궁 ", 8) == 0) {
        char suspect[32];
        sscanf(input + 8, "%31[^\n]", suspect);
        pressSuspect(game, suspect);
    } else if (strcmp(input, "!증거") == 0) {
        listFoundEvidence(game);
    } else if (strncmp(input, "!지목 ", 8) == 0) {
        char suspect[32];
        sscanf(input + 8, "%31[^\n]", suspect);
        pointOut(game, suspect);
    } else if (strcmp(input, "!도움말") == 0) {
        printf("!이동 [장소], !조사, !심문 [용의자], !추궁 [용의자], !증거, !지목 [용의자], !도움말\n");
    } else {
        printf("알 수 없는 명령입니다.\n사용 가능한 명령어: !이동 [장소], !조사, !심문 [용의자], !추궁 [용의자], !증거, !지목 [용의자], !도움말\n");
    }
}

void moveToLocation(GameState *game, const char *locationName) {
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (strcmp(game->locations[i].name, locationName) == 0) {
            game->currentLocationIndex = i;
            printf("'%s'(으)로 이동했습니다.\n", locationName);
            return;
        }
    }
    printf("해당 장소를 찾을 수 없습니다.\n");
    printf("%s", locationName);
}

void investigateLocation(GameState *game) {
    int locationIndex = game->currentLocationIndex;
    Location *loc = &game->locations[locationIndex];
    int foundNew = 0;

    for (int i = 0; i < loc->evidenceCount; i++) {
        int evidenceIndex = loc->hasEvidence[i];
        if (!game->foundEvidence[evidenceIndex]) {
            game->foundEvidence[evidenceIndex] = 1;
            printf("새로운 증거 발견: %s - %s\n", game->evidences[evidenceIndex].name, game->evidences[evidenceIndex].description);
            foundNew = 1;
        }
    }

    if (!foundNew) {
        printf("더 이상 찾을 수 있는 증거가 없습니다.\n");
    }
}

void listFoundEvidence(GameState *game) {
    int foundAny = 0;
    printf("발견한 증거 목록:\n");

    for (int i = 0; i < MAX_EVIDENCE; i++) {
        if (game->foundEvidence[i]) {
            Evidence *e = &game->evidences[i];
            printf("- %d. %s 장소: %s\n  %s\n", i+1, e->name, e->location, e->description);
            foundAny = 1;
        }
    }

    if (!foundAny) {
        printf("아직 증거를 찾지 못했습니다.\n");
    }
}

void interrogateSuspect(GameState *game, const char *suspectName) {
    Suspect *target = NULL;

    for (int i = 0; i < MAX_SUSPECTS; i++) {
        if (strcmp(game->suspects[i].name, suspectName) == 0) {
            target = &game->suspects[i];
            break;
        }
    }

    if (target == NULL) {
        printf("해당 용의자를 찾을 수 없습니다.\n");
        return;
    }

    if (target->interrogationCount >= MAX_INTERROGATIONS) {
        printf("%s: 더 이상 질문에 답하지 않겠습니다. (묵비권 행사)\n", suspectName);
        return;
    }

    target->interrogationCount++;

    char question[256];
    getInput(question, sizeof(question), "용의자에게 심문하세요: ");

    FILE *qf = fopen("/Users/sienna/Cworkspace/game/assets/question_interrogate.txt", "w");
    if (!qf) {
        perror("질문 파일 저장 실패");
        return;
    }
    fprintf(qf, "%s\n", question);
    fclose(qf);

    char command[256];
    snprintf(command, sizeof(command), "python3 /Users/sienna/Cworkspace/game/gpt/gpt_response.py interrogate \"%s\"", suspectName);
    int result = system(command);
    if (result != 0) {
        printf("GPT 호출 중 오류 발생\n");
        return;
    }

    FILE *af = fopen("/Users/sienna/Cworkspace/game/assets/response_interrogate.txt", "r");
    if (!af) {
        perror("응답 파일 열기 실패");
        return;
    }

    printf("용의자 %s의 응답: ", suspectName);
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), af)) {
        printf("%s", buffer);
    }
    fclose(af);
}

void pressSuspect(GameState *game, const char *suspectName) {
    if (game->pressChances <= 0) {
        printf("추궁 기회를 모두 소진했습니다. 더 이상 추궁할 수 없습니다.\n");
        return;
    }

    Suspect *target = NULL;
    for (int i = 0; i < MAX_SUSPECTS; i++) {
        if (strcmp(game->suspects[i].name, suspectName) == 0) {
            target = &game->suspects[i];
            break;
        }
    }
    if (!target) {
        printf("해당 용의자를 찾을 수 없습니다.\n");
        return;
    }

    char question[256];
    getInput(question, sizeof(question), "용의자에게 추궁하세요: ");

    FILE *qf = fopen("question_press.txt", "w");
    if (!qf) {
        perror("질문 파일 저장 실패");
        return;
    }
    fprintf(qf, "%s\n", question);
    fclose(qf);

    char command[256];
    snprintf(command, sizeof(command), "python3 /Users/sienna/Cworkspace/game/gpt/gpt_response.py press \"%s\"", suspectName);
    int result = system(command);
    if (result != 0) {
        printf("GPT 호출 중 오류 발생\n");
        return;
    }

    FILE *af = fopen("response_press.txt", "r");
    if (!af) {
        perror("응답 파일 열기 실패");
        return;
    }

    char line[512];
    int inResponse = 0;
    int inVerdict = 0;

    char responseText[2048] = "";
    char verdict[128] = "";

    while (fgets(line, sizeof(line), af)) {
        if (strncmp(line, "[응답]", 6) == 0) {
            inResponse = 1;
            inVerdict = 0;
            continue;
        } else if (strncmp(line, "[판단]", 6) == 0) {
            inResponse = 0;
            inVerdict = 1;
            continue;
        }

        if (inResponse) {
            strcat(responseText, line);
        } else if (inVerdict) {
            strncpy(verdict, line, sizeof(verdict));
            break;
        }
    }
    fclose(af);

    responseText[strcspn(responseText, "\n")] = '\0';
    verdict[strcspn(verdict, "\n")] = '\0';

    printf("용의자 응답:\n%s\n", responseText);
    //printf("추궁 결과: %s\n", verdict);

    if (strstr(verdict, "정확한") != NULL) {
        printf("정확한 추궁입니다. 남은 기회: %d\n", game->pressChances);
    } else {
        game->pressChances--;
        printf("잘못된 추궁입니다. 남은 기회: %d\n", game->pressChances);
    }
}

void pointOut(GameState* gameState, const char* SuspectName) {
    for (int i = 0; i < MAX_SUSPECTS; i++) {
        if (strlen(gameState->suspects[i].name) == 0) continue; // 빈 슬롯 건너뜀

        if (strcmp(gameState->suspects[i].name, SuspectName) == 0) {
            if (gameState->suspects[i].isCulprit == 1) {
                printf("범인입니다! 당신은 진실을 밝혀냈습니다.\n");
            } else {
                printf("범인이 아닙니다. 당신은 범인을 놓쳤습니다.\n");
            }
            exit(0); // 게임 종료
        }
    }

    printf("해당 이름의 용의자가 존재하지 않습니다.\n");
}