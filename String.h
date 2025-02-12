#include <iostream>
#include <cstring>
#include <algorithm>


class String{

public:
    String(char c){
        buffer_ = new char[capacity_];
        length_ = 1;
        buffer_[0] = c;
        buffer_[length_] = '\0';
    }
    String(const char* c){
        buffer_ = new char[capacity_];
        length_ = strlen(c);
        if(capacity_<length_+1){
            realloc();
        }
        std::copy(c, c+length_, buffer_);
        buffer_[length_] = '\0'; //[]
    }

    String(int n, char c)
    {
        buffer_ = new char[capacity_];
        length_ = n;
        if(capacity_<length_+1){
            realloc();
        }
        std::fill(buffer_, buffer_ + length_, c);
        buffer_[length_]  = '\0';
    }

    String(){
        buffer_ = new char[capacity_];
        buffer_[0] = '\0';
    }

    String(const String &s){
        buffer_ = new char[capacity_];
        length_ = s.length_;
        if(capacity_<length_+1){
            realloc();
        }
        std::copy(s.buffer_, s.buffer_ + s.length_, buffer_);
    }

    ~String(){
        delete[] buffer_;
    }

    //Operators
    // оператор вывода
    friend std::ostream& operator<<(std::ostream& os,const String &s)
    {
        os << s.buffer_;
        return os;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, String &s)
    {
        char* c = new char[500];
        is >> c;

        s = String(c);
        //s.length_ = strlen(c);
        //std::copy(c, c+s.length_, s.buffer_);
        //s.buffer_[s.length_] = '\0'; //[]
        delete[] c;

        return is;
    }

    // оператор присваивания
    String& operator=(const String& other)  {
        if (length_ >= other.length_)
        {
            std::copy(other.buffer_, other.buffer_+other.length_+1,buffer_);
            length_ = other.length_;
            return *this;
        }
        length_ = other.length_;
        realloc();
        std::copy(other.buffer_, other.buffer_+other.length_+1, buffer_);
        
        return *this;
    }

    // Оператор плюс равно
    String& operator +=(const String& other){
        int prev_length = length_;    
        length_ = length_ + other.length_;
        if(capacity_ < length_+1){
            realloc();
        }
        std::copy(other.buffer_,other.buffer_+other.length_, buffer_ + prev_length);
        buffer_[length_] = '\0';
        return *this;
        
    }

    // оператор сложения
    friend String operator+(const String& left, const String& right){
        // adasdas\0 dasdasdsa\0
        // kek = left
        // realoc()
        //copy(kek, right);

        int new_length_ = left.length_ + right.length_;
        int new_capacity_ = new_length_ + 1;

        char* newbuffer_ = new char[new_capacity_];
        std::copy(left.buffer_, left.buffer_ + left.length_, newbuffer_);
        std::copy(right.buffer_, right.buffer_+right.length_, newbuffer_+left.length_);
        newbuffer_[new_length_] = '\0';
        String s;
        s.buffer_ = newbuffer_;
        s.length_ = new_length_;
        s.capacity_ = new_capacity_;
        return s;
    }
    //Булевое равно
    friend bool operator == (const String& left,const String& right){
        if (left.length_ !=  right.length_)
            return false;
        for (int i = 0; i<right.length_; i++){
            if (left.buffer_[i]!=right.buffer_[i])
                return false;
        }
        return true;
            


    }
    // Булевый Оператор не равно
    friend bool operator != (const String& left,const String& right ){
        return !(right == left);
    }
    // Оператор квадратные скобки
    char& operator[](int i){
        return buffer_[i];
    } 
    const char& operator[](int i) const{
        return buffer_[i];
    } 
    // оператор сравнения Меньше
    friend bool operator <(const String& left, const String& right){
        for (int i = 0; i<left.length_; i++){
            if ( left.buffer_[i] < right.buffer_[i]){
                return true; // 
            }
            if (left.buffer_[i]> right.buffer_[i]){
                return false;
            }
        }
        return false; // проверили все, выходим
    }
    // БОльше
    friend bool operator >(const String &left, const String& right){
        return !(left<right);
    }
    // Меньше либо равно
    friend bool operator <=(const String& left, const String& right){
        return ((left==right) || (left < right));
    }
    // Больше либо равно
    friend bool operator >=(const String& left, const String& right){
        return ((left==right) || (left > right));
    }
    // Methods
    //SIZE
    int size()const{
        return length_;
    }
    // Length
    int length()const{
        return length_;
    }
    // CAPACITY
    int capacity()const{
        return  capacity_-1;
    }
    // Добавить символ в конце
    void push_back(char c){
        length_ += 1;
        if(capacity_<length_+1){
            realloc();
        }
        buffer_[length_] = c;
    }
    // Удалить последний символ
    void pop_back(){
        length_ -= 1;
        buffer_[length_] = '\0';

    }
    // ССЫЛКА на первый
    char& front(){
        return *buffer_;
    }
    const char& front() const {
        return *buffer_;
    }
    // ССылка на последний
    char& back(){
        return *(buffer_ + length_-1);
    }

    const char& back() const {
        return *(buffer_ + length_-1);
    }

    // ПУСТА ЛИ СТРОКА
    bool empty()const{
        if (buffer_[0] =='\0'){
            return true;
        }
        return false;
    }
    // очистить строку
    void clear(){
        length_=0;
        buffer_[0] = '\0';
    }
    // Указатель на начало
    char* data(){
        return buffer_;
    }
    const char* data()const {
        return buffer_;
    }
    // Левая сабстринга
    int find(const String& substring)const{
        for (int i = 0; i<(length_ - substring.length_);i++){
            for  (int j = 0; j < substring.length_;j++){
                //std::cout << "i = " << i ;
                //std::cout << "j = " << j << (*this).buffer_[i+j] << '_' << "=" << substring[j] << '\n';
                if((*this).buffer_[i+j]!=substring[j]){
                    break;
                    
                }
                if (j == (substring.length_ - 1)){
                    return i;
                }
            }
        }
        return (*this).length();
    }
    // правая сабстринга
    int rfind(const String& substring)const{
        for (int i = length_ - substring.length_; i>=0;i--){
            for  (int j = 0; j < substring.length_;j++){
                if((*this).buffer_[i+j]!=substring[j]){
                    break;
                    
                }
                if (j == (substring.length_ - 1)){
                    return i;
                }
            }

        }
        return (*this).length();
    }
    // Выделить подстроку с началом в start длиной count
    String substr(const int start, const int count)const{
        //int new_length_ = count;
        //char* newbuffer_ = nullptr;
        String s(count,'0');
        
        std::copy(buffer_+start, buffer_+start+count,s.buffer_);
        return s;
    }
    // сжать capacity до length_
    void shrink_to_fit(){
        int prev_capacity = capacity_;
        capacity_ = length_+1;
        char* temp_buff_ = new char[capacity_];
        std::copy(buffer_, buffer_ + length_,temp_buff_);
        temp_buff_[capacity_] = '\0';
        delete buffer_;
        buffer_ = nullptr;
        buffer_ = temp_buff_;

        
    }
private:
    char* buffer_{ nullptr };
    int length_{ 0 }; 
    int capacity_ {16};
    // перевыделение памяти
    void realloc()
    {
        while(capacity_ < (length_ + 1)){
            capacity_ *= 2;

        }
        char* copybuffer_ = nullptr;
        copybuffer_ = new char[capacity_];
        std::copy(buffer_, buffer_+capacity_/2 + 1,copybuffer_);
        delete[] buffer_;
        buffer_ = copybuffer_;
    }
};