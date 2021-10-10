void kb_install()
{
	irq_install_handler(1, keyboard_handler);
}
