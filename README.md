Amplifier Simulator Plugin

🎯 프로젝트 개요

Amplifier Simulator Plugin은 JUCE 프레임워크를 사용하여 개발 중인 오디오 플러그인 프로젝트입니다. 이 플러그인은 사용자가 기타 및 베이스 톤을 시뮬레이션하고 조정할 수 있도록 설계되었습니다.
프로젝트의 주요 목표는 직관적인 사용자 경험과 고품질 오디오 처리를 제공하는 것입니다.
🛠️ 개발 워크플로

1. GitHub 푸시 정책
빌드 성공 시:
모든 코드가 정상적으로 빌드되고 테스트를 통과했을 때만 main 브랜치에 푸시합니다.
빌드 실패 시:
빌드 실패 원인을 분석하고 수정한 뒤, 재검토 후 푸시합니다.
2. 빌드 실패 시 처리 방법
Jira:
빌드 실패가 발생한 경우, Jira에 새로운 버그 이슈를 생성합니다.
이슈에는 다음 정보를 포함합니다:
실패한 상황 설명.
발생한 에러 로그.
수정이 필요한 파일 및 예상 원인.
Notion:
버그 수정 후 해결 과정을 Notion의 "JUCE Bug Collection" 페이지에 기록합니다. (https://www.notion.so/JUCE-Bug-Collection-18997902a73b808d8eb8d32e2eb9d1b5)
기록에는 다음 정보를 포함합니다:
문제의 원인 및 해결 방법.
참고한 리소스 또는 추가 메모.
📝 규칙 및 참고사항

코드 관리 규칙
빌드 및 테스트 환경
IDE: Xcode (Mac) / Visual Studio (Windows)
JUCE 버전: 8.0.2
지원 플랫폼: macOS, Windows
