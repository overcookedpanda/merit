// Copyright (c) 2017-2019 The Merit Foundation
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MERIT_SCRIPT_SCRIPT_ERROR_H
#define MERIT_SCRIPT_SCRIPT_ERROR_H

typedef enum ScriptError_t
{
    SCRIPT_ERR_OK = 0,
    SCRIPT_ERR_UNKNOWN_ERROR,
    SCRIPT_ERR_EVAL_FALSE,
    SCRIPT_ERR_OP_RETURN,

    /* Max sizes */
    SCRIPT_ERR_SCRIPT_SIZE,
    SCRIPT_ERR_PUSH_SIZE,
    SCRIPT_ERR_OP_COUNT,
    SCRIPT_ERR_STACK_SIZE,
    SCRIPT_ERR_SIG_COUNT,
    SCRIPT_ERR_PUBKEY_COUNT,
    SCRIPT_ERR_BLOCKHEIGHT_COUNT,
    SCRIPT_ERR_BLOCKHEIGHT_INVALID,

    /* Failed verify operations */
    SCRIPT_ERR_VERIFY,
    SCRIPT_ERR_EQUALVERIFY,
    SCRIPT_ERR_CHECKMULTISIGVERIFY,
    SCRIPT_ERR_CHECKSIGVERIFY,
    SCRIPT_ERR_NUMEQUALVERIFY,
    SCRIPT_ERR_CHECKEASYSENDVERIFY,
    SCRIPT_ERR_CHECKOUTPUTCOUNTVERIFY,

    /* Logical/Format/Canonical errors */
    SCRIPT_ERR_BAD_OPCODE,
    SCRIPT_ERR_DISABLED_OPCODE,
    SCRIPT_ERR_INVALID_STACK_OPERATION,
    SCRIPT_ERR_INVALID_ALTSTACK_OPERATION,
    SCRIPT_ERR_UNBALANCED_CONDITIONAL,

    /* CHECKLOCKTIMEVERIFY and CHECKSEQUENCEVERIFY */
    SCRIPT_ERR_NEGATIVE_LOCKTIME,
    SCRIPT_ERR_UNSATISFIED_LOCKTIME,

    SCRIPT_ERR_SIG_PARAMS_PUSHONLY,
    SCRIPT_ERR_EXTRACT_PARAMS,

    /** CHECKOUTPUTSIG **/
    SCRIPT_ERR_BAD_ADDRESS_COUNT,
    SCRIPT_ERR_OUTPUT_INDEX_OUT_OF_BOUNDS,
    SCRIPT_ERR_OUTPUT_UNSUPPORTED,
    SCRIPT_ERR_OUTPUT_NO_ADDRESS_MATCH,
    SCRIPT_ERR_OUTPUT_NOT_ENOUGH_PARAMS,

    /* Malleability */
    SCRIPT_ERR_SIG_HASHTYPE,
    SCRIPT_ERR_SIG_DER,
    SCRIPT_ERR_MINIMALDATA,
    SCRIPT_ERR_SIG_PUSHONLY,
    SCRIPT_ERR_SIG_HIGH_S,
    SCRIPT_ERR_SIG_NULLDUMMY,
    SCRIPT_ERR_PUBKEYTYPE,
    SCRIPT_ERR_CLEANSTACK,
    SCRIPT_ERR_MINIMALIF,
    SCRIPT_ERR_SIG_NULLFAIL,

    /* softfork safeness */
    SCRIPT_ERR_DISCOURAGE_UPGRADABLE_NOPS,
    SCRIPT_ERR_DISCOURAGE_UPGRADABLE_WITNESS_PROGRAM,

    /* segregated witness */
    SCRIPT_ERR_WITNESS_PROGRAM_WRONG_LENGTH,
    SCRIPT_ERR_WITNESS_PROGRAM_WITNESS_EMPTY,
    SCRIPT_ERR_WITNESS_PROGRAM_MISMATCH,
    SCRIPT_ERR_WITNESS_MALLEATED,
    SCRIPT_ERR_WITNESS_MALLEATED_P2SH,
    SCRIPT_ERR_WITNESS_UNEXPECTED,
    SCRIPT_ERR_WITNESS_PUBKEYTYPE,

    SCRIPT_ERR_ERROR_COUNT
} ScriptError;

#define SCRIPT_ERR_LAST SCRIPT_ERR_ERROR_COUNT

const char* ScriptErrorString(const ScriptError error);

#endif // MERIT_SCRIPT_SCRIPT_ERROR_H
