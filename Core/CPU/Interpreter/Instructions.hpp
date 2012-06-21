#define INSN_ADD(a, b) { a = a + b; }
#define INSN_JMP(a) { eip += a; }

#define INSN_AAA() { WARN("STUB Instruction AAA"); }
#define INSN_AAD(a) { WARN("STUB Instruction AAD"); }
#define INSN_AAM(a) { WARN("STUB Instruction AAM"); }
#define INSN_AAS() { WARN("STUB Instruction AAS"); }
#define INSN_ADC(a, b) { WARN("STUB Instruction ADC"); }
#define INSN_AND(a, b) { WARN("STUB Instruction AND"); }
#define INSN_ARPL(a, b) { WARN("STUB Instruction ARPL"); }
#define INSN_BOUND(a, b) { WARN("STUB Instruction BOUND"); }
#define INSN_CALL(a) { WARN("STUB Instruction CALL"); }
#define INSN_CDQ() { WARN("STUB Instruction CDQ"); }
#define INSN_CLC() { WARN("STUB Instruction CLC"); }
#define INSN_CLD() { WARN("STUB Instruction CLD"); }
#define INSN_CLI() { WARN("STUB Instruction CLI"); }
#define INSN_CMC() { WARN("STUB Instruction CMC"); }
#define INSN_CMP(a, b) { WARN("STUB Instruction CMP"); }
#define INSN_CMPS(a, b) { WARN("STUB Instruction CMPS"); }
#define INSN_CWDE() { WARN("STUB Instruction CWDE"); }
#define INSN_DAA() { WARN("STUB Instruction DAA"); }
#define INSN_DAS() { WARN("STUB Instruction DAS"); }
#define INSN_DEC(a) { WARN("STUB Instruction DEC"); }
#define INSN_ENTER(a, b) { WARN("STUB Instruction ENTER"); }
#define INSN_HLT() { WARN("STUB Instruction HLT"); }
#define INSN_IMUL(a, b, c) { WARN("STUB Instruction IMUL"); }
#define INSN_IN(a, b) { WARN("STUB Instruction IN"); }
#define INSN_INC(a) { WARN("STUB Instruction INC"); }
#define INSN_INS(a, b) { WARN("STUB Instruction INS"); }
#define INSN_INT(a) { WARN("STUB Instruction INT"); }
#define INSN_INT1() { WARN("STUB Instruction INT1"); }
#define INSN_INT3() { WARN("STUB Instruction INT3"); }
#define INSN_INTO() { WARN("STUB Instruction INTO"); }
#define INSN_IRET() { WARN("STUB Instruction IRET"); }
#define INSN_JB(a) { WARN("STUB Instruction JB"); }
#define INSN_JBE(a) { WARN("STUB Instruction JBE"); }
#define INSN_JCXZ(a) { WARN("STUB Instruction JCXZ"); }
#define INSN_JL(a) { WARN("STUB Instruction JL"); }
#define INSN_JLE(a) { WARN("STUB Instruction JLE"); }
#define INSN_JNB(a) { WARN("STUB Instruction JNB"); }
#define INSN_JNBE(a) { WARN("STUB Instruction JNBE"); }
#define INSN_JNL(a) { WARN("STUB Instruction JNL"); }
#define INSN_JNLE(a) { WARN("STUB Instruction JNLE"); }
#define INSN_JNO(a) { WARN("STUB Instruction JNO"); }
#define INSN_JNP(a) { WARN("STUB Instruction JNP"); }
#define INSN_JNS(a) { WARN("STUB Instruction JNS"); }
#define INSN_JNZ(a) { WARN("STUB Instruction JNZ"); }
#define INSN_JO(a) { WARN("STUB Instruction JO"); }
#define INSN_JP(a) { WARN("STUB Instruction JP"); }
#define INSN_JS(a) { WARN("STUB Instruction JS"); }
#define INSN_JZ(a) { WARN("STUB Instruction JZ"); }
#define INSN_LAHF() { WARN("STUB Instruction LAHF"); }
#define INSN_LDS(a, b) { WARN("STUB Instruction LDS"); }
#define INSN_LEA(a, b) { WARN("STUB Instruction LEA"); }
#define INSN_LEAVE() { WARN("STUB Instruction LEAVE"); }
#define INSN_LES(a, b) { WARN("STUB Instruction LES"); }
#define INSN_LODS(a, b) { WARN("STUB Instruction LODS"); }
#define INSN_LOOP(a) { WARN("STUB Instruction LOOP"); }
#define INSN_LOOPNZ(a) { WARN("STUB Instruction LOOPNZ"); }
#define INSN_LOOPZ(a) { WARN("STUB Instruction LOOPZ"); }
#define INSN_MOV(a, b) { WARN("STUB Instruction MOV"); }
#define INSN_MOVS(a, b) { WARN("STUB Instruction MOVS"); }
#define INSN_NOP() { WARN("STUB Instruction NOP"); }
#define INSN_OR(a, b) { WARN("STUB Instruction OR"); }
#define INSN_OUT(a, b) { WARN("STUB Instruction OUT"); }
#define INSN_OUTS(a, b) { WARN("STUB Instruction OUTS"); }
#define INSN_POP(a) { WARN("STUB Instruction POP"); }
#define INSN_POPA() { WARN("STUB Instruction POPA"); }
#define INSN_POPF() { WARN("STUB Instruction POPF"); }
#define INSN_PUSH(a) { WARN("STUB Instruction PUSH"); }
#define INSN_PUSHA() { WARN("STUB Instruction PUSHA"); }
#define INSN_PUSHF() { WARN("STUB Instruction PUSHF"); }
#define INSN_RETfar_off(a) { WARN("STUB Instruction RETfar_off"); }
#define INSN_RETfar() { WARN("STUB Instruction RETfar"); }
#define INSN_RETnear_off(a) { WARN("STUB Instruction RETnear_off"); }
#define INSN_RETnear() { WARN("STUB Instruction RETnear"); }
#define INSN_SAHF() { WARN("STUB Instruction SAHF"); }
#define INSN_SALC() { WARN("STUB Instruction SALC"); }
#define INSN_SBB(a, b) { WARN("STUB Instruction SBB"); }
#define INSN_SCAS(a, b) { WARN("STUB Instruction SCAS"); }
#define INSN_STC() { WARN("STUB Instruction STC"); }
#define INSN_STD() { WARN("STUB Instruction STD"); }
#define INSN_STI() { WARN("STUB Instruction STI"); }
#define INSN_STOS(a, b) { WARN("STUB Instruction STOS"); }
#define INSN_SUB(a, b) { WARN("STUB Instruction SUB"); }
#define INSN_TEST(a, b) { WARN("STUB Instruction TEST"); }
#define INSN_WAIT() { WARN("STUB Instruction WAIT"); }
#define INSN_XCHG(a, b) { WARN("STUB Instruction XCHG"); }
#define INSN_XLAT() { WARN("STUB Instruction XLAT"); }
#define INSN_XOR(a, b) { WARN("STUB Instruction XOR"); }
