void user_ok() {
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 4);
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    print_raw(tty_buffer);
}

// Libraries
#include "Libraries/stdio.cpp"

// Services
#include "services.cpp"

// Applications
#include "Applications/exit.cpp"
#include "Applications/license.cpp"
#include "Applications/sh.cpp"
#include "Applications/login.cpp"

void setup_user_mode() {
    user_ok();
    tty_out((char*)"Switching to user mode...");
    user_ok();
    tty_out((char*)"Starting Services...");
    startup_all_services();
    tty_out((char*)"Starting Login...");
    sleep(1);
    user_ok();
    start_login();
    
}

void start_user_mode() {
    user_mode = 1;
    run_login();
    kernel_exit();
}