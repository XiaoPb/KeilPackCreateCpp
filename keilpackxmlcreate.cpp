#include "keilpackxmlcreate.h"
#include "tinyxml2.h"

using namespace tinyxml2;

KeilPackXmlCreate::KeilPackXmlCreate()
{
    Pack_Name    = "unknown";
    Pack_Type    = "unknown";
    Pack_Author  = "unknown";
    Pack_Version = "1.0.0";
}

bool KeilPackXmlCreate::setKeilPackName(string name)
{
    Pack_Name = name;
    return true;
}
bool KeilPackXmlCreate::setKeilPackVersion(string version)
{
    Pack_Version = version;
    return  true;
}
bool KeilPackXmlCreate::setKeilPackType(string type)
{
    Pack_Type = type;
    return true;
}
bool KeilPackXmlCreate::setKeilPackAuthor(string author)
{
    Pack_Author = author;
    return true;
}
bool KeilPackXmlCreate::setKeilPackParams(string name, string type, string version, string author)
{
    bool ret = true;
    ret = (this->setKeilPackName(name) && this->setKeilPackType(type) &&\
           this->setKeilPackVersion(version) && this->setKeilPackAuthor(author));
    return ret;
}
bool KeilPackXmlCreate::setKeilPackParams(string name, string type, string version)
{
    bool ret = true;
    ret = (this->setKeilPackName(name) && this->setKeilPackType(type) &&\
           this->setKeilPackVersion(version));
    return ret;
}
bool KeilPackXmlCreate::setKeilPackParams(string name, string type)
{
    bool ret = true;
    ret = (this->setKeilPackName(name) && this->setKeilPackType(type));
    return ret;
}

KeilPackXmlCreate::Keil_Params_State KeilPackXmlCreate::KeilPackParams(void)
{
    Keil_Params_State ret = Params_OK;

    if(this->Pack_Name == "unknown")
    {
        ret = Params_Name_ERROR;
    }
    if(this->Pack_Type == "unknown")
    {
        if(ret == Params_OK)
        {
            ret = Params_Type_ERROR;
        }
        else
        {
            ret = Params_Name_Type_ERROR;
        }
    }
    return ret;
}

bool KeilPackXmlCreate::KeilCreatePdscFile(void)
{
    bool ret = true;
    if (this->KeilPackParams() == Params_OK)
    {
        XMLDocument pdsc;
        const char* xml =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                "<package schemaVersion=\"1.4\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema-instance\" xs:noNamespaceSchemaLocation=\"PACK.xsd\">"
                "</package>";
        pdsc.Parse(xml);
        XMLElement* package = pdsc.FirstChildElement( "package" );
        XMLElement* vendor = pdsc.NewElement("vendor");
        vendor->SetText(this->Pack_Author.c_str());
        package->InsertEndChild(vendor);

        XMLElement* name = pdsc.NewElement("name");
        name->SetText(this->Pack_Name.c_str());
        package->InsertEndChild(name);

        XMLElement* description = pdsc.NewElement("description");
        description->SetText((this->Pack_Name + " Software Components").c_str());
        package->InsertEndChild(description);

        XMLElement* url = pdsc.NewElement("url");
        package->InsertEndChild(url);

        XMLElement* releases = pdsc.NewElement("releases");
        package->InsertEndChild(releases);
        XMLElement* release = pdsc.NewElement("release");
        release->SetAttribute("version",this->Pack_Version.c_str());
        release->SetText("first release");
        releases->InsertEndChild(release);

        XMLElement* keywords = pdsc.NewElement("keywords");
        package->InsertEndChild(keywords);
        XMLElement* keyword = pdsc.NewElement("keyword");
        keyword->SetText(this->Pack_Name.c_str());
        keywords->InsertEndChild(keyword);

        XMLElement* components = pdsc.NewElement("components");
        package->InsertEndChild(components);
        XMLElement* component = pdsc.NewElement("component");
        component->SetAttribute("Cclass",this->Pack_Type.c_str());
        component->SetAttribute("Cgroup",(this->Pack_Name + " source files").c_str());
        component->SetAttribute("Cversion","1.0.0");
        components->InsertEndChild(component);

        XMLElement* description_c = pdsc.NewElement("description");
        description_c->SetText((this->Pack_Name + " source files").c_str());
        components->InsertEndChild(description_c);

        XMLElement* files = pdsc.NewElement("files");
        components->InsertEndChild(files);

        for (int i = 0; i < 5; i++)
        {
            XMLElement* file = pdsc.NewElement("file");
            char name_c[] = "inc0/";
            name_c[3] = '0' + i;
            file->SetAttribute("category","include");
            file->SetAttribute("name",name_c);
            files->InsertEndChild(file);
        }
        for (int i = 0; i < 5; i++)
        {
            XMLElement* file = pdsc.NewElement("file");
            char name_c[] = "src/main0.c";
            name_c[8] = '0' + i;
            file->SetAttribute("category","source");
            file->SetAttribute("name",name_c);
            files->InsertEndChild(file);
        }
        for (int i = 0; i < 5; i++)
        {
            XMLElement* file = pdsc.NewElement("file");
            char name_c[] = "src/main0.h";
            name_c[8] = '0' + i;
            file->SetAttribute("category","header");
            file->SetAttribute("name",name_c);
            file->SetAttribute("attr","config");
            files->InsertEndChild(file);
        }

        pdsc.SaveFile("keiltemp.pdsc");

    }
    else
    {
        ret = false;
    }
    return ret;
}


