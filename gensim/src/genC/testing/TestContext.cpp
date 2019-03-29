/* This file is Copyright University of Edinburgh 2018. For license details, see LICENSE. */

#include "genC/testing/TestContext.h"
#include "arch/testing/TestArch.h"
#include "isa/testing/TestISA.h"
#include "genC/Parser.h"

#include "define.h"

using namespace gensim::genc::testing;
using namespace gensim::genc::ssa;
using gensim::genc::GenCContext;

GenCContext *TestContext::GetTestContext(bool include_instruction, gensim::DiagnosticContext &diag_ctx)
{
	auto test_arch = gensim::arch::testing::GetTestArch();
	IntrinsicManager *intrinsics = new IntrinsicManager(*test_arch);
	GenCContext *gencctx = new GenCContext(*test_arch, *gensim::isa::testing::GetTestISA(include_instruction), *intrinsics, diag_ctx);
	return gencctx;
}

SSAContext *TestContext::CompileSource(GenCContext *ctx, const std::string &source)
{
	auto stream = std::make_shared<std::stringstream>();
	stream->str(source);

	ctx->AddFile(FileContents("in-mem", stream));
	if(!ctx->Parse()) {
		return nullptr;
	} else {
		return ctx->EmitSSA();
	}
}
