﻿#include    <windows.h >
#include    "cpu.h"

//Based on Intel® 64 and IA-32 Architectures Software Developer's Manual (June 2013)
LPTSTR Register[11][16] = 
{
    { TEXT("al"), TEXT("cl"), TEXT("dl"), TEXT("bl"), TEXT("ah"), TEXT("ch"), TEXT("dh"), TEXT("bh"), },
    { TEXT("al"), TEXT("cl"), TEXT("dl"), TEXT("bl"), TEXT("spl"), TEXT("bpl"), TEXT("sil"), TEXT("dil"),TEXT("r8l"), TEXT("r9l"), TEXT("r10l"), TEXT("r11l"), TEXT("r12l"), TEXT("r13l"), TEXT("r14l"), TEXT("r15l"), },
    { TEXT("ax"), TEXT("cx"), TEXT("dx"), TEXT("bx"), TEXT("sp"), TEXT("bp"), TEXT("si"), TEXT("di"), TEXT("r8w"), TEXT("r9w"), TEXT("r10w"), TEXT("r11w"), TEXT("r12w"), TEXT("r13w"), TEXT("r14w"), TEXT("r15w"), },
    { TEXT("eax"), TEXT("ecx"), TEXT("edx"), TEXT("ebx"), TEXT("esp"), TEXT("ebp"), TEXT("esi"), TEXT("edi"), TEXT("r8d"), TEXT("r9d"), TEXT("r10d"), TEXT("r11d"), TEXT("r12d"), TEXT("r13d"), TEXT("r14d"), TEXT("r15d"), },
    { TEXT("rax"), TEXT("rcx"), TEXT("rdx"), TEXT("rbx"), TEXT("rsp"), TEXT("rbp"), TEXT("rsi"), TEXT("rdi"), TEXT("r8"), TEXT("r9"), TEXT("r10"), TEXT("r11"), TEXT("r12"), TEXT("r13"), TEXT("r14"), TEXT("r15"), },
    { TEXT("st0"), TEXT("st1"), TEXT("st2"), TEXT("st3"), TEXT("st4"), TEXT("st5"), TEXT("st6"), TEXT("st7"), },
    { TEXT("mm0"), TEXT("mm1"), TEXT("mm2"), TEXT("mm3"), TEXT("mm4"), TEXT("mm5"), TEXT("mm6"), TEXT("mm7"), },
    { TEXT("xmm0"), TEXT("xmm1"), TEXT("xmm2"), TEXT("xmm3"), TEXT("xmm4"), TEXT("xmm5"), TEXT("xmm6"), TEXT("xmm7"), TEXT("xmm8"), TEXT("xmm9"), TEXT("xmm10"), TEXT("xmm11"), TEXT("xmm12"), TEXT("xmm13"), TEXT("xmm14"), TEXT("xmm15"), },
    { TEXT("ymm0"), TEXT("ymm1"), TEXT("ymm2"), TEXT("ymm3"), TEXT("ymm4"), TEXT("ymm5"), TEXT("ymm6"), TEXT("ymm7"), TEXT("ymm8"), TEXT("ymm9"), TEXT("ymm10"), TEXT("ymm11"), TEXT("ymm12"), TEXT("ymm13"), TEXT("ymm14"), TEXT("ymm15"), },
    { TEXT("cr0"), TEXT("cr1"), TEXT("cr2"), TEXT("cr3"), TEXT("cr4"), TEXT("cr5"), TEXT("cr6"), TEXT("cr7"), },
    { TEXT("dr0"), TEXT("dr1"), TEXT("dr2"), TEXT("dr3"), TEXT("dr4"), TEXT("dr5"), TEXT("dr6"), TEXT("dr7"), },
    
};

