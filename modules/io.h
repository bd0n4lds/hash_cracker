#ifndef IO_H
#define IO_H

#include <stddef.h>

/*
TODO List for io.h:

1. Logging System:
   - Define log levels enum:
     * ERROR
     * WARN
     * INFO
     * DEBUG
   
   - Declare log functions:
     * log_message(level, fmt, ...)
     * set_log_level(level)
     * set_log_file(path)

2. Progress Reporting:
   - Progress callback type
   - Update functions:
     * update_progress(done, total)
     * update_rate(attempts_per_sec)
     * update_eta(seconds)

3. State Management:
   - Save/load state:
     * save_state(path, data)
     * load_state(path)
*/

void placehorder_io(void);


#endif // IO_H
