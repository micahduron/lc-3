#include <cassert>
#include "lc3.h"

namespace LC3 {

static constexpr Word highestBit = 1 << (WordBits - 1);

Value Value::abs() const {
    if (m_word & highestBit) {
        Word negatedNum = ~m_word + 1;

        return { negatedNum };
    }
    return { m_word };
}

size_t Value::bitWidth() const {
    size_t bitCount = 0;
    Word tmpWord = m_word;

    while (tmpWord) {
        tmpWord >>= 1;
        ++bitCount;
    }
    return bitCount;
}

std::optional<Value> Value::restrictWidth(size_t numBits, bool isSigned) const {
    assert(numBits <= WordBits);

    Value testVal = isSigned ? abs() : *this;

    if (testVal.bitWidth() > numBits) {
        return {};
    }
    Word bitMask = (1 << numBits) - 1;

    return { Value(m_word & bitMask) };
}

std::ostream& operator << (std::ostream& outStream, const Value& val) {
    outStream << std::hex << val.get() << std::dec;

    return outStream;
}

} // namespac LC3