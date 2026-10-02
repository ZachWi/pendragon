#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define STAT_carry 0
#define STAT_zero  1
#define STAT_inter 2
#define STAT_dec   3
#define STAT_break 4
// not used... idgaf   //
#define STAT_overf 6
#define STAT_negat 7

uint8_t opcode = 0xa9;

typedef struct {
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t flags;
    uint8_t stack_p;
    uint16_t prog_c;
} CPU_t;

uint8_t init_cpu(CPU_t *cpu){
    cpu->prog_c = 0;
    cpu->flags = 4;
    return 0;
}

void check_zero(CPU_t *cpu, uint8_t val){
    if(val == 0){
        cpu->flags |= (1U << STAT_zero);
    }
    else {
        cpu->flags &= ~(1U << STAT_zero);
    }
}

void check_negat(CPU_t *cpu, uint8_t val){
    if(val >= 0x80){
        cpu->flags |= (1U << STAT_negat);
    }
    else {
        cpu->flags &= ~(1U << STAT_negat);
    }
}

uint8_t instr(CPU_t *cpu, uint8_t opcode, uint8_t val){
    switch (opcode){
        case 0x00:
            break;
        case 0x8a:
            cpu->a = cpu->x;

            break;
        case 0xa9:
            cpu->a = val;
            check_zero(cpu, val);
            check_negat(cpu, val);
            break;
        case 0xaa:
            cpu->x = cpu->a;
            check_zero(cpu, val);
            check_negat(cpu, val);
            break;
    }
    return 0;
}

int main(){
    CPU_t cpu_t;
    init_cpu(&cpu_t);
    instr(&cpu_t, opcode, 0xff);
    printf("%d\n", cpu_t.a);
    printf("%d\n", cpu_t.flags);
    return 0;
}

