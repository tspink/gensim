/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "translate/adapt/BlockJITAdaptorLowering.h"
#include "translate/adapt/BlockJITAdaptorLoweringContext.h"

using namespace archsim::translate::adapt;

bool BlockJITLDMEMCacheLowering::Lower(const captive::shared::IRInstruction*& insn) {	
	const auto &interface = insn->operands[0];
	const auto &offset = insn->operands[1];
	const auto &disp = insn->operands[2];
	const auto &dest = insn->operands[3];
	
	llvm::Value *target_fn = nullptr;
	switch(dest.size) {
		case 1:
			target_fn = GetContext().GetValues().blkRead8Ptr; break;
		case 2:
			target_fn = GetContext().GetValues().blkRead16Ptr; break;
		case 4:
			target_fn = GetContext().GetValues().blkRead32Ptr; break;
		case 8:
		default:
			UNIMPLEMENTED;
	}
	
	auto address_value = GetBuilder().CreateAdd(GetValueFor(offset), GetValueFor(disp));
	auto interface_value = GetValueFor(interface);
	
	auto data = GetBuilder().CreateCall(target_fn, { GetContext().GetThreadPtrPtr(), address_value, interface_value });
	SetValueFor(dest, data);
	
	insn++;
	
	return true;
}

bool BlockJITSTMEMCacheLowering::Lower(const captive::shared::IRInstruction*& insn) {
	const auto &interface = insn->operands[0];
	const auto &value = insn->operands[1];
	const auto &disp = insn->operands[2];
	const auto &offset = insn->operands[3];
	
	llvm::Value *target_fn = nullptr;
	switch(value.size) {
		case 1:
			target_fn = GetContext().GetValues().blkWrite8Ptr; break;
		case 2:
			target_fn = GetContext().GetValues().blkWrite16Ptr; break;
		case 4:
			target_fn = GetContext().GetValues().blkWrite32Ptr; break;
		case 8:
		default:
			UNIMPLEMENTED;
	}
	
	auto address_value = GetBuilder().CreateAdd(GetValueFor(offset), GetValueFor(disp));
	auto interface_value = GetValueFor(interface);
	auto value_value = GetValueFor(value);
	
	GetBuilder().CreateCall(target_fn, { GetContext().GetThreadPtr(), interface_value, address_value, value_value });
	
	insn++;
	
	return true;
}
