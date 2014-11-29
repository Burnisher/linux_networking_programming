#ifndef READ_FILE_H_
#define READ_FILE_H_

#include "NonCopyable.h"
#include <string>

class ReadFile : NonCopyable
{
public:
    ReadFile(std::string filename);
    ~ReadFile();
    bool open();

    ssize_t read(char *usrbuf, size_t count);
    ssize_t readn(char *usrbuf, size_t count);
    ssize_t readLine(char *usrbuf, size_t maxlen);

    int readInt();
    int32_t readInt32();
    int64_t readInt64();
    string readLine();

    void close();

private:
    int fd_;
    std::unique_ptr<RobustIO> buffer_;
    const std::string filename_;
};

#endif //READ_FILE_H_
