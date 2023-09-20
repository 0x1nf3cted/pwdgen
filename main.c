#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(char list[], int n) {
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        swap(&list[i], &list[j]);
    }
}

bool isDuplicate(const char *str, char c, int endIndex) {
    for (int i = 0; i < endIndex; i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}

void removeDuplicates(char *str) {
    if (str == NULL) {
        return;
    }

    int len = strlen(str);
    if (len <= 1) {
        return;
    }

    int currentIndex = 1;
    for (int i = 1; i < len; i++) {
        if (!isDuplicate(str, str[i], currentIndex)) {
            str[currentIndex] = str[i];
            currentIndex++;
        }
    }

    str[currentIndex] = '\0';
}

char *parseRequirements(char *token) {
    removeDuplicates(token);
    char uppercase_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special_characters[] = "!@#$%^&*()-_=+[]{};:',.<>?/";

    int pwdListLen = 0;
    for (int i = 1; i < strlen(token); i++) {
        switch (token[i]) {
            case 'u':
                pwdListLen += strlen(uppercase_letters);
                break;
            case 'l':
                pwdListLen += strlen(lowercase_letters);
                break;
            case 'd':
                pwdListLen += strlen(digits);
                break;
            case 's':
                pwdListLen += strlen(special_characters);
                break;
            default:
                break;
        }
    }

    char *pwdList = malloc((pwdListLen + 1) * sizeof(char));
    if (pwdList == NULL) {
        perror("Error");
        exit(1);
    }

    strcpy(pwdList, "");  // Initialize an empty string

    for (int i = 1; i < strlen(token); i++) {
        switch (token[i]) {
            case 'u':
                strcat(pwdList, uppercase_letters);
                break;
            case 'l':
                strcat(pwdList, lowercase_letters);
                break;
            case 'd':
                strcat(pwdList, digits);
                break;
            case 's':
                strcat(pwdList, special_characters);
                break;
            default:
                break;
        }
    }

    shuffle(pwdList, pwdListLen);

    return pwdList;
}

char *generatePwd(char *charList, int length) {
    srand(time(NULL));

    char *pwd = malloc((length + 1) * sizeof(char));
    if (pwd == NULL) {
        perror("Error");
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        pwd[i] = charList[rand() % strlen(charList)];
    }
    pwd[length] = '\0'; // Null-terminate the string

    return pwd;
}

int checkPasswordStrength(const char *password) {
    int strength = 0;

    // Define password strength criteria
    int min_length = 8;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    // Get the length of the password
    int length = strlen(password);

    // Iterate through the characters in the password
    for (int i = 0; i < length; i++) {
        char c = password[i];

        // Check for uppercase letters, lowercase letters, digits, and special characters
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else {
            // Check for special characters (customize this based on your requirements)
            char special_chars[] = "!@#$%^&*()-_=+[]{};:',.<>?/";
            if (strchr(special_chars, c) != NULL) {
                has_special = true;
            }
        }
    }

    // Increase the strength score for meeting each criterion
    if (length >= min_length) {
        strength += 2;
    }
    if (has_upper) {
        strength += 2;
    }
    if (has_lower) {
        strength += 2;
    }
    if (has_digit) {
        strength += 2;
    }
    if (has_special) {
        strength += 2;
    }

    return strength;
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        perror("Not enough arguments");
        exit(1);
    }

    int length = atoi(argv[1]);

    if (length == 0) {
        perror("Error: Invalid length");
        exit(1);
    }

    if (argv[2][0] != '-') {
        perror("Error: Invalid requirements");
        exit(1);
    }

    char *charList = parseRequirements(argv[2]);
    char *pwd = generatePwd(charList, length);
    
    int strength = checkPasswordStrength(pwd);
    
    printf("Generated Password: %s\nPassword Strength: %d\n", pwd, strength);

     free(charList); // Free allocated memory for charList
    free(pwd);      // Free allocated memory for pwd

    return 0;
}
