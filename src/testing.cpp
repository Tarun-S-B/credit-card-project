#include <bits/stdc++.h>
using namespace std;

int randomNum() {
    return rand() % 10;
}

class INVALID_PIN: public runtime_error {
    public:
        INVALID_PIN(): runtime_error("PIN entered is not in format") {}
};

class INCORRECT_PIN_ERROR: public runtime_error {
    public:
        INCORRECT_PIN_ERROR(): runtime_error("PIN Mismatch") {}
};

class INSUFFICIENT_BALANCE: public runtime_error {
    public:
        INSUFFICIENT_BALANCE(): runtime_error("Insufficient Amount") {}
};

class NO_CARD: public runtime_error {
    public:
        NO_CARD(): runtime_error("No Credit Card Issued") {}
};


class Transaction {
    public:
        string To;
        double amt;
        
        Transaction(string receiver, double amount): To(receiver),amt(amount) {}
};


class CreditCard {
    protected:
        string cardNo;
        int cvv;
        int PIN;

    public:
        double spendLimit;
        double outstandingBalance;
        string expiryDate;
        double multipler;
        vector<Transaction> statement;

    friend int randomNum();

    CreditCard() {
        PIN = -1;

        for (int x = 0; x < 16; x++)
            cardNo.append(to_string(randomNum()));

        string temp = "";
        for (int x = 0; x < 3; x++)
            temp.append(to_string(randomNum()));
        cvv = stoi(temp);

        expiryDate = expireDate();
    }

    virtual void cardDetails() const = 0; // Pure virtual function

    void genaratePIN() {
        int tempPIN;

        if (PIN == -1) {
            try {
                cout << "Enter New PIN: " << endl;
                cin >> tempPIN;
                if (tempPIN < 1000 || tempPIN > 9999)
                    throw INVALID_PIN();
                else {
                    PIN = tempPIN;
                }
            }
            catch (INVALID_PIN& e) {
                cout << e.what() << endl;
            }
        }
        else {
            cout << "PIN ALREADY GENERATED" << endl;
        }
    }

    void changePIN() {
        int tempPIN;
        try {
            cout << "Enter Current PIN: ";
            cin >> tempPIN;
            if (PIN != tempPIN)
                throw INCORRECT_PIN_ERROR();
            else {
                cout << "Enter New PIN: ";
                cin >> tempPIN;
                if (tempPIN < 1000 || tempPIN > 9999)
                    throw INVALID_PIN();
                else {
                    PIN = tempPIN;
                }
            }
        }
        catch (INCORRECT_PIN_ERROR& e) {
            cout << e.what() << endl;
        }
        catch (INVALID_PIN& e) {
            cout << e.what() << endl;
        }
    }

    string expireDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        int year = 1900 + ltm->tm_year + 5;
        int month = 1 + ltm->tm_mon;

        string expDate;

        if (month < 10) {
            expDate = "0" + to_string(month);
        }
        else {
            expDate = to_string(month);
        }
        expDate.append("/");
        expDate.append(to_string(year).substr(2, 2));
        return expDate;
    }

    void Statement() const {
        int x = statement.size();
        for (int i = 0; i < x; i++) {
            cout << "Transaction " << i + 1 << ": " << statement[i].To << " - $" << statement[i].amt << endl;
        }
    }
};

class SilverCard: public CreditCard {
    public:
        string cName;
        int rewardPoints;

        SilverCard() {
            cName = "Silver Card";
            multipler = 0.01;
            rewardPoints = 0;
            spendLimit = 20000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class GoldCard: public CreditCard {
    public:
        string cName;
        int rewardPoints;

        GoldCard() {
            cName = "Gold Card";
            multipler = 0.02;
            rewardPoints = 0;
            spendLimit = 50000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};


class PlatinumCard: public CreditCard {
    public:
        string cName;
        int rewardPoints;

        PlatinumCard() {
            cName = "Platinum Card";
            multipler = 0.05;
            rewardPoints = 0;
            spendLimit = 100000;
        }

        void cardDetails() const override {
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class CardHolder {
    public:
        string name;
        string address;
        string email;
        string phoneNo;
        vector<CreditCard*> Cards;
        CreditCard* CurrCard;
        int creditScore;

        CardHolder(string n, string a, string e, string p, int c): name(n), address(a), email(e), phoneNo(p), creditScore(c), CurrCard(nullptr) {}

        ~CardHolder() {
            for (CreditCard* card : Cards) {
                delete card;
            }
        }

        void applyCreditCard() {
            if (creditScore > 800) {
                CurrCard = new PlatinumCard();
                Cards.push_back(CurrCard);
                cout << "Platinum Card Issued:" << endl;
                CurrCard->cardDetails();
            }
            else if (creditScore > 675) {
                CurrCard = new GoldCard();
                Cards.push_back(CurrCard);
                cout << "Gold Card Issued:" << endl;
                CurrCard->cardDetails();
            }
            else {
                CurrCard = new SilverCard();
                Cards.push_back(CurrCard);
                cout << "Silver Card Issued:" << endl;
                CurrCard->cardDetails();
            }
        }

        void pay(string receiver, double amt) {
            try {
                if (CurrCard == nullptr)
                    throw NO_CARD();
                if (CurrCard->outstandingBalance + amt <= CurrCard->spendLimit) {
                    CurrCard->outstandingBalance += amt;
                    CurrCard->statement.push_back(Transaction(receiver, amt));
                    cout << "Transaction Done: " << receiver << ": $" << amt << endl;
                }
                else {
                    throw INSUFFICIENT_BALANCE();
                }
            }
            catch (INSUFFICIENT_BALANCE& e) {
                cout << "Available Limit: " << CurrCard->spendLimit - CurrCard->outstandingBalance << endl;
                cout << e.what() << endl;
            }
            catch (NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            }
        }
};

int main() {
    srand(time(0));

    CardHolder Tar("Tiger", "India", "@gmail.com", "999", 700);
    Tar.applyCreditCard();
    Tar.pay("Triumph", 25000);

    return 0;
}
