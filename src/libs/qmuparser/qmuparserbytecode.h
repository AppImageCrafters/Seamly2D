/***************************************************************************************************
 **
 **  Original work Copyright (C) 2013 Ingo Berg
 **  Modified work Copyright 2014 Roman Telezhynskyi <dismine(at)gmail.com>
 **
 **  Permission is hereby granted, free of charge, to any person obtaining a copy of this
 **  software and associated documentation files (the "Software"), to deal in the Software
 **  without restriction, including without limitation the rights to use, copy, modify,
 **  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 **  permit persons to whom the Software is furnished to do so, subject to the following conditions:
 **
 **  The above copyright notice and this permission notice shall be included in all copies or
 **  substantial portions of the Software.
 **
 **  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 **  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 **  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 **  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 **  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **
 ******************************************************************************************************/

#ifndef QMUPARSERBYTECODE_H
#define QMUPARSERBYTECODE_H

#include "qmuparserdef.h"
#include "qmuparsererror.h"
#include "qmuparsertoken.h"

/**
 * @file
 * @brief Definition of the parser bytecode class.
 */

namespace qmu
{
struct SToken
{
    ECmdCode Cmd;
    int StackPos;

    union //
    {
        struct //SValData
        {
            qreal  ptr;
            qreal  data;
            qreal  data2;
        } Val;

        struct //SFunData
        {
            // Note: generic_fun_type is merely a placeholder. The real type could be
            //       anything between gun_type1 and fun_type9. I can't use a void
            //       pointer due to constraints in the ANSI standard which allows
            //       data pointers and function pointers to differ in size.
            generic_fun_type ptr;
            int   argc;
            int   idx;
        } Fun;

        struct //SOprtData
        {
            qreal *ptr;
            int offset;
        } Oprt;
    };
};


/**
 * @brief Bytecode implementation of the Math Parser.
 *
 * The bytecode contains the formula converted to revers polish notation stored in a continious
 * memory area. Associated with this data are operator codes, variable pointers, constant
 * values and function pointers. Those are necessary in order to calculate the result.
 * All those data items will be casted to the underlying datatype of the bytecode.
 *
 * @author (C) 2004-2013 Ingo Berg
 */
class QmuParserByteCode
{
public:
    QmuParserByteCode() Q_DECL_NOEXCEPT;
    QmuParserByteCode(const QmuParserByteCode &a_ByteCode) Q_DECL_NOEXCEPT;
    QmuParserByteCode& operator=(const QmuParserByteCode &a_ByteCode) Q_DECL_NOEXCEPT;
    void          Assign(const QmuParserByteCode &a_ByteCode) Q_DECL_NOEXCEPT;
    void          AddVar(qreal a_pVar) Q_DECL_NOEXCEPT;
    void          AddVal(qreal a_fVal) Q_DECL_NOEXCEPT;
    void          AddOp(ECmdCode a_Oprt);
    void          AddIfElse(ECmdCode a_Oprt) Q_DECL_NOEXCEPT;
    void          AddAssignOp(qreal a_pVar) Q_DECL_NOEXCEPT;
    void          AddFun(generic_fun_type a_pFun, int a_iArgc) Q_DECL_NOEXCEPT;
    void          AddBulkFun(generic_fun_type a_pFun, int a_iArgc) Q_DECL_NOEXCEPT;
    void          AddStrFun(generic_fun_type a_pFun, int a_iArgc, int a_iIdx) Q_DECL_NOEXCEPT;
    void          EnableOptimizer(bool bStat) Q_DECL_NOEXCEPT;
    void          Finalize() Q_DECL_NOEXCEPT;
    void          clear() Q_DECL_NOEXCEPT;
    std::size_t   GetMaxStackSize() const Q_DECL_NOEXCEPT;
    std::size_t   GetSize() const Q_DECL_NOEXCEPT;
    const SToken* GetBase() const;
    void          AsciiDump();
private:
    /** @brief Token type for internal use only. */
    typedef QmuParserToken<qreal, string_type> token_type;

    /** @brief Token vector for storing the RPN. */
    typedef QVector<SToken> rpn_type;

    /** @brief Position in the Calculation array. */
    unsigned m_iStackPos;

    /** @brief Maximum size needed for the stack. */
    std::size_t m_iMaxStackSize;

    /** @brief The actual rpn storage. */
    rpn_type  m_vRPN;

    bool m_bEnableOptimizer;

    void ConstantFolding(ECmdCode a_Oprt);
};

//---------------------------------------------------------------------------------------------------------------------
inline void QmuParserByteCode::EnableOptimizer(bool bStat) Q_DECL_NOEXCEPT
{
    m_bEnableOptimizer = bStat;
}

//---------------------------------------------------------------------------------------------------------------------
inline std::size_t QmuParserByteCode::GetMaxStackSize() const Q_DECL_NOEXCEPT
{
    return m_iMaxStackSize+1;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Returns the number of entries in the bytecode.
 */
// cppcheck-suppress unusedFunction
inline std::size_t QmuParserByteCode::GetSize() const Q_DECL_NOEXCEPT
{
    return m_vRPN.size();
}

} // namespace qmu
#endif
