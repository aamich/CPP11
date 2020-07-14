#include <cctype>
#include <string>
#include <algorithm>

inline std::string trim(const std::string &s)
{
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

// boost
#include <boost/algorithm/string.hpp>

std::string str("hello world! ");
boost::trim_right(str);

// more examples
    #include <boost/algorithm/string.hpp>
    using namespace std;
    using namespace boost;
    
    // ...

    string str1(" hello world! ");
    to_upper(str1);  // str1 == " HELLO WORLD! "
    trim(str1);      // str1 == "HELLO WORLD!"

    string str2=
       to_lower_copy(
          ireplace_first_copy(
             str1,"hello","goodbye")); // str2 == "goodbye world!"

// more
    string str1="     hello world!     ";
    string str2=trim_left_copy(str1);   // str2 == "hello world!     "
    string str3=trim_right_copy(str1);  // str3 == "     hello world!"
    trim(str1);                         // str1 == "hello world!"

    string phone="00423333444";
    // remove leading 0 from the phone number
    trim_left_if(phone,is_any_of("0")); // phone == "423333444"

// more
str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

// more
 str.erase (std::remove (str.begin(), str.end(), ' '), str.end());
