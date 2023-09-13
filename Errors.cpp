#include "Errors.h"
#include <algorithm>

std::string Error::StringWithArrows(std::string text, Position pos_Start, Position pos_End)
{
    std::string res = std::string();

    // Calculate indices
    int idxStart = text.find_last_of("\n");
    if(idxStart == std::string::npos) idxStart = -1;
    int idxEnd = text.find_first_of("\n", idxStart + 1);
    if(idxEnd < 0) idxEnd = text.size();

    int lineCount = pos_End.ln - pos_Start.ln + 1;
    for (size_t i = 0; i < lineCount; i++)
    {
        // Calculate line columns
        std::string line = std::string(&text[idxStart], &text[idxEnd]);
        int col_Start = i == 0 ? pos_Start.col : 0;
        int col_End = i == lineCount - 1 ? pos_End.col : line.size() - 1;

        // Append to result
        res += line + '\n';
        for(size_t i = 0; i < col_Start; i++) res += ' ';
        for(size_t i = 0; i < col_End - col_Start; i++) res += '^';

        // Recalculate indices
        idxStart = idxEnd;
        idxEnd = text.find_first_of("\n", idxStart + 1);
        if(idxEnd < 0) idxEnd = text.size();
    }
    // Remove all '\t's
    text.erase(std::remove(text.begin(), text.end(), '\t'), text.end());

    return res;
};


Error::Error(Position posStart, Position posEnd, std::string errName, std::string errDet)
    : p_Start(posStart), p_End(posEnd), errorName(errName), errorDetails(errDet)
{
}

std::string Error::As_String()
{
    std::string result = errorName + ": " + errorDetails + '\n';
    result += "File " + p_Start.fn + ", line " + std::to_string(p_Start.ln + 1);
    result += "\n\n" + StringWithArrows(p_Start.ftxt, p_Start, p_End);
    return result;
}

IllegalCharError::IllegalCharError(Position posStart, Position posEnd, std::string errDet)
    : Error(posStart, posEnd, "IllegalCharError", errDet) {}

InvalidSyntaxError::InvalidSyntaxError(Position posStart, Position posEnd, std::string errDet)
    : Error(posStart, posEnd, "InvalidSyntaxError", errDet) {}

RuntimeError::RuntimeError(Position posStart, Position posEnd, std::string errDet, std::shared_ptr<Context> _context)
    : Error(posStart, posEnd, "RuntimeError", errDet), context(_context) {}

std::string RuntimeError::GenerateTraceback()
{
    std::string res = std::string();
    Position pos = p_Start;
    std::shared_ptr ctx = context;

    while(ctx)
    {
        res += "  File " + pos.fn + ", line " + std::to_string(pos.ln + 1) + 
        ", in " + ctx->displayName + '\n';

        pos = ctx->parentEntryPos;
        ctx = ctx->parent;
    }

    return "Traceback (most recent call last):\n" + res;
}

std::string RuntimeError::As_String()
{
    std::string result = GenerateTraceback();
    result += errorName + ": " + errorDetails + '\n';
    result += "\n\n" + StringWithArrows(p_Start.ftxt, p_Start, p_End);
    return result;
}