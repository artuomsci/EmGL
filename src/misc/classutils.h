#ifndef CLASSUTILS_H
#define CLASSUTILS_H

//--------------------------------------------------------------------
//     No copy macros

#define NO_COPY_CLASS(class_name) \
class_name(const class_name&);\
void operator=(const class_name&);

//--------------------------------------------------------------------
//     This is the interface class for the Memento design pattern

class IMemento {

public:

    ~IMemento() {}

    virtual void PushState() = 0;
    virtual void PopState() = 0;
};

#endif

