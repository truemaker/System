void start_login() {
    tty_set(7);
}

void run_login() {
    cls();
    out("Login: ");
    uint8* user = inputk();
    out("Password: ");
    uint8* passwd = passwdk();
    out("\b");
    out("Logged in as: ");
    outu(user);
    out("\n");
    user_manager_user = user;
    start_license();
    start_sh();
}
