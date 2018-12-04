# SEOULTECH_UnixProject_BankSystem




## 수정1차(정승진)
  - main 함수에서 if문에 wait큐가 비워져 있어도 돌아가는 버그 발생 --> if문에 wait가 비워져있으면 패스하는걸로 수정
  - bank.c Make Account 에서 같은 계좌 탐색하는것 추가
  - exit(0) 부재로 인해 함수가 두번도는 버그 해결
