void sh_command_prompt(uint8* user) {
    outu(user);
    out("@myos$ ");
}

uint8 sh_command_execute(uint8* command) {
    uint8* name = (uint8*)kmalloc(255);
    uint8* args = (uint8*)kmalloc(255);
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
        out("Command: ");
        outu(name);
        out(" with argument(s): ");
        outu(args);
        out("\n");
    }
    return 0;
}

void start_sh() {
    out("\n");
    uint8* user = user_manager_get_user();
    uint8 exit_code;
    while (1) {
        sh_command_prompt(user);
        uint8* cmd = inputk();
        out("\n");
        exit_code = sh_command_execute(cmd);
    }
}