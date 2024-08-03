#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_TRANSACTION_CAPACITY 10

typedef struct Account {
    char username[20];
    char password[20];
    float balance;
    int transaction_count;
    int transaction_capacity;
    float* transactions;
    struct Account* next;
} Account;

Account* head = NULL;

void create_account() {
    Account* new_account = (Account*) malloc(sizeof(Account));
    if (new_account == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", new_account->username);
    printf("Enter password: ");
    scanf("%s", new_account->password);
    new_account->balance = 0.0;
    new_account->transaction_count = 0;
    new_account->transaction_capacity = INITIAL_TRANSACTION_CAPACITY;
    new_account->transactions = (float*) malloc(sizeof(float) * new_account->transaction_capacity);
    if (new_account->transactions == NULL) {
        printf("Memory allocation failed\n");
        free(new_account);
        return;
    }

    new_account->next = head;
    head = new_account;
    printf("Account created successfully!\n");
}

Account* authenticate() {
    char username[20];
    char password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    Account* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deposit(Account* account) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    account->balance += amount;
    if (account->transaction_count == account->transaction_capacity) {
        account->transaction_capacity *= 2;
        account->transactions = (float*) realloc(account->transactions, sizeof(float) * account->transaction_capacity);
        if (account->transactions == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    account->transactions[account->transaction_count++] = amount;
    printf("Deposit successful!\n");
}

void withdraw(Account* account) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (account->balance >= amount) {
        account->balance -= amount;
        if (account->transaction_count == account->transaction_capacity) {
            account->transaction_capacity *= 2;
            account->transactions = (float*) realloc(account->transactions, sizeof(float) * account->transaction_capacity);
            if (account->transactions == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
        }
        account->transactions[account->transaction_count++] = -amount;
        printf("Withdrawal successful!\n");
    } else {
        printf("Insufficient balance!\n");
    }
}

void check_balance(Account* account) {
    printf("Balance: %.2f\n", account->balance);
}

void transaction_history(Account* account) {
    printf("Transaction History:\n");
    for (int i = 0; i < account->transaction_count; i++) {
        printf("%+.2f\n", account->transactions[i]);
    }
}

void login() {
    Account* current = authenticate();
    if (current == NULL) {
        printf("Login failed!\n");
        return;
    }

    printf("Login successful!\n");
    int choice;
    do {
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Check Balance\n");
        printf("4. Transaction History\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit(current);
                break;
            case 2:
                withdraw(current);
                break;
            case 3:
                check_balance(current);
                break;
            case 4:
                transaction_history(current);
                break;
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
}

void free_memory() {
    Account* current = head;
    while (current != NULL) {
        Account* temp = current;
        current = current->next;
        free(temp->transactions);
        free(temp);
    }
}

int main() {
    int choice;
    while (1) {
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                login();
                break;
            case 3:
                free_memory();
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
