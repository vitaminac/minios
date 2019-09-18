#include "cpu/types.h"

nat8 port_byte_in(nat16 port);
void port_byte_out (nat16 port, nat8 data);
nat16 port_word_in (nat16 port);
void port_word_out (nat16 port, nat16 data);