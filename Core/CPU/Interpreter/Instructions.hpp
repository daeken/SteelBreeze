#define INSN_ADD(a, b) { a = a + b; }
#define INSN_SUB(a, b) { a = a - b; }

#define INSN_JMP(a) { eip += a; }

#define INSN_AAA() { BAIL("STUB Instruction AAA"); }
#define INSN_AAD(a) { BAIL("STUB Instruction AAD"); }
#define INSN_AAM(a) { BAIL("STUB Instruction AAM"); }
#define INSN_AAS() { BAIL("STUB Instruction AAS"); }
#define INSN_ADC(a, b) { BAIL("STUB Instruction ADC"); }
#define INSN_AND(a, b) { BAIL("STUB Instruction AND"); }
#define INSN_ARPL(a, b) { BAIL("STUB Instruction ARPL"); }
#define INSN_BOUND(a, b) { BAIL("STUB Instruction BOUND"); }
#define INSN_CALL(a) { BAIL("STUB Instruction CALL"); }
#define INSN_CDQ() { BAIL("STUB Instruction CDQ"); }
#define INSN_CLC() { BAIL("STUB Instruction CLC"); }
#define INSN_CLD() { BAIL("STUB Instruction CLD"); }
#define INSN_CLI() { BAIL("STUB Instruction CLI"); }
#define INSN_CMC() { BAIL("STUB Instruction CMC"); }
#define INSN_CMP(a, b) { BAIL("STUB Instruction CMP"); }
#define INSN_CMPS(a, b) { BAIL("STUB Instruction CMPS"); }
#define INSN_CWDE() { BAIL("STUB Instruction CWDE"); }
#define INSN_DAA() { BAIL("STUB Instruction DAA"); }
#define INSN_DAS() { BAIL("STUB Instruction DAS"); }
#define INSN_DEC(a) { BAIL("STUB Instruction DEC"); }
#define INSN_ENTER(a, b) { BAIL("STUB Instruction ENTER"); }
#define INSN_HLT() { BAIL("STUB Instruction HLT"); }
#define INSN_IMUL(a, b, c) { BAIL("STUB Instruction IMUL"); }
#define INSN_IN(a, b) { BAIL("STUB Instruction IN"); }
#define INSN_INC(a) { BAIL("STUB Instruction INC"); }
#define INSN_INS(a, b) { BAIL("STUB Instruction INS"); }
#define INSN_INT(a) { BAIL("STUB Instruction INT"); }
#define INSN_INT1() { BAIL("STUB Instruction INT1"); }
#define INSN_INT3() { BAIL("STUB Instruction INT3"); }
#define INSN_INTO() { BAIL("STUB Instruction INTO"); }
#define INSN_IRET() { BAIL("STUB Instruction IRET"); }
#define INSN_JB(a) { BAIL("STUB Instruction JB"); }
#define INSN_JBE(a) { BAIL("STUB Instruction JBE"); }
#define INSN_JCXZ(a) { BAIL("STUB Instruction JCXZ"); }
#define INSN_JL(a) { BAIL("STUB Instruction JL"); }
#define INSN_JLE(a) { BAIL("STUB Instruction JLE"); }
#define INSN_JNB(a) { BAIL("STUB Instruction JNB"); }
#define INSN_JNBE(a) { BAIL("STUB Instruction JNBE"); }
#define INSN_JNL(a) { BAIL("STUB Instruction JNL"); }
#define INSN_JNLE(a) { BAIL("STUB Instruction JNLE"); }
#define INSN_JNO(a) { BAIL("STUB Instruction JNO"); }
#define INSN_JNP(a) { BAIL("STUB Instruction JNP"); }
#define INSN_JNS(a) { BAIL("STUB Instruction JNS"); }
#define INSN_JNZ(a) { BAIL("STUB Instruction JNZ"); }
#define INSN_JO(a) { BAIL("STUB Instruction JO"); }
#define INSN_JP(a) { BAIL("STUB Instruction JP"); }
#define INSN_JS(a) { BAIL("STUB Instruction JS"); }
#define INSN_JZ(a) { BAIL("STUB Instruction JZ"); }
#define INSN_LAHF() { BAIL("STUB Instruction LAHF"); }
#define INSN_LDS(a, b) { BAIL("STUB Instruction LDS"); }
#define INSN_LEA(a, b) { BAIL("STUB Instruction LEA"); }
#define INSN_LEAVE() { BAIL("STUB Instruction LEAVE"); }
#define INSN_LES(a, b) { BAIL("STUB Instruction LES"); }
#define INSN_LODS(a, b) { BAIL("STUB Instruction LODS"); }
#define INSN_LOOP(a) { BAIL("STUB Instruction LOOP"); }
#define INSN_LOOPNZ(a) { BAIL("STUB Instruction LOOPNZ"); }
#define INSN_LOOPZ(a) { BAIL("STUB Instruction LOOPZ"); }
#define INSN_MOV(a, b) { BAIL("STUB Instruction MOV"); }
#define INSN_MOVS(a, b) { BAIL("STUB Instruction MOVS"); }
#define INSN_NOP() { BAIL("STUB Instruction NOP"); }
#define INSN_OR(a, b) { BAIL("STUB Instruction OR"); }
#define INSN_OUT(a, b) { BAIL("STUB Instruction OUT"); }
#define INSN_OUTS(a, b) { BAIL("STUB Instruction OUTS"); }
#define INSN_POP(a) { BAIL("STUB Instruction POP"); }
#define INSN_POPA() { BAIL("STUB Instruction POPA"); }
#define INSN_POPF() { BAIL("STUB Instruction POPF"); }
#define INSN_PUSH(a) { BAIL("STUB Instruction PUSH"); }
#define INSN_PUSHA() { BAIL("STUB Instruction PUSHA"); }
#define INSN_PUSHF() { BAIL("STUB Instruction PUSHF"); }
#define INSN_RETfar_off(a) { BAIL("STUB Instruction RETfar_off"); }
#define INSN_RETfar() { BAIL("STUB Instruction RETfar"); }
#define INSN_RETnear_off(a) { BAIL("STUB Instruction RETnear_off"); }
#define INSN_RETnear() { BAIL("STUB Instruction RETnear"); }
#define INSN_SAHF() { BAIL("STUB Instruction SAHF"); }
#define INSN_SALC() { BAIL("STUB Instruction SALC"); }
#define INSN_SBB(a, b) { BAIL("STUB Instruction SBB"); }
#define INSN_SCAS(a, b) { BAIL("STUB Instruction SCAS"); }
#define INSN_STC() { BAIL("STUB Instruction STC"); }
#define INSN_STD() { BAIL("STUB Instruction STD"); }
#define INSN_STI() { BAIL("STUB Instruction STI"); }
#define INSN_STOS(a, b) { BAIL("STUB Instruction STOS"); }
#define INSN_TEST(a, b) { BAIL("STUB Instruction TEST"); }
#define INSN_WAIT() { BAIL("STUB Instruction WAIT"); }
#define INSN_XCHG(a, b) { BAIL("STUB Instruction XCHG"); }
#define INSN_XLAT() { BAIL("STUB Instruction XLAT"); }
#define INSN_XOR(a, b) { BAIL("STUB Instruction XOR"); }
