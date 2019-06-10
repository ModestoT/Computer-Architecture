#include "cpu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 6
#define HLT 0b00000001
#define LDI 0b10000010
#define PRN 0b01000111

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

unsigned char cpu_ram_read(struct cpu *cpu, int index)
{
  return cpu->ram[index];
};

void cpu_ram_write(struct cpu *cpu, int index, int value)
{
  cpu->ram[index] = value;
};

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char ir = cpu_ram_read(cpu, cpu->pc);
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc+1); 
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc+2);
    int val;
    int index;
    // 4. switch() over it to decide on a course of action.
    switch (ir) {
      // 5. Do whatever the instruction should do according to the spec.
      case LDI:
        index = operandA;
        val = operandB;
        cpu->registers[index] = val;
        cpu->pc+=3;
        break;
      
      case PRN:
        index = operandA;
        printf("%d\n", cpu->registers[index]);
        cpu->pc+=2;
        break;
      case HLT:
        running = 0;
        break;

      default:
        printf("Unknown instruction %02x at address %02x\n", ir, cpu->pc);
        exit(1);
      // 6. Move the PC to the next instruction.
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers

  // set cpu PC to 0
  cpu->pc = 0;
  // Set cpu registers array to be all 0's 
  memset(cpu->registers, 0, sizeof(cpu->registers));
  // set cpu Memory array to be all 0's
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
