#ifndef SMART_H
#define SMART_H

template<typename T>
class SharedPtr{
public:
    SharedPtr();//默认ptr为空指针
    SharedPtr(T* _ptr);//
    SharedPtr(const SharedPtr& example);//拷贝构造
    SharedPtr& operator=(const SharedPtr& right_op);//赋值重载
    T* operator->();
    T& operator*();
    operator bool();
    bool operator==(SharedPtr& ex);
    T* get();//获取对象保存的指针
    void swap(SharedPtr& p);//交换两对象中的指针
    unsigned getCount();//获取当前对ptr的引用数目
    ~SharedPtr();

private:
    T* ptr;
    unsigned* count;//引用计数
};
#endif





template<typename T>
SharedPtr<T>::SharedPtr()
    :ptr(nullptr), count(nullptr){//默认全为空
}

template<typename T>
SharedPtr<T>::SharedPtr(T* _ptr)
    :ptr(_ptr), count(new unsigned(1)){
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& example){
    this->ptr = example.ptr;
    this->count = example.count;
    if(count != nullptr)
        (*count)++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& right_op){
    if(count != nullptr &&(--(*count) <= 0)){
        delete ptr;
        delete count;
        ptr = nullptr;
        count = nullptr;
    }
    
    //赋值
    ptr = right_op.ptr;
    count = right_op.count;
    //判断右操作数保存的指针是否为空
    if(ptr == nullptr);//空不增加引用数目
    else 
        (*count)++;
    
    return *this;
}

template<typename T>
T* SharedPtr<T>::get(){
    return ptr;
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr<T>& p){
    T* tmp = p.ptr;
    unsigned* ctmp = p.count;
    //交换
    p.ptr = this->ptr;
    p.count = this->count;
    this->ptr = tmp;
    this->count = ctmp;
}

template<typename T>
unsigned SharedPtr<T>::getCount(){
    if(count == nullptr) 
        return 0;
    else    
        return *count;
}

template<typename T>
T* SharedPtr<T>::operator->(){
    return ptr;
}

template<typename T>
T& SharedPtr<T>::operator*(){
    return *ptr;
}

template<typename T>
SharedPtr<T>::operator bool(){
    return ptr != nullptr;
}

template<typename T>
bool SharedPtr<T>::operator==(SharedPtr<T>& Real){
    return ptr == Real.ptr;
}

template<typename T>
SharedPtr<T>::~SharedPtr(){
    if(count != nullptr && (--(*count) == 0)){
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
}