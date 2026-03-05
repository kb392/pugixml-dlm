#include "pugixml.hpp"
#include <rsl/dlmintf.h>
#include "dlmpugixml_nodeset.hpp"
#include "dlmpugixml_node.hpp"
#include "dlmparmtools.hpp"

void CPugixmlNodeSet::Set(pugi::xpath_node_set node_set_) {
    node_set = node_set_;
}

CPugixmlNodeSet::CPugixmlNodeSet (TGenObject *pThis = 0) {
    iterate_count = 0;
}

CPugixmlNodeSet::~CPugixmlNodeSet () {
}

int __cdecl CPugixmlNodeSet::thunk_Constructor (void *p,VALUE *obj) 
{ 
    new(p) CPugixmlNodeSet (); 
    return 0; 
} 

void * __cdecl CPugixmlNodeSet::thunk_Constructor2 (void *p,TGenObject *obj) 
{ 
    return new(p) CPugixmlNodeSet (obj); 
} 

int __cdecl CPugixmlNodeSet::thunk_Destructor (void *p, VALUE*) 
{ 
    delete (CPugixmlNodeSet*)p; 
    return 0;
} 

void * CPugixmlNodeSet::operator new (size_t,void *p) 
{ 
    return p; 
} 

void CPugixmlNodeSet::operator delete (void*,void*) {
} 

void * CPugixmlNodeSet::operator new (size_t) 
{ 
    return 0; 
} 

void CPugixmlNodeSet::operator delete (void*) 
{
} 

//TMethodTable * CPugixmlNodeSet::TablePtr; 
//TMethodTable CPugixmlNodeSet::_Table; 

// typedef CPugixmlNodeSet CPugixmlNodeSet::thisCls_t; 

//TMethodEntry CPugixmlNodeSet::_Entries [];

int __cdecl CPugixmlNodeSet::thunk_Init (void *p,VALUE *v) 
{ 
    ((thisCls_t*)p)->Init ((int*)v); 
    return 0; 
} 

void CPugixmlNodeSet::Init (int *firstParmOffs) 
{ 
    VALUE *v;
    ((RSLCALLTBL*)ExeExports)->ptr_GetParm (*firstParmOffs, &v);
}

int __cdecl CPugixmlNodeSet::thunk_Next (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->Next (v); 
} 

int CPugixmlNodeSet::Next (VALUE *retVal)
{
    int iRet;

    if (iterate_count == 0)
        it = node_set.begin();

    if (it != node_set.end()) {
        pugi::xpath_node node = *it;
        ++it;
        iterate_count++;

        TGenObject *obj;
        CPugixmlNode *cppObj;
        TGenClass *cls;

        
        cls = RslFindUniClass("CPugixmlNode");
        obj = CreateObjectOfClassEx(cls, 0, (void**)&cppObj);
        cppObj->Set(node.node());

        ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_GENOBJ,obj);

    } else {
        iRet = 0;
        ((RSLCALLTBL*)ExeExports)->ptr_ValueClear(retVal);
        ((RSLCALLTBL*)ExeExports)->ptr_ValueSet(retVal, V_UNDEF, &iRet);
    }
    return 0;
}

int __cdecl CPugixmlNodeSet::thunk_Item (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->Item (v); 
} 

int CPugixmlNodeSet::Item (VALUE *retVal)
{
    VALUE * vParm;

    if (((RSLCALLTBL*)ExeExports)->ptr_GetParm (1,&vParm) && vParm->v_type == V_INTEGER) {

        TGenObject *obj;
        CPugixmlNode *cppObj;
        TGenClass *cls;

        cls = RslFindUniClass("CPugixmlNode");
        obj = CreateObjectOfClassEx(cls, 0, (void**)&cppObj);
        cppObj->Set(node_set[vParm->value.intval].node());

        ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_GENOBJ, obj);
  } else {
        int iRet = 0;
        ((RSLCALLTBL*)ExeExports)->ptr_ValueClear(retVal);
        ((RSLCALLTBL*)ExeExports)->ptr_ValueSet (retVal, V_UNDEF, &iRet);
  }

    return 0;
}


int __cdecl CPugixmlNodeSet::thunk_get_Size (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->get_Size (v); 
} 

int CPugixmlNodeSet::get_Size (VALUE *retVal)  { 
    int iRet=node_set.size();
    ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_INTEGER, &iRet);
    return 0;
}

int __cdecl CPugixmlNodeSet::thunk_get_Length (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->get_Length (v); 
} 

int CPugixmlNodeSet::get_Length (VALUE *retVal)  { 
    int iRet=node_set.size();
    ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_INTEGER, &iRet);
    return 0;
}

int __cdecl CPugixmlNodeSet::thunk_get_Empty (void *p,VALUE *v) 
{ 
    return ((thisCls_t*)p)->get_Empty (v); 
} 

int CPugixmlNodeSet::get_Empty (VALUE *retVal)  { 
    int iRet=node_set.empty();
    ((RSLCALLTBL*)ExeExports)->ptr_ReturnVal(V_BOOL, &iRet);
    return 0;
}
