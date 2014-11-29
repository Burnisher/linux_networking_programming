#include "ReadFile.h"

ReadFile::ReadFile(std::string filename)
    :fd_(-1),
     filename_(std::move(filename))
{

}

ReadFile::~ReadFile()
{
    if(fd_ != -1)
        close();
}

bool ReadFile::open()
{
    fd_ = ::open(filename_.c_str(), O_RDONLY);
    if(fd == -1)
        return false;

    buffer_.reset(new RobustIO(fd_));
    return true;
}

void ReadFile::close()
{
    ::close(fd_);
    fd_ = -1;
}







