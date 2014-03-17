#ifndef TOSTRING_H
#define TOSTRING_H

#include <sstream>
using namespace std;

//-------------------------------------------------
//
// Converts passed int, float, double, etc. to string
//-------------------------------------------------

class ToString {
    public:
        template<class T>
        static string getString(T var) {
            oStringStream.str("");
            oStringStream << var;
            return oStringStream.str();
        }
    protected:
    private:
        ToString();
        virtual ~ToString();

        static ostringstream oStringStream;
};

#endif // TOSTRING_H
