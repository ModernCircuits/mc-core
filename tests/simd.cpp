#include "mc/simd.hpp"

#include "mc/format.hpp"

auto main() -> int
{
    mc::print("        cacheLineSize: {0}\n", mc::simd::CpuId::cacheLineSize());
    mc::print("        processorType: {0}\n", mc::simd::CpuId::processorType());
    mc::print("      processorFamily: {0}\n", mc::simd::CpuId::processorFamily());
    mc::print("       processorModel: {0}\n", mc::simd::CpuId::processorModel());
    mc::print("    logicalProcessors: {0}\n", mc::simd::CpuId::logicalProcessors());
    mc::print("                isAmd: {0}\n", mc::simd::CpuId::isAmd());
    mc::print("              isIntel: {0}\n", mc::simd::CpuId::isIntel());
    mc::print("              hasSse3: {0}\n", mc::simd::CpuId::hasSse3());
    mc::print("         hasPclmulqdq: {0}\n", mc::simd::CpuId::hasPclmulqdq());
    mc::print("           hasMonitor: {0}\n", mc::simd::CpuId::hasMonitor());
    mc::print("               hasVmx: {0}\n", mc::simd::CpuId::hasVmx());
    mc::print("               hasSmx: {0}\n", mc::simd::CpuId::hasSmx());
    mc::print("              hasEist: {0}\n", mc::simd::CpuId::hasEist());
    mc::print("               hasTm2: {0}\n", mc::simd::CpuId::hasTm2());
    mc::print("             hasSsse3: {0}\n", mc::simd::CpuId::hasSsse3());
    mc::print("               hasFma: {0}\n", mc::simd::CpuId::hasFma());
    mc::print("        hasCmpXchg16b: {0}\n", mc::simd::CpuId::hasCmpXchg16b());
    mc::print("              hasPdcm: {0}\n", mc::simd::CpuId::hasPdcm());
    mc::print("               hasDca: {0}\n", mc::simd::CpuId::hasDca());
    mc::print("             hasSse41: {0}\n", mc::simd::CpuId::hasSse41());
    mc::print("             hasSse42: {0}\n", mc::simd::CpuId::hasSse42());
    mc::print("             hasMovbe: {0}\n", mc::simd::CpuId::hasMovbe());
    mc::print("            hasPopcnt: {0}\n", mc::simd::CpuId::hasPopcnt());
    mc::print("               hasAes: {0}\n", mc::simd::CpuId::hasAes());
    mc::print("           hasOsxsave: {0}\n", mc::simd::CpuId::hasOsxsave());
    mc::print("               hasAvx: {0}\n", mc::simd::CpuId::hasAvx());
    mc::print("              hasBmi1: {0}\n", mc::simd::CpuId::hasBmi1());
    mc::print("               hasHle: {0}\n", mc::simd::CpuId::hasHle());
    mc::print("              hasAvx2: {0}\n", mc::simd::CpuId::hasAvx2());
    mc::print("              hasBmi2: {0}\n", mc::simd::CpuId::hasBmi2());
    mc::print("               hasRtm: {0}\n", mc::simd::CpuId::hasRtm());
    mc::print("           hasAvx512f: {0}\n", mc::simd::CpuId::hasAvx512f());
    mc::print("          hasAvx512dq: {0}\n", mc::simd::CpuId::hasAvx512dq());
    mc::print("        hasAvx512ifma: {0}\n", mc::simd::CpuId::hasAvx512ifma());
    mc::print("          hasAvx512pf: {0}\n", mc::simd::CpuId::hasAvx512pf());
    mc::print("          hasAvx512er: {0}\n", mc::simd::CpuId::hasAvx512er());
    mc::print("          hasAvx512cd: {0}\n", mc::simd::CpuId::hasAvx512cd());
    mc::print("          hasAvx512bw: {0}\n", mc::simd::CpuId::hasAvx512bw());
    mc::print("          hasAvx512vl: {0}\n", mc::simd::CpuId::hasAvx512vl());
    mc::print("        hasAvx512vbmi: {0}\n", mc::simd::CpuId::hasAvx512vbmi());
    mc::print("              hasF16c: {0}\n", mc::simd::CpuId::hasF16c());
    mc::print("            hasRdrand: {0}\n", mc::simd::CpuId::hasRdrand());
    mc::print("               hasFpu: {0}\n", mc::simd::CpuId::hasFpu());
    mc::print("               hasVme: {0}\n", mc::simd::CpuId::hasVme());
    mc::print("                hasDe: {0}\n", mc::simd::CpuId::hasDe());
    mc::print("               hasPse: {0}\n", mc::simd::CpuId::hasPse());
    mc::print("               hasTsc: {0}\n", mc::simd::CpuId::hasTsc());
    mc::print("               hasMsr: {0}\n", mc::simd::CpuId::hasMsr());
    mc::print("               hasPae: {0}\n", mc::simd::CpuId::hasPae());
    mc::print("               hasCx8: {0}\n", mc::simd::CpuId::hasCx8());
    mc::print("              hasMtrr: {0}\n", mc::simd::CpuId::hasMtrr());
    mc::print("              hasCmov: {0}\n", mc::simd::CpuId::hasCmov());
    mc::print("             hasClfsh: {0}\n", mc::simd::CpuId::hasClfsh());
    mc::print("              hasAcpi: {0}\n", mc::simd::CpuId::hasAcpi());
    mc::print("               hasMmx: {0}\n", mc::simd::CpuId::hasMmx());
    mc::print("               hasSse: {0}\n", mc::simd::CpuId::hasSse());
    mc::print("              hasSse2: {0}\n", mc::simd::CpuId::hasSse2());
    mc::print("               hasHtt: {0}\n", mc::simd::CpuId::hasHtt());
    mc::print("             hasSse4a: {0}\n", mc::simd::CpuId::hasSse4a());
    mc::print("       hasMisAlignSse: {0}\n", mc::simd::CpuId::hasMisAlignSse());
    mc::print("       hasAmdPrefetch: {0}\n", mc::simd::CpuId::hasAmdPrefetch());
    mc::print("               hasXop: {0}\n", mc::simd::CpuId::hasXop());
    mc::print("              hasFma4: {0}\n", mc::simd::CpuId::hasFma4());
    mc::print("            hasRdtscp: {0}\n", mc::simd::CpuId::hasRdtscp());
    mc::print("             has3DNow: {0}\n", mc::simd::CpuId::has3DNow());
    mc::print("          has3DNowExt: {0}\n", mc::simd::CpuId::has3DNowExt());
    mc::print("        L1Instruction: {0}\n", mc::simd::CpuId::L1Instruction());
    mc::print("               L1Data: {0}\n", mc::simd::CpuId::L1Data());
    mc::print("               L2Data: {0}\n", mc::simd::CpuId::L2Data());
    mc::print("               L3Data: {0}\n", mc::simd::CpuId::L3Data());
    mc::print("L1InstructionLineSize: {0}\n", mc::simd::CpuId::L1InstructionLineSize());
    mc::print("       L1DataLineSize: {0}\n", mc::simd::CpuId::L1DataLineSize());
    mc::print("       L2DataLineSize: {0}\n", mc::simd::CpuId::L2DataLineSize());
    mc::print("       L3DataLineSize: {0}\n", mc::simd::CpuId::L3DataLineSize());
    mc::print("      L1Associativity: {0}\n", mc::simd::CpuId::L1Associativity());
    mc::print("      L2Associativity: {0}\n", mc::simd::CpuId::L2Associativity());
    mc::print("      L3Associativity: {0}\n", mc::simd::CpuId::L3Associativity());
    mc::print("             prefetch: {0}\n", mc::simd::CpuId::prefetch());

    return 0;
}
