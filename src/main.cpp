#include<iostream>
#include<vector>
#include<exception>
#include<ctime>
#include<cstdlib>
#include<limits>
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

class INELIGIBLE_LIMIT_INCREMENT: public runtime_error {
    public:
        INELIGIBLE_LIMIT_INCREMENT(): runtime_error("Spend More on Credit to be eligible for Spend Limit INcrement") {}
};

class DUE_PENDING: public runtime_error {
    public:
        DUE_PENDING(): runtime_error("Pay the Due Amount Before Surrendering") {}
};

class INVALID_INPUT: public runtime_error {
    public:
        INVALID_INPUT(): runtime_error("Please enter Valid Input") {}
};


void giveChoices();
void cardActions();


class Transaction {
    public:
        string To;
        double amt;
        
        Transaction(string receiver, double amount): To(receiver),amt(amount) {}
};


class CreditCard {
    protected:
        int cvv;
        //string bankName;
        // int PIN;

    public:
        int PIN;
        string cardNo;
        string cName;
        double multipler;
        double spendLimit;
        double outstandingBalance;
        string expiryDate;
        vector <Transaction> statement;
        int rewardPoints;

    friend int randomNum();

    CreditCard()
    {
        outstandingBalance = 0;
        //Name of Bank
        //bankName = bName;
        // PIN = -1;

        //CARD NUMBER GENERATION
        for (int x=0; x<16; x++)
            cardNo.append(to_string(randomNum()));

        //CVV GENERATION
        string temp = "";
        for (int x=0; x<3; x++)
            temp.append(to_string(randomNum()));
        cvv = stoi(temp);

        
        //EXPIRE DATE
        expiryDate = expireDate();
    }

    virtual void cardDetails() const {
        cout << "Card No: " << cardNo << endl;
        cout << "CVV: " << cvv << endl;
        cout << "Exp Date: " << expiryDate << endl;
        cout << "Spend Limit: " << spendLimit << endl;
        cout << "Outstanding Balance: " << outstandingBalance << endl;
    }

    void genaratePIN() {
        // code to generate pin for credit card
        // change the pin
        int tempPIN;
            try {
                cout << "Enter New PIN: " << endl;
                // cin.ignore();
                cin >> this->PIN;
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                if(PIN<=0 || PIN>9999) 
                    throw INVALID_PIN();           //EXCEPTION EXCEPTION EXCEPTION
            }
            catch(INVALID_PIN& e) {
                cout << e.what() << endl;
            }   
    }

    void changePIN() {
        int tempPIN;
            try {
                cout << "Enter Current PIN: ";
                cin >> tempPIN;
                if(PIN != tempPIN) 
                    throw INCORRECT_PIN_ERROR();    
                else {
                    cout << "Enter New PIN: ";
                    cin >> tempPIN;
                    if(PIN<1000 || PIN>9999) 
                        throw INVALID_PIN();        
                    else {
                        PIN = tempPIN;
                    }
                }
            }
            catch(INCORRECT_PIN_ERROR& e) {
                cout << e.what() << endl;
            }
            catch(INVALID_PIN& e) {
                cout << e.what() << endl;
            }
    }

    string expireDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int year = 1900 + ltm->tm_year + 5; // assuming the credit card validity is 5 years;
        int month = 1 + ltm->tm_mon;

        string expDate;

        if (month < 10)
        {
            expDate = "0" + to_string(month);
        }
        else
        {
            expDate = to_string(month);
        }
        expDate.append("/"); // expDate += '/';
        expDate.append(to_string(year).substr(2, 4));
        return expDate;
    }

    double Statement() {
        int x = statement.size();
        double totalSpend = 0;
        for(int i=0; i<x; i++) {
            cout << statement[i].To << ": ";
            cout << statement[i].amt << endl;
            if(statement[i].To != "Repay Due Amount")
                totalSpend += statement[i].amt;
        }
        return totalSpend;
    }

    int getPIN() {
        return PIN;
    }

};

class SilverCard: public CreditCard {
    public:
            SilverCard() {
            cName = "Silver Card";
            multipler = 0.01;
            rewardPoints = 0;
            spendLimit = 20000;
        }

        void cardDetails() const override{
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};

class GoldCard: public CreditCard {
    public:
        GoldCard() {
            cName = "Gold Card";
            multipler = 0.02;
            rewardPoints = 0;
            spendLimit = 50000;
        }

        void cardDetails() const override{
            cout << "Card No: " << cardNo << endl;
            cout << "CVV: " << cvv << endl;
            cout << "Exp Date: " << expiryDate << endl;
            cout << "Spend Limit: " << spendLimit << endl;
            cout << "Reward Points: " << rewardPoints << endl;
        }
};


class PlatinumCard: public CreditCard {
    public:
        PlatinumCard() {
            cName = "Platinum Card";
            multipler = 0.05;
            rewardPoints = 0;
            spendLimit = 100000;
        }

