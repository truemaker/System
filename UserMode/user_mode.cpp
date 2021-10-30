void user_ok() {
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 4);
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    print_raw(tty_buffer);
}

void setup_user_mode() {
    tty_out("Starting Services...");
    user_ok();
    tty_out("Starting Login...");
    sleep(1);
}

void start_user_mode() {
    tty_clear();
    tty_out((char*)"Login: ");
}