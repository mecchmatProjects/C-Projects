//
// OMG8
// Created by Ю. Петрова
// Комп мат 1
// OMG8.cpp header file
//

#pragma once
#include <vector>
#include <iostream>
#include <cstdint>

class SymbolContainer {
private:
    std::vector<uint64_t> symbolBuffer;

public:
    SymbolContainer();
    explicit SymbolContainer(size_t initialCapacity);
    explicit SymbolContainer(const std::vector<uint64_t>& initialSequence);
    explicit SymbolContainer(const std::vector<unsigned char>& encodedData);

    std::vector<unsigned char> CompressSymbols();
    void DecompressSymbols(const std::vector<unsigned char>& compressedBytes);

    void InsertSymbol(size_t position, const SymbolContainer& sequence);
    void InsertSymbol(size_t position, uint64_t singleSymbol);
    SymbolContainer ExtractSubsequence(size_t start, size_t end) const;
    ssize_t LocateSubsequence(const SymbolContainer& searchSequence) const;

    void DisplaySymbols();
    void DisplaySymbols(std::ostream* outputStream);
    void InputSymbols(size_t length);
    void InputSymbols(std::istream* inputStream, size_t length);

    uint64_t ConvertToInteger(uint64_t base) const;
    void InitializeFromInteger(uint64_t number, uint64_t base);

    size_t GetLength() const;
    uint64_t& operator[](size_t index);
    const uint64_t& operator[](size_t index) const;
};
