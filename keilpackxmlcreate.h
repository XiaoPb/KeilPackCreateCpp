#ifndef KEILPACKXMLCREATE_H
#define KEILPACKXMLCREATE_H
#include <cstdio>
#include <cstdint>
#include <string>
using namespace std;

class KeilPackXmlCreate
{
public:
    typedef enum Keil_Params_State{
        Params_OK = 0x00,
        Params_Name_ERROR = 0x01,
        Params_Type_ERROR = 0x02,
        Params_Name_Type_ERROR = 0x03,
    }Keil_Params_State;

    KeilPackXmlCreate();

    bool setKeilPackName(string name);
    bool setKeilPackVersion(string version);
    bool setKeilPackType(string type);
    bool setKeilPackAuthor(string author);

    bool setKeilPackParams(string name, string type, string version, string author);
    bool setKeilPackParams(string name, string type, string version);
    bool setKeilPackParams(string name, string type);

    Keil_Params_State KeilPackParams(void);

    bool KeilCreatePdscFile(void);
private:
    string Pack_Name;
    string Pack_Version;
    string Pack_Type;
    string Pack_Author;
};

#endif // KEILPACKXMLCREATE_H
