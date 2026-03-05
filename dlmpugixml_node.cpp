#include "pugixml.hpp"
#include <rsl/dlmintf.h>
#include "dlmpugixml_node.hpp"
#include "dlmpugixml_nodeset.hpp"
#include "dlmparmtools.hpp"

void CPugixmlNode::Set(pugi::xml_node node_) {
    node = node_;
}

CPugixmlNode::CPugixmlNode(TGenObject *pThis = 0) {

}

CPugixmlNode::~CPugixmlNode() {
}

// private: 
int __cdecl CPugixmlNode::thunk_Constructor (void *p, VALUE *obj) {
    new(p) CPugixmlNode (); 
    return 0; 
} 

void * __cdecl CPugixmlNode::thunk_Constructor2 (void *p, TGenObject *obj) { 
    return new(p) CPugixmlNode (obj); 
}
 
int __cdecl CPugixmlNode::thunk_Destructor (void *p,VALUE*) { 
    delete (CPugixmlNode*)p; 
    return 0;
} 

void* CPugixmlNode::operator new (size_t, void *p) { 
    return p; 
} 

void CPugixmlNode::operator delete (void*, void*) {
} 

void* CPugixmlNode::operator new (size_t) { 
    return 0; 
} 

void CPugixmlNode::operator delete (void*) {
} 

//public: 
//TMethodTable * CPugixmlNode::TablePtr; 
//TMethodTable CPugixmlNode::_Table; 

//private: typedef CPugixmlNode thisCls_t; static TMethodEntry _Entries [];
//typedef CPugixmlNode CPugixmlNode::thisCls_t; 
//TMethodEntry CPugixmlNode::_Entries [];

int __cdecl CPugixmlNode::thunk_Init (void *p,VALUE *v) { 
    ((thisCls_t*)p)->Init ((int*)v); 
    return 0; 
} 

void CPugixmlNode::Init (int *firstParmOffs) 
{ 
    VALUE *v;
    ((RSLCALLTBL*)ExeExports)->ptr_GetParm (*firstParmOffs, &v);
}

int __cdecl CPugixmlNode::thunk_GetName (void *p, VALUE *v) { 
    return ((thisCls_t*)p)->GetName (v); 
} 

int CPugixmlNode::GetName (VALUE *retVal)
{
    int iRet;
    const pugi::char_t* name = node.name();
    

    ((RSLCALLTBL*)ExeExports)->ptr_ValueClear(retVal);
    ((RSLCALLTBL*)ExeExports)->ptr_ValueSet(retVal, V_STRING, (void *)name);

    return 0;
}

int __cdecl CPugixmlNode::thunk_GetAttribute (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->GetAttribute (v); 
} 

int CPugixmlNode::GetAttribute (VALUE *retVal)
{
    int iRet;

    char * szXPath;

    if ((szXPath = rsGetFilePathParam(1)) == 0)
        ((RSLCALLTBL*)ExeExports)->ptr_RslError("Ошибка получения xpath"); 

    const pugi::char_t* val = node.attribute(szXPath).value();

    ((RSLCALLTBL*)ExeExports)->ptr_ValueClear(retVal);
    ((RSLCALLTBL*)ExeExports)->ptr_ValueSet(retVal, V_STRING, (void *)val);

    // free(szXPath);
    return 0;
}


int __cdecl CPugixmlNode::thunk_SelectNodes (void *p,VALUE *v) { 
    return ((thisCls_t*)p)->SelectNodes (v); 
} 

int CPugixmlNode::SelectNodes (VALUE *retVal)
{
    char * szXPath;

    if ((szXPath = rsGetFilePathParam(1)) == 0)
        ((RSLCALLTBL*)ExeExports)->ptr_RslError("Ошибка получения xpath"); 

    pugi::xpath_node_set node_set = node.select_nodes(szXPath);

    TGenObject *obj;
    CPugixmlNodeSet *cppObj;
    TGenClass *cls;

    cls = RslFindUniClass("CPugixmlNodeSet");
    obj = CreateObjectOfClassEx(cls, 0, (void**)&cppObj);
    cppObj->Set(node_set);

    ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_GENOBJ,obj);

    // free(szXPath);
    return 0;
}

int __cdecl CPugixmlNode::thunk_SelectSingleNode (void *p, VALUE *v) { 
    return ((thisCls_t*)p)->SelectSingleNode(v); 
} 

int CPugixmlNode::SelectSingleNode (VALUE *retVal)
{
    char * szXPath;

    if ((szXPath = rsGetFilePathParam(1)) == 0)
        ((RSLCALLTBL*)ExeExports)->ptr_RslError("Ошибка получения xpath"); 

    pugi::xpath_node result_node = node.select_node(szXPath, PUGIXML_NULL);

    TGenObject *obj;
    CPugixmlNode *cppObj;
    TGenClass *cls;

    cls = RslFindUniClass("CPugixmlNode");
    obj = CreateObjectOfClassEx(cls, NULL, (void**)&cppObj);
    cppObj->Set(result_node.node());

    ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_GENOBJ,obj);

    // free(szXPath);
    return 0;
}

int __cdecl CPugixmlNode::thunk_Text (void *p, VALUE *v) { 
    return ((thisCls_t*)p)->Text (v); 
} 

int CPugixmlNode::Text (VALUE *retVal)
{
    int iRet;
    const char * result = node.text().get();
    

    ((RSLCALLTBL*)ExeExports)->ptr_ValueClear(retVal);
    ((RSLCALLTBL*)ExeExports)->ptr_ValueSet(retVal, V_STRING, (void *)result);

    return 0;
}



    //private:
    //    pugi::xml_node node;
