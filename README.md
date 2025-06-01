# 🕵️ AI Detective Game: CODE 404

AI 기반 C 텍스트 추리 어드벤처 게임 프로젝트입니다. 플레이어는 주어진 단서와 증거를 바탕으로 범인을 추리하게 됩니다.
An AI text-based mystery adventure game. The player investigates various locations, collects evidence, interrogates suspects, and uncovers the truth behind the incident.

## File Structure

```
game/
├── assets/              # 증거/용의자, 질문/응답 텍스트 파일 (GPT 전달용)
├── gpt/                 # GPT 응답 처리 파이썬 스크립트
├── src/                 # 메인 C 코드 및 게임 로직
└── main                 # 빌드된 실행 파일 (main)
```

## How to Run

### 1. C 코드 빌드

```bash
cd src
gcc main.c command_parser.c save_txt.c game_data1.c game_data2.c game_data3.c -o ../main
```

### 2. 게임 실행

```bash
cd ..
./main
```

### 3. GPT 연동 (필수)

```bash
pip install openai
pip install python-dotenv
```

`.env` 파일 생성 후 다음과 같이 입력:

```
OPENAI_API_KEY=your_openai_api_key_here
```

## How to Play

* 텍스트 명령어로 이동, 탐색, 증거 조사, 용의자 심문/추궁 가능
* 증거를 모아 진범을 지목하고 사건을 해결해야 함

### Command

| 명령어             | 설명                          |
| --------------- | --------------------------- |
| `!이동 장소명`      | 해당 장소로 이동                   |
| `!조사 증거명`        | 현재 장소의 증거를 조사               |
| `!증거`           | 수집한 증거 목록 확인                |
| `!심문 이름`        | 용의자에게 일반 질문 (GPT 호출)        |
| `!추궁 이름`        | 용의자를 논리적으로 압박하는 질문 (GPT 호출) |
| `!지목 이름`        | 범인을 지목하고 게임 종료 시도           |
| `!도움말`          | 명령어 요약 보기                   |
| `!종료`            | 게임 종료                       |

## Scenario

### 시나리오 1: Turth Not Found

* 장소: 대학교 공학관
* 피해자: 대학원생 김도현
* 사인: 옥상 추락사
* 난이도: Hard

### 시나리오 2: Observatory Unavailable

* 장소: 외딴 산 속 관측소
* 피해자: 천체물리학 박사 윤지훈
* 사인: 둔기 가격
* 난이도: Normal

### 시나리오 3: Unknown Coffee

* 장소: 종로구 디자인 카페
* 피해자: 사장 최서준
* 사인: 독극물 중독
* 난이도: Easy

## Data Sturtures

이 프로젝트는 **자료구조**의 실습으로, 다음 구조체를 사용하여 게임 상태를 관리합니다:

### 1. `Evidence` 구조체

```c
typedef struct {
    char name[64];
    char description[256];
    char location[64];
} Evidence;
```

### 2. `Suspect` 구조체

```c
typedef struct {
    char name[32];
    char job[64];
    char personality[128];
    char relationWithVictim[128];
    char alibi[256];
    char suspicious_points[256];
    int isCulprit;
    int interrogationCount;
} Suspect;
```

### 3. `Location` 구조체

```c
typedef struct {
    char name[64];
    int hasEvidence[MAX_EVIDENCE];
    int evidenceCount;
} Location;
```

### 4. `GameState` 구조체

```c
typedef struct {
    int evidenceCount;
    int suspectCount;
    Location locations[MAX_LOCATIONS];
    Suspect suspects[MAX_SUSPECTS];
    Evidence evidences[MAX_EVIDENCE];
    int currentLocationIndex;
    int foundEvidence[MAX_EVIDENCE];
    int pressChances;
    Suspect interrogationCount[MAX_INTERROGATIONS];
    char currentLocationName[64];
    int scenarioNumber;
} GameState;
```

이러한 구조를 통해 C 언어 기반에서 객체 지향적인 상태 관리를 구현하였으며, 텍스트 기반 인터페이스와 GPT API 연동을 조합하여 직관적인 추리 게임을 구성하였습니다.

---

🔧 개발자용 안내: `save_txt.c`에서는 구조체 데이터를 `evidence.txt`, `suspect_profiles.txt`로 저장하며, Python의 `gpt_response.py`가 이를 읽어 GPT-3.5에게 질문을 전달합니다.
