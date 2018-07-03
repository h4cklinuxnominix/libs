#pragma once
void throws(std::string & str){
        throw(std::runtime_error(str));
}
template<typename T, typename ... Args>
void throws(std::string & str, T what, Args ... args) noexcept{
        str += reinterpret_cast<std::ostringstream*>(&(std::ostringstream() << what))->str();
        throws(str, args...);
}

template<typename T,typename ... Args>
void throws(T what, Args ... args) noexcept{
        std::string first;
        throws(first, what, args...);
}

