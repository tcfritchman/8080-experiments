void set_reg_b(char new_val);

void set_reg_c(char new_val);

void set_reg_d(char new_val);

void set_reg_e(char new_val);

void set_reg_h(char new_val);

void set_reg_l(char new_val);

void set_reg_a(char new_val);

void set_sp(unsigned short new_val);

void set_pc(unsigned short new_val);

void set_sign(int new_val);

void set_zero(int new_val);

void set_parity(int new_val);

void set_carry(int new_val);

void set_aux_carry(int new_val);

void set_mem_byte(unsigned short mem_location, char new_val);

//void set_mem_word(short mem_location, char new_val);

void copy_to_mem(unsigned short mem_location,
  unsigned short data_length, char *data);

char get_reg_b();

char get_reg_c();

char get_reg_d();

char get_reg_e();

char get_reg_h();

char get_reg_l();

char get_reg_a();

unsigned short get_sp();

unsigned short get_pc();

int get_sign();

int get_zero();

int get_parity();

int get_carry();

int get_aux_carry();

char get_mem_byte(unsigned short mem_location);
