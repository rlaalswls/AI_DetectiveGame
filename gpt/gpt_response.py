from dotenv import load_dotenv
from openai import OpenAI
import os
import sys

# (1) OpenAI API 키 입력
load_dotenv()
api_key = os.getenv("OPENAI_API_KEY")
client = OpenAI(api_key=api_key)

# (2) txt 파일 파싱 함수
def load_txt_data(filename):
    entries = []
    entry = {}
    with open(filename, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line == "---":
                entries.append(entry)
                entry = {}
            else:
                key, value = line.split(": ", 1)
                entry[key] = value
    return entries

suspects = load_txt_data("../game/assets/suspect_profiles.txt")
evidences = load_txt_data("../game/assets/evidence.txt")

# (3) 실행 인자 받기
# 예시: python3 gpt_response.py press "이유빈"
mode = sys.argv[1]  # 'press' or 'interrogate'
suspect_name = sys.argv[2]
question_file = f"../game/assets/question_{mode}.txt"
response_file = f"../game/assets/response_{mode}.txt"

# (4) 질문 읽기
with open(question_file, 'r', encoding='utf-8') as f:
    question = f.read().strip()

# (6) 시스템 프롬프트 생성 함수
def build_system_prompt(suspects, evidences, suspect_name, mode):
    
    prompt = f"""
너는 추리게임의 등장인물인 용의자 n명을 각각 연기해야해. 
아래는 게임에 등장하는 용의자 및 장소와 증거 정보야:
{suspects}
{evidences}
플레이어는 이 정보를 바탕으로 너를 심문하거나 추궁할 거야.
""".strip()

    if mode == "press":
        prompt += """

지금 너는 용의자 {suspect_name}를 연기하고 있어. 플레이어의 질문에 답해야 해.
플레이어가 너에게 예리한 추궁을 할거야.
추궁이 다음 중 하나를 충족하면 '정확한 추궁'이다:
- 증거에 기반해 진실을 지적함
- 용의자의 거짓말이나 알리바이의 허점, 수상한 점을 집어냄
- 수상한 행동과 증거의 연결을 논리적으로 집어냄

그 외에는 '잘못된 추궁'으로 간주해.

응답은 아래의 포맷을 따르라:
[응답]
(용의자의 대답)

[판단]
정확한 추궁 | 잘못된 추궁 중 하나를 선택
"""

    else:
        prompt += "\n지금 너는 용의자 {suspect_name}이야. 플레이어가 너에게 심문할 거야. 너는 이 인물을 연기해서 자연스럽게 답변해."

    return prompt

system_prompt = build_system_prompt(suspects, evidences, suspect_name, mode)

# (7) GPT 호출
response = client.chat.completions.create(
    model="gpt-3.5-turbo",
    messages=[
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": question}
    ],
    temperature=0.7,
    max_tokens=500,
)

# (8) 응답 추출 및 저장
answer = response.choices[0].message.content.strip()

with open(response_file, "w", encoding="utf-8") as f:
    f.write(answer)
