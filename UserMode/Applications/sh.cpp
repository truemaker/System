extern void start_shutdown();

uint8 sh_should_exit = 0;

void start_sh();

void sh_exit() {
    sh_should_exit = 1;
}

void sh_command_prompt(uint8* user) {
    outu(user);
    out("@myos$ ");
}

uint8 sh_command_execute(uint8* command) {
    uint8* name = (uint8*)umalloc(255);
    uint8* args = (uint8*)umalloc(255);
    uint8 executed = 0;
    uint8 is_command = 1;
    uint8 is_args = 0;
    int start_args = 0;
    if (strlen((char*)command) > 0) {
        for (int i = 0; i < strlen((char*)command); i++) {
            if (command[i] == ' ' && is_command == 1) {
                is_command = 0;
                is_args = 1;
                start_args = i + 1;
            }
            if (is_command == 1) {
                name[i] = command[i];
            } else if (is_args == 1) {
                args[i - start_args] = command[i];
            }
        }
        uint8* processed_name = (uint8*)umalloc(strlen((char*)name) + 1);
        umemcut(name);
        for (int i = 0; i < strlen((char*)name); i++) {
            processed_name[i] = name[i];
        }
        if (strcompare((char*)processed_name, (char*)"shutdown")) {
            executed = 1;
            start_shutdown();
        }
        if (strcompare((char*)processed_name, (char*)"exit")) {
            executed = 1;
            start_exit();
        }
        if (strcompare((char*)processed_name, (char*)"sh")) {
            executed = 1;
            start_sh();
        }
        if (strcompare((char*)processed_name, (char*)"tty")) {
            executed = 1;
            start_tty(args);
        }
        if (strcompare((char*)processed_name, (char*)"desktop")) {
            executed = 1;
            start_desktop();
        }
        if (executed == 1) {
        } else {
            out("Could not find command: ");
            outu(processed_name);
            out("\n");
        }
        umemcut(processed_name);
    }
    umemcut(args);
    return 0;
}

void start_sh() {
    out("\n");
    uint8* user = user_manager_get_user();
    uint8 exit_code;
    while (sh_should_exit == 0) {
        if (*tty_pos > 2000 - 160) {
            tty_clear();
        }
        sh_command_prompt(user);
        uint8* cmd = inputk();
        if (strlen((char*)cmd) > 0) {
            out("\n");
        }
        exit_code = sh_command_execute(cmd);
    }
    sh_should_exit = 0;
}