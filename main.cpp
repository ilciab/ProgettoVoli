#include <iostream>

#include "ui/CLI.h"
#include "service/AuthService.h"
using namespace std;

bool signIn(){
    string name, email, hashedPassword;
}



int main() {
    UserRepository userRepo(std::string("users.txt"));
    AuthService authService(userRepo);
    CLI cli(authService);
    cli.menu();
    return 0;
}