OPCODE_X86 Opcode__________ = { TEXT(""), 0, { 0x0 }, OPCODE_X86_INVAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_00_____00 = { TEXT("add"), 1, { 0x00 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_01_____00 = { TEXT("add"), 1, { 0x01 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_02_____00 = { TEXT("add"), 1, { 0x02 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_03_____00 = { TEXT("add"), 1, { 0x03 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_04_____00 = { TEXT("add"), 1, { 0x04 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_05_____00 = { TEXT("add"), 1, { 0x05 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_10_____00 = { TEXT("adc"), 1, { 0x10 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_11_____00 = { TEXT("adc"), 1, { 0x11 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_12_____00 = { TEXT("adc"), 1, { 0x12 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_13_____00 = { TEXT("adc"), 1, { 0x13 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_14_____00 = { TEXT("adc"), 1, { 0x14 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_15_____00 = { TEXT("adc"), 1, { 0x15 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_20_____00 = { TEXT("and"), 1, { 0x20 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_21_____00 = { TEXT("and"), 1, { 0x21 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_22_____00 = { TEXT("and"), 1, { 0x22 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_23_____00 = { TEXT("and"), 1, { 0x23 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_24_____00 = { TEXT("and"), 1, { 0x24 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_25_____00 = { TEXT("and"), 1, { 0x25 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_27_____00 = { TEXT("daa"), 1, { 0x27 }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_2F_____00 = { TEXT("das"), 1, { 0x2F }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_37_____00 = { TEXT("aaa"), 1, { 0x37 }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_38_____00 = { TEXT("cmp"), 1, { 0x38 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_39_____00 = { TEXT("cmp"), 1, { 0x39 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_3A_____00 = { TEXT("cmp"), 1, { 0x3A }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_3B_____00 = { TEXT("cmp"), 1, { 0x3B }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_3C_____00 = { TEXT("cmp"), 1, { 0x3C }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_3D_____00 = { TEXT("cmp"), 1, { 0x3D }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_62_____00 = { TEXT("bound"), 1, { 0x62 }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_80_____00 = { TEXT("adc"), 1, { 0x80 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_80_____01 = { TEXT("add"), 1, { 0x80 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_80_____02 = { TEXT("and"), 1, { 0x80 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_80_____03 = { TEXT("cmp"), 1, { 0x80 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_81_____00 = { TEXT("adc"), 1, { 0x81 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_81_____01 = { TEXT("add"), 1, { 0x81 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_81_____02 = { TEXT("and"), 1, { 0x81 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_81_____03 = { TEXT("cmp"), 1, { 0x81 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_83_____00 = { TEXT("adc"), 1, { 0x83 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_83_____01 = { TEXT("add"), 1, { 0x83 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_83_____02 = { TEXT("and"), 1, { 0x83 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_83_____03 = { TEXT("cmp"), 1, { 0x83 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_88_____00 = { TEXT("mov"), 1, { 0x88 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_89_____00 = { TEXT("mov"), 1, { 0x89 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_8A_____00 = { TEXT("mov"), 1, { 0x8A }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_8B_____00 = { TEXT("mov"), 1, { 0x8B }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_8C_____00 = { TEXT("mov"), 1, { 0x8C }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_SEGMENT_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_8D_____00 = { TEXT("lea"), 1, { 0x8D }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_8E_____00 = { TEXT("mov"), 1, { 0x8E }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_SEGMENT_REG | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_9A_____00 = { TEXT("call"), 1, { 0x9A }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_FARPTR, };
OPCODE_X86 Opcode_A0_____00 = { TEXT("mov"), 1, { 0xA0 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_A1_____00 = { TEXT("mov"), 1, { 0xA1 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD_DQ, };
OPCODE_X86 Opcode_A2_____00 = { TEXT("mov"), 1, { 0xA2 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_A3_____00 = { TEXT("mov"), 1, { 0xA3 }, OPCODE_X86_VAILD | OPCODE_X86_DIRECTION_BIT, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD_DQ, };
OPCODE_X86 Opcode_B0_____00 = { TEXT("mov"), 1, { 0xB0 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_REG, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_B8_____00 = { TEXT("mov"), 1, { 0xB8 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_REG, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD_DQ, };
OPCODE_X86 Opcode_C6_____00 = { TEXT("mov"), 1, { 0xC6 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_C7_____00 = { TEXT("mov"), 1, { 0xC7 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_DW_DD_DQ, };
OPCODE_X86 Opcode_C8_____00 = { TEXT("enter"), 1, { 0xC8 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_3_BYTE, };
OPCODE_X86 Opcode_C9_____00 = { TEXT("leave"), 1, { 0xC9 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_CC_____00 = { TEXT("int3"), 1, { 0xCC }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_CD_____00 = { TEXT("int"), 1, { 0xCD }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_CE_____00 = { TEXT("into"), 1, { 0xCE }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_D4_____00 = { TEXT("aam"), 1, { 0xD4 }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_D5_____00 = { TEXT("aad"), 1, { 0xD5 }, OPCODE_X86_LEGACY_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E0_____00 = { TEXT("loopne"), 1, { 0xE0 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E1_____00 = { TEXT("loope"), 1, { 0xE1 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E2_____00 = { TEXT("loop"), 1, { 0xE2 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E4_____00 = { TEXT("in"), 1, { 0xE4 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E5_____00 = { TEXT("in"), 1, { 0xE5 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_E8_____00 = { TEXT("call"), 1, { 0xE8 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_EA_____00 = { TEXT("jmp"), 1, { 0xEA }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_FARPTR, };
OPCODE_X86 Opcode_EB_____00 = { TEXT("jmp"), 1, { 0xEB }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_BYTE, };
OPCODE_X86 Opcode_EC_____00 = { TEXT("in"), 1, { 0xEC }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_ED_____00 = { TEXT("in"), 1, { 0xED }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_DW_DD, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F4_____00 = { TEXT("hlt"), 1, { 0xF4 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F5_____00 = { TEXT("cmc"), 1, { 0xF5 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F6_____00 = { TEXT("div"), 1, { 0xF6 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F6_____01 = { TEXT("idiv"), 1, { 0xF6 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F6_____02 = { TEXT("mul"), 1, { 0xF6 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_BYTE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F7_____00 = { TEXT("div"), 1, { 0xF7 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F7_____01 = { TEXT("idiv"), 1, { 0xF7 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F7_____02 = { TEXT("mul"), 1, { 0xF7 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F8_____00 = { TEXT("clc"), 1, { 0xF8 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_F9_____00 = { TEXT("jmp"), 1, { 0xF9 }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_DW_DD, };
OPCODE_X86 Opcode_FA_____00 = { TEXT("cli"), 1, { 0xFA }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_FC_____00 = { TEXT("cld"), 1, { 0xFC }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_NONE, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_FF_____00 = { TEXT("call"), 1, { 0xFF }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_FF_____01 = { TEXT("call"), 1, { 0xFF }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_FARPTR, };
OPCODE_X86 Opcode_FF_____02 = { TEXT("jmp"), 1, { 0xFF }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_DW_DD_DQ, OPCODE_X86_IMMEDIATE_NONE, };
OPCODE_X86 Opcode_FF_____03 = { TEXT("jmp"), 1, { 0xFF }, OPCODE_X86_VAILD, OPCODE_X86_MODRM_OPCODE | OPCODE_X86_MODRM_REG_MEM, OPCODE_X86_OPERAND_NONE, OPCODE_X86_IMMEDIATE_FARPTR, };

LPOPCODE_X86 OpcodeMap1[256] =
{
    /*
    0x00,              0x01,              0x02,              0x03,              0x04,              0x05,              0x06,              0x07,
    0x08,              0x09,              0x0A,              0x0B,              0x0C,              0x0D,              0x0E,              0x0F,
    */
    &Opcode_00_____00, &Opcode_01_____00, &Opcode_02_____00, &Opcode_03_____00, &Opcode_04_____00, &Opcode_05_____00, &Opcode__________, &Opcode__________, /* 0x00 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x08 */
    &Opcode_10_____00, &Opcode_11_____00, &Opcode_12_____00, &Opcode_13_____00, &Opcode_14_____00, &Opcode_15_____00, &Opcode__________, &Opcode__________, /* 0x10 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x18 */
    &Opcode_20_____00, &Opcode_21_____00, &Opcode_22_____00, &Opcode_23_____00, &Opcode_24_____00, &Opcode_25_____00, &Opcode__________, &Opcode_27_____00, /* 0x20 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode_2F_____00, /* 0x28 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode_37_____00, /* 0x30 */
    &Opcode_38_____00, &Opcode_39_____00, &Opcode_3A_____00, &Opcode_3B_____00, &Opcode_3C_____00, &Opcode_3D_____00, &Opcode__________, &Opcode__________, /* 0x38 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x40 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x48 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x50 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x58 */
    &Opcode__________, &Opcode__________, &Opcode_62_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x60 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x68 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x70 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x78 */
    &Opcode_80_____00, &Opcode_81_____00, &Opcode__________, &Opcode_83_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x80 */
    &Opcode_88_____00, &Opcode_89_____00, &Opcode_8A_____00, &Opcode_8B_____00, &Opcode_8C_____00, &Opcode_8D_____00, &Opcode_8E_____00, &Opcode__________, /* 0x88 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x90 */
    &Opcode__________, &Opcode__________, &Opcode_9A_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0x98 */
    &Opcode_A0_____00, &Opcode_A1_____00, &Opcode_A2_____00, &Opcode_A3_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0xA0 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0xA8 */
    &Opcode_B0_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0xB0 */
    &Opcode_B8_____00, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0xB8 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode_C6_____00, &Opcode_C7_____00, /* 0xC0 */
    &Opcode_C8_____00, &Opcode_C9_____00, &Opcode__________, &Opcode__________, &Opcode_CC_____00, &Opcode_CD_____00, &Opcode_CE_____00, &Opcode__________, /* 0xC8 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode_D4_____00, &Opcode_D5_____00, &Opcode__________, &Opcode__________, /* 0xD0 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, /* 0xD8 */
    &Opcode_E0_____00, &Opcode_E1_____00, &Opcode_E2_____00, &Opcode__________, &Opcode_E4_____00, &Opcode_E5_____00, &Opcode__________, &Opcode__________, /* 0xE0 */
    &Opcode_E8_____00, &Opcode__________, &Opcode_EA_____00, &Opcode_EB_____00, &Opcode_EC_____00, &Opcode_ED_____00, &Opcode__________, &Opcode__________, /* 0xE8 */
    &Opcode__________, &Opcode__________, &Opcode__________, &Opcode__________, &Opcode_F4_____00, &Opcode_F5_____00, &Opcode_F6_____00, &Opcode_F7_____00, /* 0xF0 */
    &Opcode_F8_____00, &Opcode_F9_____00, &Opcode_FA_____00, &Opcode__________, &Opcode_FC_____00, &Opcode__________, &Opcode__________, &Opcode_FF_____00, /* 0xF8 */

};

BYTE LegacyPrefixMap[256] =
{
    /*
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* 0x20 */  /* 26h:ES 2Eh:[CS NBRANCH] */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* 0x30 */  /* 36h:SS 3Eh:[DS BRANCH] */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 */
    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 */  /* 64h:FS 65h:GS 66h:OPERAND_SIZE 67h:ADDRESS_SIZE */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xA0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xB0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xC0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xD0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xE0 */
    0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xF0 */  /* F0h:LOCK F2h:[REPNE REPNZ XACQUIRE] F3h:[REP REPE REPZ XRELEASE] */
};

BYTE EmptyMap[256] =
{
    /*
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xA0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xB0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xC0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xD0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xE0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xF0 */
};
OPCODE_INFO_X86 PrefixMap[256] =
{
    { TEXT("es:"), 1, { 0x26 }, OPCODE_X86_PREFIX },
    { TEXT("cs:"), 1, { 0x2E }, OPCODE_X86_PREFIX },
    { TEXT("ss:"), 1, { 0x36 }, OPCODE_X86_PREFIX },
    { TEXT("ds:"), 1, { 0x3E }, OPCODE_X86_PREFIX },
};
OPCODE_INFO_X86 OpcodeMap32[4][256] =
{
    // One-byte Opcode Map
    {
        // 0x00 - 0x0F
        { TEXT("add"), 1, { 0x00 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("add"), 1, { 0x01 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("add"), 1, { 0x02 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("add"), 1, { 0x03 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("add"), 1, { 0x04 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("add"), 1, { 0x05 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push es"), 1, { 0x06 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("pop es"), 1, { 0x07 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("or"), 1, { 0x08 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("or"), 1, { 0x09 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("or"), 1, { 0x0A }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("or"), 1, { 0x0B }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("or"), 1, { 0x0C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("or"), 1, { 0x0D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push cs"), 1, { 0x0E }, OPCODE_X86_LEGACY_VAILD },
        { TEXT(""), 1, { 0x0F }, OPCODE_X86_INVAILD },
        // 0x10 - 0x1F
        { TEXT("adc"), 1, { 0x10 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("adc"), 1, { 0x11 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("adc"), 1, { 0x12 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("adc"), 1, { 0x13 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("adc"), 1, { 0x14 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("adc"), 1, { 0x15 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push ss"), 1, { 0x16 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("pop ss"), 1, { 0x17 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("sbb"), 1, { 0x18 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("sbb"), 1, { 0x19 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("sbb"), 1, { 0x1A }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("sbb"), 1, { 0x1B }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("sbb"), 1, { 0x1C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("sbb"), 1, { 0x1D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push ds"), 1, { 0x1E }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("pop ds"), 1, { 0x1F }, OPCODE_X86_LEGACY_VAILD },
        // 0x20 - 0x2F
        { TEXT("and"), 1, { 0x20 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("and"), 1, { 0x21 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("and"), 1, { 0x22 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("and"), 1, { 0x23 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("and"), 1, { 0x24 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("and"), 1, { 0x25 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT(""), 1, { 0x26 }, OPCODE_X86_INVAILD },
        { TEXT("daa"), 1, { 0x27 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("sub"), 1, { 0x28 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("sub"), 1, { 0x29 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("sub"), 1, { 0x2A }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("sub"), 1, { 0x2B }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("sub"), 1, { 0x2C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("sub"), 1, { 0x2D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT(""), 1, { 0x2E }, OPCODE_X86_INVAILD },
        { TEXT("das"), 1, { 0x2F }, OPCODE_X86_LEGACY_VAILD },
        // 0x30 - 0x3F
        { TEXT("xor"), 1, { 0x30 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("xor"), 1, { 0x31 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("xor"), 1, { 0x32 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("xor"), 1, { 0x33 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("xor"), 1, { 0x34 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("xor"), 1, { 0x35 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT(""), 1, { 0x36 }, OPCODE_X86_INVAILD },
        { TEXT("aaa"), 1, { 0x37 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("cmp"), 1, { 0x38 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE },
        { TEXT("cmp"), 1, { 0x39 }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("cmp"), 1, { 0x3A }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_BYTE | OPCODE_X86_DIRECTION },
        { TEXT("cmp"), 1, { 0x3B }, OPCODE_X86_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_DIRECTION },
        { TEXT("cmp"), 1, { 0x3C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE | OPCODE_X86_OPERAND_BYTE },
        { TEXT("cmp"), 1, { 0x3D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT(""), 1, { 0x3E }, OPCODE_X86_INVAILD },
        { TEXT("aas"), 1, { 0x3F }, OPCODE_X86_LEGACY_VAILD },
        // 0x40 - 0x4F
        { TEXT("inc"), 1, { 0x40 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x41 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x42 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x43 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x44 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x45 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x46 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("inc"), 1, { 0x47 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x48 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x49 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4A }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4B }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4C }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4D }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4E }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("dec"), 1, { 0x4F }, OPCODE_X86_LEGACY_VAILD },
        // 0x50 - 0x5F
        { TEXT("push"), 1, { 0x50 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x51 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x52 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x53 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x54 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x55 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x56 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("push"), 1, { 0x57 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x58 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x59 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5A }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5B }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5C }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5D }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5E }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("pop"), 1, { 0x5F }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ },
        // 0x60 - 0x6F
        { TEXT("pushad"), 1, { 0x60 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("popad"), 1, { 0x61 }, OPCODE_X86_LEGACY_VAILD },
        { TEXT("bound"), 1, { 0x62 }, OPCODE_X86_LEGACY_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_DW_DD_DQ },
        { TEXT("arpl"), 1, { 0x63 }, OPCODE_X86_LEGACY_VAILD | OPCODE_X86_MODRM_EXIST | OPCODE_X86_OPERAND_WORD },
        { TEXT(""), 1, { 0x64 }, OPCODE_X86_INVAILD },
        { TEXT(""), 1, { 0x65 }, OPCODE_X86_INVAILD },
        { TEXT(""), 1, { 0x66 }, OPCODE_X86_INVAILD },
        { TEXT(""), 1, { 0x67 }, OPCODE_X86_INVAILD },
        { TEXT("push"), 1, { 0x68 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_DW_DD },
        { TEXT("imul"), 1, { 0x69 }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_IMMEDIATE_DW_DD },
        { TEXT("push"), 1, { 0x6A }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("imul"), 1, { 0x6B }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD_DQ | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("ins"), 1, { 0x6C }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_BYTE },
        { TEXT("ins"), 1, { 0x6D }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD },
        { TEXT("outs"), 1, { 0x6E }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_BYTE },
        { TEXT("outs"), 1, { 0x6F }, OPCODE_X86_VAILD | OPCODE_X86_OPERAND_DW_DD },
        // 0x70 - 0x7F
        { TEXT("jo"), 1, { 0x70 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jno"), 1, { 0x71 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jb"), 1, { 0x72 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnb"), 1, { 0x73 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jz"), 1, { 0x74 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnz"), 1, { 0x75 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jna"), 1, { 0x76 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("ja"), 1, { 0x77 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("js"), 1, { 0x78 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jns"), 1, { 0x79 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jp"), 1, { 0x7A }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnp"), 1, { 0x7B }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jl"), 1, { 0x7C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnl"), 1, { 0x7D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jng"), 1, { 0x7E }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jg"), 1, { 0x7F }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        // 0x80 - 0x8F
        { TEXT("jo"), 1, { 0x70 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jno"), 1, { 0x71 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jb"), 1, { 0x72 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnb"), 1, { 0x73 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jz"), 1, { 0x74 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnz"), 1, { 0x75 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jna"), 1, { 0x76 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("ja"), 1, { 0x77 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("js"), 1, { 0x78 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jns"), 1, { 0x79 }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jp"), 1, { 0x7A }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnp"), 1, { 0x7B }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jl"), 1, { 0x7C }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jnl"), 1, { 0x7D }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jng"), 1, { 0x7E }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },
        { TEXT("jg"), 1, { 0x7F }, OPCODE_X86_VAILD | OPCODE_X86_IMMEDIATE_BYTE },

    }
};

BYTE ValidMap[4][256] =
{
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0xFF, /* 0x00 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, /* 0x10 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, /* 0x20 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, /* 0x30 */
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* 0x40 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x50 */
    0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x60 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x70 */
    0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x80 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x90 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xA0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xB0 */
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, /* 0xC0 */
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xD0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xE0 */
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xF0 */

    /*
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,     Two-byte Opcode Map (First Byte is 0FH)
    */
    0x03, 0x03, 0x03, 0x03, 0x00, 0x02, 0x03, 0x02, 0x03, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, /* 0x00 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, /* 0x10 */
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x20 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x40 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x50 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x60 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, /* 0x70 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x80 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x90 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xA0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xB0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xC0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xD0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xE0 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, /* 0xF0 */

    /*
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,     Three-byte Opcode Map (First Two Bytes are 0F 38H)
    */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x00 */
    0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, /* 0x10 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x20 */
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x30 */
    0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70 */
    0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, /* 0x80 */
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x90 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xA0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xB0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xC0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0xD0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xE0 */
    0x03, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xF0 */

    /*
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,     Three-byte Opcode Map (First two bytes are 0F 3AH)
    */
    0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* 0x00 */
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, /* 0x10 */
    0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30 */
    0x03, 0x03, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, /* 0x40 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 */
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x70 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xA0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xB0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xC0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, /* 0xD0 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xE0 */
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xF0 */
};