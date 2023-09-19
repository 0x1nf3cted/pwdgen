# Password Generator

## Introduction

This is a simple password generator written in C. It allows you to generate random passwords based on various criteria, such as the length of the password and the types of characters to include (uppercase letters, lowercase letters, digits, and special characters).

## Usage

### Prerequisites

Before running the program, ensure that you have a C compiler installed on your system.

### Building the Program

Compile the program using a C compiler. For example, using GCC:

```shell
gcc -o main main.c
```

### Running the Program

Run the program with the desired password length and requirements. The requirements are specified as a string of flags:

-   -u: Include uppercase letters (A-Z)
    
-   -l: Include lowercase letters (a-z)

-   -d: Include digits (0-9)

-   -s: Include special characters (!@#$%^&*()-_=+[]{};:',.<>?/)


### Example usage:

./main [LENGTH] [OPTIONS]

```shell
./main 12 -ulds
```

This command will generate a random password with a length of 12 characters, including uppercase letters, lowercase letters, digits, and special characters.

## Output

The program will output the generated password to the console.

## License

This project is licensed under the MIT License.


## Contributions

This project is open for contributions! If you'd like to contribute to the development or improvement of this password generator, feel free to fork the repository and submit pull requests.

