#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <exception>
//�쳣�࣬���ýӿڼ��ɣ���ʱ�����˽�
class Exception : std::exception
{
public:
    explicit Exception(const std::string &message);
    explicit Exception(const char *message);
    virtual ~Exception() throw();  //���׳��쳣
    virtual const char* what() const throw(); //��ӡ�쳣��Ϣ
    const char* stackTrace() const throw(); //��ӡջ�ۼ�

private:
    void fillStackTrace(); //���ջ�ۼ�
    std::string demangle(const char* symbol); //�����ָı�

    std::string message_;
    std::string stack_;
};

#endif //EXCEPTION_H_