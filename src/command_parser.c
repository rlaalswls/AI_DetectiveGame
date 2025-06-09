#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_structs.h"
#include "command_parser.h"

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
        return continueGame;
    } else if (strcmp(input, "!도움말") == 0) {
        printf("!!이동 [장소], !조사 [증거명], !심문 [용의자], !추궁 [용의자], !증거, !지목 [용의자], !도움말, !종료\n");
    } else {
        printf("알 수 없는 명령입니다.\n");
    }
    return 0;
}

void moveToLocation(GameState *game, const char *locationName) {
    Location* loc = game->locations;
    while (loc) {
        if (strcmp(loc->name, locationName) == 0) {
            strcpy(game->currentLocationName, loc->name);
            printf("'%s'(으)로 이동한다.\n", locationName);

            if (!loc->evidences) {
                printf("이 장소에는 아무 단서가 보이지 않는다.\n");
            } else {
                printf("이 장소에 있는 단서들:\n");
                Evidence* evi = loc->evidences;
                while (evi) {
                    printf("- %s\n", evi->name);
                    evi = evi->next;
                }
            }
            return;
        }
        loc = loc->next;
    }
    printf("해당 장소를 찾을 수 없습니다: %s\n", locationName);
}

void investigateLocation(GameState *game, const char *evidenceName) {
    Location* loc = game->locations;
    while (loc) {
        if (strcmp(loc->name, game->currentLocationName) == 0) {
            Evidence* evi = loc->evidences;
            while (evi) {
                if (strcmp(evi->name, evidenceName) == 0) {
                    if (!evi->found) {
                        evi->found = 1;
                        printf("새로운 증거를 발견했다!\n %s: %s\n", evi->name, evi->description);
                    } else {
                        printf("이미 조사한 증거다.\n");
                    }
                    return;
                }
                evi = evi->next;
            }
            printf("이 장소에 '%s'라는 증거는 없습니다.\n", evidenceName);
            return;
        }
        loc = loc->next;
    }
    printf("현재 위치를 찾을 수 없습니다.\n");
}

void listFoundEvidence(GameState *game) {
    Evidence* evi = game->allEvidences;
    int foundAny = 0;
    printf("<발견한 증거 목록>\n");
    while (evi) {
        if (evi->found) {
            printf("- %s : %s\n", evi->name, evi->description);
            foundAny = 1;
        }
        evi = evi->next;
    }
    if (!foundAny) {
        printf("아직 증거를 발견하지 못했다.\n");
    }
}

void interrogateSuspect(GameState *game, const char *suspectName) {
    Suspect* suspect = game->suspects;
    while (suspect) {
        if (strcmp(suspect->name, suspectName) == 0) {
            if (suspect->interrogationCount >= 10) {
                printf("%s: 더 이상 질문에 답하지 않겠습니다. (묵비권 행사)\n", suspectName);
                return;
            }
            suspect->interrogationCount++;
            char question[256];
            getInput(question, sizeof(question), "용의자에게 심문하세요: ");
            FILE *qf = fopen("../AI_DetectiveGame/assets/question_interrogate.txt", "w");
            if (!qf) { perror("질문 파일 저장 실패"); return; }
            fprintf(qf, "%s\n", question);
            fclose(qf);
            char command[256];
            snprintf(command, sizeof(command), "python3 ../AI_DetectiveGame/gpt/gpt_response.py interrogate \"%s\"", suspectName);
            system(command);
            FILE *af = fopen("../AI_DetectiveGame/assets/response_interrogate.txt", "r");
            if (!af) { perror("응답 파일 열기 실패"); return; }
            char buffer[512];
            printf("용의자 %s의 응답: ", suspectName);
            while (fgets(buffer, sizeof(buffer), af)) { printf("%s", buffer); }
            fclose(af);
            return;
        }
        suspect = suspect->next;
    }
    printf("해당 용의자를 찾을 수 없습니다.\n");
}

void pressSuspect(GameState *game, const char *suspectName) {
    if (game->pressChances <= 0) {
        printf("추궁 기회를 모두 소진했습니다.\n");
        return;
    }
    Suspect* suspect = game->suspects;
    while (suspect) {
        if (strcmp(suspect->name, suspectName) == 0) {
            char question[256];
            getInput(question, sizeof(question), "용의자에게 추궁하세요: ");
            FILE *qf = fopen("../AI_DetectiveGame/assets/question_press.txt", "w");
            if (!qf) { perror("질문 파일 저장 실패"); return; }
            fprintf(qf, "%s\n", question);
            fclose(qf);
            char command[256];
            snprintf(command, sizeof(command), "python3 ../AI_DetectiveGame/gpt/gpt_response.py press \"%s\"", suspectName);
            system(command);
            FILE *af = fopen("../AI_DetectiveGame/assets/response_press.txt", "r");
            if (!af) { perror("응답 파일 열기 실패"); return; }
            
            char line[512];
            char responseText[2048] = "";
            char verdict[128] = "";
            while (fgets(line, sizeof(line), af)) {
                line[strcspn(line, "\n")] = '\0';  // 개행 제거
                if (strncmp(line, "[판단]", 9) == 0) {
                    break;
                }
                strcat(responseText, line);
                strcat(responseText, "\n");
            }

            if (fgets(line, sizeof(line), af)) {
                line[strcspn(line, "\n")] = '\0';
                snprintf(verdict, sizeof(verdict), "%s", line);
            }

            fclose(af);
            responseText[strlen(responseText) - 1] = '\0';
            printf("용의자 응답:\n%s\n", responseText);
            if (strstr(verdict, "정확한") != NULL) {
                printf("정확한 추궁입니다. 남은 기회: %d\n", game->pressChances);
            } else {
                game->pressChances--;
                printf("잘못된 추궁입니다. 남은 기회: %d\n", game->pressChances);
            }
            return;
        }
        suspect = suspect->next;
    }
    printf("해당 용의자를 찾을 수 없습니다.\n");
}

int pointOut(GameState* game, const char* suspectName) {
    Suspect* suspect = game->suspects;
    while (suspect) {
        if (strcmp(suspect->name, suspectName) == 0) {
            int isCorrect = (suspect->isCulprit == 1);
            switch (game->scenarioNumber) {
                case 1: ending1(isCorrect); break;
                case 2: ending2(isCorrect); break;
                case 3: ending3(isCorrect); break;
                default: printf("알 수 없는 시나리오입니다.\n"); break;
            }
            int a;
            printf("\n다른 시나리오 게임을 진행하시겠습니까? (1)Yes (2)No\n");
            printf("입력: ");
            scanf("%d", &a);
            getchar();
            return (a == 1) ? 1 : 0;
        }
        suspect = suspect->next;
    }
    printf("해당 이름의 용의자가 존재하지 않습니다.\n");
    return 0;
}
