int start_tty(uint8* args) {
    tty_set(args[0]);
    return 0;
}