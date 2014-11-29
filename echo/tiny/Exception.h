#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <exception>
//异常类，会用接口即可，暂时不必了解
class Exception : std::exception
{
public:
    explicit Exception(const std::string &message);
    explicit Exception(const char *message);
    virtual ~Exception() throw();  //不抛出异常
    virtual const char* what() const throw(); //打印异常信息
    const char* stackTrace() const throw(); //打印栈痕迹

private:
    void fillStackTrace(); //填充栈痕迹
    std::string demangle(const char* symbol); //反名字改编

    std::string message_;
    std::string stack_;
};

#endif //EXCEPTION_H_