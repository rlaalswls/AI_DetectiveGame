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

int parseCommand(GameState *game, const char *input) {
    if (strncmp(input, "!이동 ", 8) == 0) {
        char location[64];
        sscanf(input + 8, "%63[^\n]", location);
        moveToLocation(game, location);
    } else if (strncmp(input, "!조사 ", 8) == 0) {
        char evidence[64];
        sscanf(input + 8, "%63[^\n]", evidence);
        investigateLocation(game, evidence);
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
        int continueGame = pointOut(game, suspect);
        return continueGame; //1이면 재시작
    } else if (strcmp(input, "!도움말") == 0) {
        printf("!이동 [장소], !조사 [증거명], !심문 [용의자], !추궁 [용의자], !증거, !지목 [용의자], !도움말, !종료\n");
    } else {
        printf("알 수 없는 명령입니다.\n사용 가능한 명령어: !이동 [장소], !조사, !심문 [용의자], !추궁 [용의자], !증거 [증거명], !지목 [용의자], !도움말, !종료\n");
    }
    return 0;
}

void moveToLocation(GameState *game, const char *locationName) {
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (strcmp(game->locations[i].name, locationName) == 0) {
            game->currentLocationIndex = i;
            strcpy(game->currentLocationName, game->locations[i].name);
            printf("'%s'(으)로 이동한다.\n", locationName);

            Location *loc = &game->locations[i];

            if (loc->evidenceCount == 0) {
                printf("이 장소에는 아무 단서가 보이지 않는다.\n");
            } else {
                printf("이 장소에 있는 단서들:\n");
                for (int j = 0; j < loc->evidenceCount; j++) {
                    int evidenceIndex = loc->hasEvidence[j];
                    printf("- %s\n", game->evidences[evidenceIndex].name);
                }
            }
            return;
        }
    }
    printf("해당 장소를 찾을 수 없습니다: %s\n", locationName);
}

void investigateLocation(GameState *game, const char *evidenceName) {
    int locationIndex = game->currentLocationIndex;
    Location *loc = &game->locations[locationIndex];

    for (int i = 0; i < loc->evidenceCount; i++) {
        int evidenceIndex = loc->hasEvidence[i];
        Evidence *evi = &game->evidences[evidenceIndex];

        if (strcmp(evi->name, evidenceName) == 0) {
            if (!game->foundEvidence[evidenceIndex]) {
                game->foundEvidence[evidenceIndex] = 1;
                printf("새로운 증거를 발견했다!\n %s: %s\n", evi->name, evi->description);
            } else {
                printf("이미 조사한 증거다.\n");
            }
            return;
        }
    }

    printf("이 장소에 '%s'라는 증거는 없습니다.\n", evidenceName);
}

void listFoundEvidence(GameState *game) {
    int foundAny = 0;
    printf("<발견한 증거 목록>\n");

    for (int i = 0; i < MAX_EVIDENCE; i++) {
        if (game->foundEvidence[i]) {
            Evidence *e = &game->evidences[i];
            printf("- %s 장소: %s\n  %s\n", e->name, e->location, e->description);
            foundAny = 1;
        }
    }

    if (!foundAny) {
        printf("아직 증거를 발견하지 못했다.\n");
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

    FILE *qf = fopen("../game/assets/question_interrogate.txt", "w");
    if (!qf) {
        perror("질문 파일 저장 실패");
        return;
    }
    fprintf(qf, "%s\n", question);
    fclose(qf);

    char command[256];
    snprintf(command, sizeof(command), "python3 ../game/gpt/gpt_response.py interrogate \"%s\"", suspectName);
    int result = system(command);
    if (result != 0) {
        printf("GPT 호출 중 오류 발생\n");
        return;
    }

    FILE *af = fopen("../game/assets/response_interrogate.txt", "r");
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

    FILE *qf = fopen("../game/assets/question_press.txt", "w");
    if (!qf) {
        perror("질문 파일 저장 실패");
        return;
    }
    fprintf(qf, "%s\n", question);
    fclose(qf);

    char command[256];
    snprintf(command, sizeof(command), "python3 ../game/gpt/gpt_response.py press \"%s\"", suspectName);
    int result = system(command);
    if (result != 0) {
        printf("GPT 호출 중 오류 발생\n");
        return;
    }

    FILE *af = fopen("../game/assets/response_press.txt", "r");
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


int pointOut(GameState* gameState, const char* SuspectName) {
    for (int i = 0; i < MAX_SUSPECTS; i++) {
        if (strlen(gameState->suspects[i].name) == 0) continue;

        if (strcmp(gameState->suspects[i].name, SuspectName) == 0) {
            int isCorrect = (gameState->suspects[i].isCulprit == 1);

            // 시나리오 엔딩 호출
            switch (gameState->scenarioNumber) {
                case 1: ending1(isCorrect); break;
                case 2: ending2(isCorrect); break;
                case 3: ending3(isCorrect); break;
                default: printf("알 수 없는 시나리오입니다.\n"); break;
            }

            int a;
            printf("\n다른 시나리오 게임을 진행하시겠습니까? (1)Yes (2)No\n");
            printf("입력: ");
            scanf("%d", &a);
            getchar();  // 개행 문자 제거

            return (a == 1) ? 1 : 0;
        }
    }

    printf("해당 이름의 용의자가 존재하지 않습니다.\n");
    return 0;
}
