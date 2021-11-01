#include "Services/cinit.cpp"
#include "Services/user_manager.cpp"

void start_cinit() {
    tty_out((char*)"Starting cinit...");
    cinit_running = 1;
}

void start_user_manager() {
    tty_out((char*)"Starting user manager...");
    user_manager_running = 1;
}

void startup_all_services() {
    user_ok();
    start_cinit();
    user_ok();
    start_user_manager();
    user_ok();
}