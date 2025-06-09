#include <stdio.h>
#include <string.h>
#include "game_structs.h"

void saveEvidenceToFile(GameState *game, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("파일 열기 실패 (evidence)");
        return;
    }

    Evidence *e = game->allEvidences;
    while (e != NULL) {
        fprintf(fp, "이름: %s\n", e->name);
        fprintf(fp, "설명: %s\n", e->description);
        fprintf(fp, "위치: %s\n", e->location);
        fprintf(fp, "---\n");
        e = e->next;
    }

    fclose(fp);
}

void saveSuspectsToFile(GameState *game, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("파일 열기 실패 (suspect)");
        return;
    }

    Suspect *s = game->suspects;
    while (s != NULL) {
        fprintf(fp, "이름: %s\n", s->name);
        fprintf(fp, "직업: %s\n", s->job);
        fprintf(fp, "성격: %s\n", s->personality);
        fprintf(fp, "피해자와의 관계: %s\n", s->relationWithVictim);
        fprintf(fp, "알리바이: %s\n", s->alibi);
        fprintf(fp, "수상한 점: %s\n", s->suspicious_points);
        fprintf(fp, "범인 여부: %s\n", s->isCulprit ? "범인" : "아님");
        fprintf(fp, "---\n");
        s = s->next;
    }
    
    fclose(fp);
}
