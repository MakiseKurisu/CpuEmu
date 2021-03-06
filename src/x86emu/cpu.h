﻿#ifndef _CPUEMU_X86EMU_X86_H_
#define _CPUEMU_X86EMU_X86_H_

#define CPU_X86_16BITS          0x01
#define CPU_X86_32BITS          0x02
#define CPU_X86_64BITS          0x04

typedef struct
{
    LPBYTE  lpInstruction;
    SIZE_T  nInstructionSize;
    SIZE_T  nCpuStatus;
    SIZE_T  nLegacyPrefix;
    SIZE_T  nExtendedPrefix;
    SIZE_T  nOpcode;
    SIZE_T  nAddressingByte;
    SIZE_T  nDisplacement;
    SIZE_T  nImmediate;
} DECODE_STATUS_X86, *LPDECODE_STATUS_X86;

#define OPCODE_X86_INVAILD              0x00000000
#define OPCODE_X86_16BITS_VAILD         0x00000001
#define OPCODE_X86_32BITS_VAILD         0x00000002
#define OPCODE_X86_64BITS_VAILD         0x00000004
#define OPCODE_X86_LEGACY_VAILD         OPCODE_X86_16BITS_VAILD | OPCODE_X86_32BITS_VAILD
#define OPCODE_X86_VAILD                OPCODE_X86_LEGACY_VAILD | OPCODE_X86_64BITS_VAILD

#define OPCODE_X86_PREFIX               0x00000008

#define OPCODE_X86_IMMEDIATE_NONE       0x00000000
#define OPCODE_X86_IMMEDIATE_BYTE       0x00000010
#define OPCODE_X86_IMMEDIATE_WORD       0x00000020
#define OPCODE_X86_IMMEDIATE_DWORD      0x00000040
#define OPCODE_X86_IMMEDIATE_QWORD      0x00000080
#define OPCODE_X86_IMMEDIATE_DB_DW      0x00000100
#define OPCODE_X86_IMMEDIATE_DW_DD      0x00000200
#define OPCODE_X86_IMMEDIATE_DD_DQ      0x00000400
#define OPCODE_X86_IMMEDIATE_DW_DD_DQ   0x00000800
#define OPCODE_X86_IMMEDIATE_FIXED      OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_IMMEDIATE_WORD | OPCODE_X86_IMMEDIATE_DWORD | OPCODE_X86_IMMEDIATE_QWORD
#define OPCODE_X86_IMMEDIATE_FLEXIBLE   OPCODE_X86_IMMEDIATE_DB_DW | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_IMMEDIATE_DD_DQ | OPCODE_X86_IMMEDIATE_DW_DD_DQ
#define OPCODE_X86_IMMEDIATE_EXIST      OPCODE_X86_IMMEDIATE_FIXED | OPCODE_X86_IMMEDIATE_FLEXIBLE
#define OPCODE_X86_IMMEDIATE_FARPTR     0x10000001
#define OPCODE_X86_IMMEDIATE_3_BYTE     0x10000002

#define OPCODE_X86_OPERAND_NONE         0x00000000
#define OPCODE_X86_OPERAND_BYTE         0x00001000
#define OPCODE_X86_OPERAND_WORD         0x00002000
#define OPCODE_X86_OPERAND_DWORD        0x00004000
#define OPCODE_X86_OPERAND_QWORD        0x00008000
#define OPCODE_X86_OPERAND_DB_DW        0x00010000
#define OPCODE_X86_OPERAND_DW_DD        0x00020000
#define OPCODE_X86_OPERAND_DD_DQ        0x00040000
#define OPCODE_X86_OPERAND_DW_DD_DQ     0x00080000
#define OPCODE_X86_OPERAND_FIXED        OPCODE_X86_OPERAND_BYTE | OPCODE_X86_OPERAND_WORD | OPCODE_X86_OPERAND_DWORD | OPCODE_X86_OPERAND_QWORD
#define OPCODE_X86_OPERAND_FLEXIBLE     OPCODE_X86_OPERAND_DB_DW | OPCODE_X86_OPERAND_DW_DD | OPCODE_X86_OPERAND_DD_DQ | OPCODE_X86_OPERAND_DW_DD_DQ
#define OPCODE_X86_OPERAND_EXIST        OPCODE_X86_OPERAND_FIXED | OPCODE_X86_OPERAND_FLEXIBLE
#define OPCODE_X86_OPERAND_DW_DQ        0x10000001

#define OPCODE_X86_MODRM_NONE           0x00000000
#define OPCODE_X86_MODRM_OPCODE         0x00000001
#define OPCODE_X86_MODRM_REG            0x00000002
#define OPCODE_X86_MODRM_REG_MEM        0x00000004
#define OPCODE_X86_MODRM_SEGMENT_REG    0x00000008
#define OPCODE_X86_MODRM_EXIST          0x00100000

#define OPCODE_X86_DIRECTION            0x00200000
#define OPCODE_X86_DIRECTION_BIT        0x00200000

typedef struct
{
    TCHAR   szInstruction[32];
    BYTE    nOpcode;
    BYTE    Opcode[3];
    DWORD   Flags;
} OPCODE_INFO_X86, *LPOPCODE_INFO_X86;

typedef struct
{
    LPCTSTR lpszMnemonic;
    SIZE_T  nOpcode;
    BYTE    Opcode[3];
    DWORD   fValid;
    DWORD   fModRM;
    DWORD   fOperand;
    DWORD   fImmediate;
} OPCODE_X86, *LPOPCODE_X86;

extern  BYTE LegacyPrefixMap[256];
extern  OPCODE_INFO_X86 OpcodeMap32[4][256];
extern  LPOPCODE_X86 OpcodeMap1[256];

#endif  /* _CPUEMU_X86EMU_X86_H_ */