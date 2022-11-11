#include "signals.h"

void sig_init(void)
{
	g_sig.signum = 0;
	g_sig.current_proc.exit_status = 0;
	g_sig.current_proc.pid = 0;
}
