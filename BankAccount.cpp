#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // 잔액은 외부에서 직접 수정하면 무결성이 훼손될 수 있으므로 private으로 캡슐화
    double balance = 0.0;

    // 계좌번호는 생성 후 임의로 변경되면 안 되므로 private으로 캡슐화
    string accountNumber = "";

    // 예금주 이름은 개인 정보 보호를 위해 private으로 캡슐화
    string ownerName = "";

public:
    // 계좌 초기값 설정 함수 (생성자 대신 사용)
    void setAccount(const string& name, const string& number, double initialBalance) {
        if (initialBalance < 0) {
            cout << "오류: 초기 잔액은 음수일 수 없습니다." << endl;
            return;
        }
        ownerName = name;
        accountNumber = number;
        balance = initialBalance;
    }

    // 입금 함수
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "오류: 입금액은 0보다 커야 합니다." << endl;
            return;
        }
        balance += amount;
    }

    // 출금 함수
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "오류: 출금액은 0보다 커야 합니다." << endl;
            return;
        }
        if (amount > balance) {
            cout << "오류: 잔액이 부족합니다. (현재 잔액: " << balance << "원)" << endl;
            return;
        }
        balance -= amount;
    }

    // 현재 잔액 조회 함수
    double getBalance() const {
        return balance;
    }

    // 계좌 정보 출력 함수
    void printInfo() const {
        cout << "예금주: " << ownerName
             << ", 계좌번호: " << accountNumber
             << ", 잔액: " << balance << "원" << endl;
    }
};

int main() {
    BankAccount account;

    cout << "=== 정상 데이터 테스트 ===" << endl;
    account.setAccount("홍길동", "123-456-789", 10000);
    account.printInfo();

    account.deposit(5000);
    cout << "5000원 입금 후 ";
    account.printInfo();

    account.withdraw(3000);
    cout << "3000원 출금 후 ";
    account.printInfo();

    cout << endl;
    cout << "=== 비정상 데이터 테스트 ===" << endl;

    // 음수 초기 잔액
    account.setAccount("김철수", "000-000-000", -500);

    // 0원 입금
    account.deposit(0);

    // 음수 출금
    account.withdraw(-100);

    // 잔액 초과 출금
    account.withdraw(100000);

    return 0;
}
