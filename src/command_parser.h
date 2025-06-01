#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "game_structs.h"

void getInput(char *buffer, size_t size, const char *prompt);

// 명령어 문자열을 파싱하여 적절한 게임 함수 호출
int parseCommand(GameState *game, const char *input);

// 장소 이동 명령 처리
void moveToLocation(GameState *game, const char *locationName);

// 현재 위치 조사 명령 처리
void investigateLocation(GameState *game, const char *evidenceName);

// 발견된 증거 목록 출력
void listFoundEvidence(GameState *game);

// 용의자 심문 추궁 명령 처리
void interrogateSuspect(GameState *game, const char *suspectName);
void pressSuspect(GameState *game, const char *suspectName);

// 용의자 지목 명령 처리
int pointOut(GameState* gameState, const char* SuspectName);

#endif // COMMAND_PARSER_H
