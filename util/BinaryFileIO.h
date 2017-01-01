#include <cstdio>

#pragma once

namespace FileMode {
    struct Writer {
        static std::FILE* open(const char *fileName) {
            return std::fopen(fileName, "w");
        }
    };
    struct Reader {
        static std::FILE* open(const char *fileName) {
            return std::fopen(fileName, "r");
        }
    };
};

enum SeekMode {
    FromStart = SEEK_SET,
    FromCurrent = SEEK_CUR,
    FromEnd = SEEK_END
};

template <typename Mode>
class BinaryFileIO {
public:
    BinaryFileIO() {}
    BinaryFileIO(const BinaryFileIO& other) = delete;
    BinaryFileIO(const char* fileName) :
      m_fileHandle{ Mode::open(fileName) }
    {}

    ~BinaryFileIO() {
        close();
    }

    BinaryFileIO& operator = (const BinaryFileIO& other) = delete;

    bool isOpen() const {
        return m_fileHandle != nullptr;
    }

    explicit operator bool() const {
        return isOpen();
    }

    void open(const char* fileName);
    void close();

    long tell() const {
        return std::ftell(const_cast<file_type*>(file()));
    }
    bool seek(size_t offset, enum SeekMode mode = SeekMode::FromStart) {
        return std::fseek(file(), offset, mode) == 0;
    }

protected:
    using file_type = std::FILE;

    file_type* file() {
        return m_fileHandle;
    }
    const file_type* file() const {
        return m_fileHandle;
    }

private:
    file_type* m_fileHandle = nullptr;
};

#include "BinaryFileIO.tpp"
