#include <iostream>
#include <string>

class BankAccount {
private:
    std::string ownerName = "";  // 계좌 소유자 정보는 외부에서 임의로 바꾸지 못하게 보호하기 위해 private으로 설정
    int pinCode = 0;             // 비밀번호는 민감한 정보이므로 외부에서 직접 접근하지 못하게 하기 위해 private으로 설정
                                 // 실무에서는 평문 보관 대신 해시 등 안전한 방식으로 관리해야 함
    double balance = 0.0;        // 잔액은 음수 등 잘못된 값이 직접 저장되지 않도록 보호하기 위해 private으로 설정
    bool isInitialized = false;

public:
    bool initialize(const std::string& name, int pin, double initialBalance) {
        if (isInitialized) {
            std::cout << "에러: 초기 설정은 한 번만 할 수 있습니다." << std::endl;
            return false;
        }

        if (name.empty()) {
            std::cout << "에러: 예금주 이름은 비어 있을 수 없습니다." << std::endl;
            return false;
        }

        if (pin < 1000 || pin > 9999) {
            std::cout << "에러: 비밀번호는 4자리 숫자여야 합니다." << std::endl;
            return false;
        }

        if (initialBalance < 0) {
            std::cout << "에러: 초기 잔액은 음수일 수 없습니다." << std::endl;
            return false;
        }

        ownerName = name;
        pinCode = pin;
        balance = initialBalance;
        isInitialized = true;
        return true;
    }

    bool deposit(double amount) {
        if (!isInitialized) {
            std::cout << "에러: 먼저 계좌를 초기 설정해야 합니다." << std::endl;
            return false;
        }

        if (amount <= 0) {
            std::cout << "에러: 입금액은 0보다 커야 합니다." << std::endl;
            return false;
        }

        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (!isInitialized) {
            std::cout << "에러: 먼저 계좌를 초기 설정해야 합니다." << std::endl;
            return false;
        }

        if (amount <= 0) {
            std::cout << "에러: 출금액은 0보다 커야 합니다." << std::endl;
            return false;
        }

        if (amount > balance) {
            std::cout << "에러: 잔액이 부족합니다." << std::endl;
            return false;
        }

        balance -= amount;
        return true;
    }

    void displayInfo(int inputPin) const {
        if (!isInitialized) {
            std::cout << "에러: 먼저 계좌를 초기 설정해야 합니다." << std::endl;
            return;
        }

        if (inputPin != pinCode) {
            std::cout << "에러: 비밀번호가 일치하지 않습니다." << std::endl;
            return;
        }

        std::cout << "예금주: " << ownerName << std::endl;
        std::cout << "잔액: " << balance << "원" << std::endl;
    }
};

int main() {
    BankAccount account;
    BankAccount invalidAccount;

    account.initialize("Kim", 1234, 10000);  // 정상 데이터
    account.deposit(5000);                   // 정상 데이터
    account.withdraw(3000);                  // 정상 데이터
    account.displayInfo(1234);               // 정상 데이터

    account.deposit(-1000);                  // 비정상 데이터
    account.withdraw(50000);                 // 비정상 데이터
    account.displayInfo(1111);               // 비정상 데이터
    invalidAccount.initialize("", 12, -5000);  // 비정상 데이터
    account.initialize("Lee", 5678, 5000);     // 비정상 데이터

    return 0;
}
