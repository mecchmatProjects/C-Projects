//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.cpp source file
//

#include "OMG8.h"

SymbolContainer::SymbolContainer() : symbolBuffer(0) {}

SymbolContainer::SymbolContainer(size_t initialCapacity) :
    symbolBuffer(initialCapacity) {}

SymbolContainer::SymbolContainer(const std::vector<uint64_t>& initialSequence) :
    symbolBuffer(initialSequence) {}

SymbolContainer::SymbolContainer(const std::vector<unsigned char>& encodedData) {
    DecompressSymbols(encodedData);
}

std::vector<unsigned char> SymbolContainer::CompressSymbols() {
    size_t compressedLength = 0;
    std::vector<unsigned char> compressedData;

    // Calculate compressed buffer size
    for (const auto& symbol : symbolBuffer) {
        uint64_t tempSymbol = symbol;
        compressedLength += (tempSymbol == 0) ? 1 : 0;
        while (tempSymbol > 0) {
            tempSymbol /= 128;
            compressedLength++;
        }
    }

    compressedData.resize(compressedLength);
    size_t currentIndex = 0;

    // Perform actual compression
    for (const auto& symbol : symbolBuffer) {
        uint64_t remainingSymbol = symbol;
        while (true) {
            unsigned char currentByte = remainingSymbol & 127;
            if (remainingSymbol < 128) {
                compressedData[currentIndex++] = currentByte;
                break;
            } else {
                compressedData[currentIndex++] = currentByte | 128;
                remainingSymbol -= (currentByte | 128);
                remainingSymbol /= 128;
            }
        }
    }

    return compressedData;
}

void SymbolContainer::DecompressSymbols(const std::vector<unsigned char>& compressedBytes) {
    size_t decompressedLength = 0;
    for (const auto& byte : compressedBytes) {
        if ((byte & 128) == 0) decompressedLength++;
    }

    symbolBuffer.resize(decompressedLength);
    size_t currentSymbolIndex = 0;
    uint64_t multiplier = 1;

    for (const auto& byte : compressedBytes) {
        symbolBuffer[currentSymbolIndex] += (multiplier * byte);
        multiplier *= 128;

        if ((byte & 128) == 0) {
            currentSymbolIndex++;
            multiplier = 1;
        }
    }
}

void SymbolContainer::InsertSymbol(size_t position, const SymbolContainer& sequence) {
    std::vector<uint64_t> tempBuffer = symbolBuffer;
    symbolBuffer.resize(tempBuffer.size() + sequence.GetLength());

    // Copy elements before insertion point
    std::copy(tempBuffer.begin(), tempBuffer.begin() + position, symbolBuffer.begin());

    std::copy(sequence.symbolBuffer.begin(), sequence.symbolBuffer.end(),
              symbolBuffer.begin() + position);

    std::copy(tempBuffer.begin() + position, tempBuffer.end(),
              symbolBuffer.begin() + position + sequence.GetLength());
}

void SymbolContainer::InsertSymbol(size_t position, uint64_t singleSymbol) {
    std::vector<uint64_t> tempBuffer = symbolBuffer;
    symbolBuffer.resize(tempBuffer.size() + 1);

    std::copy(tempBuffer.begin(), tempBuffer.begin() + position, symbolBuffer.begin());
    symbolBuffer[position] = singleSymbol;
    std::copy(tempBuffer.begin() + position, tempBuffer.end(),
              symbolBuffer.begin() + position + 1);
}

SymbolContainer SymbolContainer::ExtractSubsequence(size_t start, size_t end) const {
    SymbolContainer result(end - start);
    std::copy(symbolBuffer.begin() + start, symbolBuffer.begin() + end, result.symbolBuffer.begin());
    return result;
}

ssize_t SymbolContainer::LocateSubsequence(const SymbolContainer& searchSequence) const {
    for (size_t i = 0; i + searchSequence.GetLength() < symbolBuffer.size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < searchSequence.GetLength(); ++j) {
            if (searchSequence[j] != symbolBuffer[i + j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

void SymbolContainer::DisplaySymbols() {
    for (const auto& symbol : symbolBuffer) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;
}

void SymbolContainer::DisplaySymbols(std::ostream* outputStream) {
    for (const auto& symbol : symbolBuffer) {
        *outputStream << symbol << " ";
    }
    *outputStream << std::endl;
}

void SymbolContainer::InputSymbols(size_t length) {
    symbolBuffer.resize(length);
    for (auto& symbol : symbolBuffer) {
        std::cin >> symbol;
    }
}

void SymbolContainer::InputSymbols(std::istream* inputStream, size_t length) {
    symbolBuffer.resize(length);
    for (auto& symbol : symbolBuffer) {
        *inputStream >> symbol;
    }
}

uint64_t SymbolContainer::ConvertToInteger(uint64_t base) const {
    uint64_t result = 0;
    for (const auto& symbol : symbolBuffer) {
        if (symbol >= base) return -1;
        result = result * base + symbol;
    }
    return result;
}

void SymbolContainer::InitializeFromInteger(uint64_t number, uint64_t base) {
    uint64_t tempNumber = number;
    size_t digitCount = (tempNumber == 0) ? 1 : 0;

    while (tempNumber > 0) {
        digitCount++;
        tempNumber /= base;
    }

    symbolBuffer.resize(digitCount);
    tempNumber = number;

    for (ssize_t i = digitCount - 1; i >= 0; --i) {
        symbolBuffer[i] = tempNumber % base;
        tempNumber /= base;
    }
}

size_t SymbolContainer::GetLength() const {
    return symbolBuffer.size();
}

uint64_t& SymbolContainer::operator[](size_t index) {
    return symbolBuffer[index];
}

const uint64_t& SymbolContainer::operator[](size_t index) const {
    return symbolBuffer[index];
}