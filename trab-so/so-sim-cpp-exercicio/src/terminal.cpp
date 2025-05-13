#include "os.h"
#include <string>

namespace Terminal {
    static std::string input_buffer;
    
    void initialize() {
        OS::cpu->write_io(IO_Port::TerminalSet, 2); // Seleciona terminal Command
        print_string("Terminal inicializado\n", 2);
    }
    
    void print_string(const std::string& s, uint8_t term_code) {
        OS::cpu->write_io(IO_Port::TerminalSet, term_code);
        for (char c : s) {
            OS::cpu->write_io(IO_Port::TerminalUpload, c);
        }
    }
    
    void process_input(char c) {
        if (c == '\n') {
            OS::execute_terminal_command(input_buffer);
            input_buffer.clear();
        } else {
            input_buffer += c;
        }
    }
}