        void cardDetails() const override{
            // cout << "Card Type: " << cName << endl;
            // CreditCard::cardDetails();
            // cout << "Reward Points: " << rewardPoints << endl
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

        CardHolder(string n, string a, string e, string p, int c): name(n), address(a), email(e), phoneNo(p), creditScore(c) {}

        ~CardHolder() {
            for(int i=0; i<Cards.size(); i++) {
                dropCard(i);
            }
        }

        void applyCreditCard() {
            if(creditScore>800) {
                CurrCard = new PlatinumCard();
                Cards.push_back(CurrCard);
                //CurrCard = &Cards[Cards.size()-1];
                CurrCard->genaratePIN();
                cout << "Platinum Card Issued:" << endl;
                CurrCard->cardDetails();
            }
            else if(creditScore>675) {
                CurrCard = new GoldCard();
                Cards.push_back(CurrCard);
                // CurrCard = &Cards[Cards.size()-1];
                CurrCard->genaratePIN();
                cout << "Gold Card Issued:" << endl;
                CurrCard->cardDetails();
            }
            else {
                CurrCard = new SilverCard();
                Cards.push_back(CurrCard);
                // CurrCard = &Cards[Cards.size()-1];
                CurrCard->genaratePIN();
                cout << "Silver Card Issued:" << endl;
                CurrCard->cardDetails();
            }
        }

        void pay(string receiver, double amt) {
            int cardPin;
            cout << "IN PAY PIN is " << CurrCard->getPIN();
            try {
                if(CurrCard == nullptr) 
                    throw NO_CARD();

                cout << "Enter PIN:" << endl;
                cin >> cardPin;
                if(cardPin != CurrCard->getPIN())
                    throw INCORRECT_PIN_ERROR();

                if(CurrCard->outstandingBalance + amt <= CurrCard->spendLimit) {
                    CurrCard->outstandingBalance += amt;
                    CurrCard->statement.push_back(Transaction(receiver,amt));
                    cout << "Transaction Done: " << receiver << ": " << amt << endl;
                    CurrCard->rewardPoints += amt * CurrCard->multipler;
                }
                else {
                    throw INSUFFICIENT_BALANCE();
                }
            }
            catch(INSUFFICIENT_BALANCE& e) {
                cout << "Available Limit: " << CurrCard->spendLimit - CurrCard->outstandingBalance << endl;
                cout << e.what() << endl;
            }
            catch(NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            }
            catch(INCORRECT_PIN_ERROR& e) {
                cout << e.what() << endl;
                cout << "Transaction Failed" << endl;
            }
        }

        void displayCards() {
            cout << "Displaying the list of cards:" << endl;
            for(int i=0; i<Cards.size(); i++) {
                cout << i+1 << endl;
                cout << "\t" << "Card Name:  " << Cards[i]->cName << endl;
                cout << "\t" << "Card No:    " << Cards[i]->cardNo << endl;
                cout << "\t" << "Card Limit: " << Cards[i]->spendLimit << endl;
            }
        }
        
        void displayCurrCard() {
            try {
                if(CurrCard == NULL) 
                    throw NO_CARD();
                else {
                    cout << "Details of Current Card" << endl;
                    CurrCard->cardDetails();
                }
            }
            catch(NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            }
        }

        void switchCard() {
            try {
                if(CurrCard == NULL) 
                    throw NO_CARD();
                else {
                    displayCards();
                    int srNo;
                    cout << "Enter Card Serial Number: " << endl;
                    cin >> srNo;
                    CurrCard = Cards[srNo-1];
                }
            }
            catch(NO_CARD& e) {
                cout << e.what() << endl;
                cout << "Use .applyCreditCard() method" << endl;
            }
        } 

        void repay() {
            CurrCard->statement.push_back(Transaction("Repay Due Amount",CurrCard->outstandingBalance));
            cout << "Repaid the Due Amount: " << CurrCard->outstandingBalance << endl;
            CurrCard->outstandingBalance = 0;
        }

        void increaseLimit() {
            double totalSpend = CurrCard->Statement();
            try {
                if(totalSpend >= (5*CurrCard->spendLimit)) {
                    cout << "Limit: " << CurrCard->spendLimit << "-> ";
                    CurrCard->spendLimit *= 1.5;
                    cout << CurrCard->spendLimit << endl;
                }
                else 
                    throw INELIGIBLE_LIMIT_INCREMENT();
            }
            catch (INELIGIBLE_LIMIT_INCREMENT& e) {
                cout << e.what() << endl;
            }
        }

        void viewStatement() {
            cout << endl << "Card spends: " << endl;
            CurrCard->Statement();
        }

        void useRewards() {
            CurrCard->outstandingBalance -= CurrCard->rewardPoints;
            cout << "Used: " << CurrCard->rewardPoints << "towards due repay" << endl;
            CurrCard->statement.push_back(Transaction("Repay Due Amount",CurrCard->rewardPoints));
            CurrCard->rewardPoints = 0;
        }

        void dropCard(int x) {
            CurrCard = Cards[x];
            try {
                if(CurrCard->outstandingBalance != 0) {
                    throw DUE_PENDING();
                }
                else {
                    free(Cards[x]);
                    Cards.erase(Cards.begin() + x);
                    cout << "Card Surrendered" << endl;
                }
            }
            catch (DUE_PENDING& e) {
                cout << e.what() << endl;
            }
        }

        void surrenderCard() {
            displayCards();
            int srNo;
            cout << "Enter Card Serial Number you want to Surrender: " << endl;
            cin >> srNo;
            try {
                if(srNo > Cards.size() || srNo<=0) {
                    throw INVALID_INPUT();
                }
                else 
                    dropCard(srNo-1);
            }
            catch(INVALID_INPUT& e) {
                cout << e.what() << endl;
            }

            // CurrCard=Cards[srNo-1];
            // try {
            //     if(CurrCard->outstandingBalance != 0) {
            //         throw DUE_PENDING();
            //     }
            //     else {
            //         free(Cards[srNo-1]);
            //         Cards.erase(Cards.begin() + srNo - 1);
            //         cout << "Card Surrendered" << endl;
            //     }
            // }
            // catch (DUE_PENDING& e) {
            //     cout << e.what() << endl;
            // }
        }

};

class System {


};

int main()
{
//     CardHolder Tar("Tiger", "India", "@gmail.com", "999", 700);
//     Tar.applyCreditCard();
//     Tar.displayCurrCard();
//     Tar.repay();
//     Tar.surrenderCard();
    // Tar.pay("Triumph", 25000);
    // Tar.pay("Axor", 5000);
    // Tar.pay("Triumph", 50000);
    // Tar.repay();
    // Tar.pay("Clan", 50000);
    // Tar.repay();
    // Tar.pay("Clan", 50000);
    // Tar.repay();
    // Tar.pay("Clan", 50000);
    // Tar.repay();
    // Tar.pay("Clan", 50000);
    // Tar.repay();
    // Tar.increaseLimit();
    // Tar.applyCreditCard();
    // Tar.viewStatement();
    // Tar.displayCards();

    int ch;
    int cardCh = 1;
    vector <CardHolder*> Users;
    string name, address, email, phoneNum,receiver;
    int creditScore;
    double amt;

    CardHolder* user = NULL;

    while(1) {
        giveChoices();
        cin >> ch;

        switch(ch) {
            case 1: cout << "Name: ";
                    cin.ignore();
                    getline(cin, name);
                    
                    cout << "Address: ";
                    cin.ignore();
                    getline(cin, address);

                    cout << "Email: ";
                    cin >> email;

                    cout << "Phone No: ";
                    cin >> phoneNum;

                    cout << "Credit Score: ";
                    cin >> creditScore;

                    user = new CardHolder(name, address, email, phoneNum, creditScore);
                    Users.push_back(user);
                    break;

            case 2: if(user == nullptr) {
                        cout << "Add User First" << endl;
                        break;
                    }
            
                    while(cardCh>0 && cardCh<=11) {
                        cardActions();
                        cin >> cardCh;

                        switch(cardCh) {
                            case 1: user->applyCreditCard();
                                    break;

                            case 2: if(user->CurrCard == nullptr) {
                                        cout << "Apply for Card" << endl;
                                        break;
                                    }
                                    cout << "Enter Receiver: ";
                                    cin >> receiver;
                                    cout << "Enter Amount: ";
                                    cin >> amt;
                                    user->pay(receiver,amt);
                                    break;

                            case 3: user->displayCards();
                                    break;

                            case 4: user->displayCurrCard();
                                    break;

                            case 5: user->switchCard();
                                    break;

                            case 6: user->repay();
                                    break;

                            case 7: user->increaseLimit();
                                    break;

                            case 8: user->viewStatement();
                                    break;

                            case 9: user->useRewards();
                                    break;

                            case 10: user->surrenderCard();
                                    break;

                            case 11: user->CurrCard->changePIN();
                                    break;

                            default: break;
                        }
                    }
        }
    }
    return 0;
}

    
        // void applyCreditCard() {
        // void pay(string receiver, double amt) 
        // void displayCards() {    
        // void displayCurrCard() {
        // void switchCard() {
        // void repay() {
        // void increaseLimit() {
        // void viewStatement() {
        // void useRewards() {
        // void surrenderCard() {


void cardActions() {
    cout << "1. Apply For Credit Card" << endl;
    cout << "2. Make Payment" << endl;
    cout << "3. Display Cards" << endl;
    cout << "4. Display Current Card" << endl;
    cout << "5. Switch Card" << endl;
    cout << "6. Repay Due Amount" << endl;
    cout << "7. Limit Increment Appeal" << endl;
    cout << "8. View Statement" << endl;
    cout << "9. Redeem Reward Points" << endl;
    cout << "10.Surrender Card" << endl;
    cout << "11.Change Card PIN" << endl;

    cout << endl << "Enter Action: ";
    //cout << "11.Go Back" << endl;
}

void giveChoices() {
    cout << "1. Add User" << endl;
    cout << "2. Card Transaction" << endl;
}
