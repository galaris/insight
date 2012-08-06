/*-
 * Copyright (c) 2010-2012, Centre National de la Recherche Scientifique,
 *                          Institut Polytechnique de Bordeaux,
 *                          Universite Bordeaux 1.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "x86_32_translation_functions.hh"

using namespace std;

static Expr *
s_flag_at_position (x86_32::parser_data &data, const char *flagname, int pos)
{
  Expr *flag = BinaryApp::create (BV_OP_LSH, data.get_flag (flagname),
				  Constant::create (pos, 0, BV_DEFAULT_SIZE),
				  0, 8);
  return flag;
}

X86_32_TRANSLATE_0_OP(LAHF)
{
  Expr *alvalue = BinaryApp::create (BV_OP_OR, data.get_flag ("cf"),
				     Constant::create (2, 0, 8),
				     0, 8);

  alvalue = BinaryApp::create (BV_OP_OR, alvalue,
			       s_flag_at_position (data, "pf", 2),
			       0, 8);
  alvalue = BinaryApp::create (BV_OP_OR, alvalue,
			       s_flag_at_position (data, "af", 4),
			       0, 8);
  alvalue = BinaryApp::create (BV_OP_OR, alvalue,
			       s_flag_at_position (data, "zf", 6),
			       0, 8);
  alvalue = BinaryApp::create (BV_OP_OR, alvalue,
			       s_flag_at_position (data, "sf", 7),
			       0, 8);

  data.mc->add_assignment (data.start_ma, data.get_register ("ah"), alvalue,
			   data.next_ma);
}

X86_32_TRANSLATE_0_OP(SAHF)
{
  MicrocodeAddress from (data.start_ma);
  Expr *ah = data.get_register ("ah");

  x86_32_assign_CF (from, data, ah->extract_bit_vector (0,1));
  x86_32_assign_PF (from, data, ah->extract_bit_vector (2,1));
  x86_32_assign_AF (from, data, ah->extract_bit_vector (4,1));
  x86_32_assign_ZF (from, data, ah->extract_bit_vector (6,1));
  x86_32_assign_SF (from, data, ah->extract_bit_vector (7,1), &data.next_ma);
  ah->deref ();
}

X86_32_TRANSLATE_2_OP(LEA)
{
  LValue *dst = (LValue *) op2;
  Expr *src;

  if (dst->get_bv_size () == 16 && ! data.addr16)
    src = op1->extract_bit_vector (0, 16);
  else 
    src = op1->ref ();
	
  data.mc->add_assignment (data.start_ma, dst, src, &data.next_ma);
  op1->deref ();
}

X86_32_TRANSLATE_1_OP(LGDT)
{
  x86_32_skip (data);
  op1->deref ();
}

X86_32_TRANSLATE_1_OP(LIDT)
{
  x86_32_skip (data);
  op1->deref ();
}

X86_32_TRANSLATE_1_OP(LLDT)
{
  x86_32_skip (data);
  op1->deref ();
}

X86_32_TRANSLATE_1_OP(LMSW)
{
  x86_32_skip (data);
  op1->deref ();
}

X86_32_TRANSLATE_0_OP(STC)
{
  data.mc->add_assignment (data.start_ma, data.get_flag ("cf"),
			   Constant::one (1), data.next_ma);
}

X86_32_TRANSLATE_0_OP(STD)
{
  data.mc->add_assignment (data.start_ma, data.get_flag ("df"),
			   Constant::one (1), data.next_ma);
}

