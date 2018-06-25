#pragma once

#include <cstdint>
#include <gtirb/Block.hpp>
#include <gtirb/Data.hpp>
#include <gtirb/IR.hpp>
#include <gtirb/Instruction.hpp>
#include <gtirb/Relocation.hpp>
#include <gtirb/Symbol.hpp>
#include <gtirb/SymbolSet.hpp>
#include <gtirb/Table.hpp>
#include <iosfwd>
#include <list>
#include <map>
#include <string>
#include <vector>
#include "DisasmTypes.h"
#include "Export.h"
#include "Table.h"

///
/// \class DisasmData
///
/// Port of the prolog disasm.
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DisasmData
{
public:
    ///
    /// Read all of the expected file types out of a directory.
    ///
    /// This calls all of the individual "parse" functions for the known file names in the given
    /// directory.
    ///
    void parseDirectory(std::string x);

    void saveIRToFile(std::string path);
    void loadIRFromFile(std::string path);

    // FIXME: IR should replace DisasmData entirely.
    gtirb::IR ir;

    gtirb::SymbolSet* getSymbolSet() const;
    const std::vector<gtirb::Section>& getSections() const;
    std::vector<DecodedInstruction>* getDecodedInstruction();
    std::vector<OpRegdirect>* getOPRegdirect();
    std::vector<OpImmediate>* getOPImmediate();
    std::vector<OpIndirect>* getOPIndirect();
    std::vector<uint64_t>* getRemainingEA();
    std::vector<uint64_t>* getMainFunction();
    std::vector<uint64_t>* getStartFunction();
    std::vector<uint64_t>* getFunctionEntry();
    std::vector<std::string>* getAmbiguousSymbol();
    std::vector<uint64_t>* getBSSData();
    std::vector<gtirb::Table::InnerMapType>& getDataSections();
    Table* getStackOperand();
    Table* getPreferredDataAccess();
    Table* getDataAccessPattern();
    Table* getDiscardedBlock();
    Table* getDirectJump();
    Table* getPCRelativeJump();
    Table* getPCRelativeCall();
    Table* getBlockOverlap();
    Table* getDefUsed();
    Table* getPairedDataAccess();
    Table* getValueReg();
    Table* getIncompleteCFG();
    Table* getNoReturn();
    Table* getInFunction();

    const std::vector<gtirb::Block>* getCodeBlocks() const;
    std::string getSectionName(uint64_t x) const;
    std::string getFunctionName(gtirb::EA x) const;
    std::string getGlobalSymbolReference(uint64_t ea) const;
    std::string getGlobalSymbolName(uint64_t ea) const;
    const PLTReference* const getPLTDataReference(uint64_t ea) const;
    const SymbolicData* const getSymbolicData(uint64_t ea) const;
    const SymbolMinusSymbol* const getSymbolMinusSymbol(uint64_t ea) const;
    const String* const getString(uint64_t ea) const;
    const DecodedInstruction* const getDecodedInstruction(uint64_t ea) const;
    const OpIndirect* const getOpIndirect(uint64_t x) const;
    const OpRegdirect* const getOpRegdirect(uint64_t x) const;
    uint64_t getOpRegdirectCode(std::string name) const;
    const OpImmediate* const getOpImmediate(uint64_t x) const;
    const MovedDataLabel* const getMovedDataLabel(uint64_t x) const;
    const gtirb::Relocation* const getRelocation(const std::string& x) const;
    const gtirb::Section* const getSection(const std::string& x) const;

    bool getIsAmbiguousSymbol(const std::string& ea) const;

    static void AdjustPadding(std::vector<gtirb::Block>& blocks);
    static std::string CleanSymbolNameSuffix(std::string x);
    static std::string AdaptOpcode(const std::string& x);
    static std::string AdaptRegister(const std::string& x);
    static std::string GetSizeName(uint64_t x);
    static std::string GetSizeName(const std::string& x);
    static std::string GetSizeSuffix(const OpIndirect& x);
    static std::string GetSizeSuffix(uint64_t x);
    static std::string GetSizeSuffix(const std::string& x);
    static bool GetIsReservedSymbol(const std::string& x);
    static std::string AvoidRegNameConflicts(const std::string& x);

private:
    std::vector<DirectCall>* getDirectCall();
    std::vector<MovedLabel>* getMovedLabel();
    std::vector<PLTReference>* getPLTCodeReference();
    std::vector<SymbolicOperand>* getSymbolicOperand();
    const PLTReference* const getPLTCodeReference(uint64_t ea) const;
    const DirectCall* const getDirectCall(uint64_t ea) const;
    const MovedLabel* const getMovedLabel(uint64_t x, uint64_t index) const;
    const SymbolicOperand* const getSymbolicOperand(uint64_t x, uint64_t opNum) const;
    std::vector<PLTReference>* getPLTDataReference();
    std::vector<uint64_t>* getLabeledData();
    std::vector<SymbolicData>* getSymbolicData();
    std::vector<SymbolMinusSymbol>* getSymbolMinusSymbol();
    std::vector<MovedDataLabel>* getMovedDataLabel();
    std::vector<String>* getString();

    void createCodeBlocks();
    void buildDataGroups();

    ///
    /// Parse the statistics facts file.
    ///
    void parseSymbol(const std::string& x);
    void parseSection(const std::string& x);
    void parseRelocation(const std::string& x);
    void parseDecodedInstruction(const std::string& x);
    void parseOpRegdirect(const std::string& x);
    void parseOpImmediate(const std::string& x);
    void parseOpIndirect(const std::string& x);
    void parseDataByte(const std::string& x);

    void parseBlock(const std::string& x);
    void parseCodeInblock(const std::string& x);
    void parseRemainingEA(const std::string& x);
    void parseMainFunction(const std::string& x);
    void parseStartFunction(const std::string& x);
    void parseFunctionEntry(const std::string& x);
    void parseAmbiguousSymbol(const std::string& x);
    void parseDirectCall(const std::string& x);
    void parsePLTCodeReference(const std::string& x);
    void parsePLTDataReference(const std::string& x);
    void parseSymbolicOperand(const std::string& x);
    void parseMovedLabel(const std::string& x);
    void parseLabeledData(const std::string& x);
    void parseSymbolicData(const std::string& x);
    void parseSymbolMinusSymbol(const std::string& x);
    void parseMovedDataLabel(const std::string& x);
    void parseString(const std::string& x);
    void parseBSSData(const std::string& x);
    void parseStackOperand(const std::string& x);
    void parsePreferredDataAccess(const std::string& x);
    void parseDataAccessPattern(const std::string& x);
    void parseDiscardedBlock(const std::string& x);
    void parseDirectJump(const std::string& x);
    void parsePCRelativeJump(const std::string& x);
    void parsePCRelativeCall(const std::string& x);
    void parseBlockOverlap(const std::string& x);
    void parseDefUsed(const std::string& x);
    void parsePairedDataAccess(const std::string& x);
    void parseValueReg(const std::string& x);
    void parseIncompleteCFG(const std::string& x);
    void parseNoReturn(const std::string& x);
    void parseInFunction(const std::string& x);
    // these are facts generated by the decoder
    std::vector<DecodedInstruction> instruction;
    std::vector<OpRegdirect> op_regdirect;
    std::vector<OpImmediate> op_immediate;
    std::vector<OpIndirect> op_indirect;

    // these facts are necessary for printing the asm
    std::vector<uint64_t> block;
    std::vector<CodeInBlock> code_in_block;
    std::vector<uint64_t> remaining_ea;
    std::vector<uint64_t> main_function;
    std::vector<uint64_t> start_function;
    std::vector<uint64_t> function_entry;
    std::vector<std::string> ambiguous_symbol;
    std::vector<DirectCall> direct_call;
    std::vector<PLTReference> plt_code_reference;
    std::vector<PLTReference> plt_data_reference;
    std::vector<SymbolicOperand> symbolic_operand;
    std::vector<MovedLabel> moved_label;
    std::vector<uint64_t> labeled_data;
    std::vector<SymbolicData> symbolic_data;
    std::vector<SymbolMinusSymbol> symbol_minus_symbol;
    std::vector<MovedDataLabel> moved_data_label;
    std::vector<String> string;
    std::vector<uint64_t> bss_data;

    // these facts are only used for generating hints
    Table stack_operand{2};
    Table preferred_data_access{2};
    Table data_access_pattern{4};

    // these facts are only collected for printing debugging information
    Table discarded_block{1};
    Table direct_jump{2};
    Table pc_relative_jump{2};
    Table pc_relative_call{2};
    Table block_overlap{2};
    Table def_used{4};
    Table paired_data_access{6};
    Table value_reg{7};
    Table incomplete_cfg{1};
    Table no_return{1};
    Table in_function{2};
};

const std::pair<std::string, int>* getDataSectionDescriptor(const std::string& name);
