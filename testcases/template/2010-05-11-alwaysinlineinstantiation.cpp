// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<class charT>
class basic_string
{
public:
	basic_string();
	~basic_string();
};

template <class charT>
__attribute__ ((__visibility__("hidden"), __always_inline__)) inline
basic_string<charT>::basic_string()
{
}

template <class charT>
inline
basic_string<charT>::~basic_string()
{
}

typedef basic_string<char> string;

extern template class basic_string<char>;

int main()
{
	string s;
}
