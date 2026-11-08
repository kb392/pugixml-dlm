#ifndef DLMPUGIXML_NODESET_H
#define DLMPUGIXML_NODESET_H

class  CPugixmlNodeSet{

    public:

        void Set(pugi::xpath_node_set );
        CPugixmlNodeSet (TGenObject *);
        ~CPugixmlNodeSet ();

    private: 
        static int __cdecl thunk_Constructor (void *p,VALUE *obj);  
        static void * __cdecl thunk_Constructor2 (void *p,TGenObject *obj);
        static int __cdecl thunk_Destructor (void *p,VALUE*);
        void *operator new (size_t,void *p);
        void operator delete (void*,void*);
        void *operator new (size_t);
        void operator delete (void*);

    public: 
        static TMethodTable *TablePtr; 
        static TMethodTable _Table; 

    private: 
        typedef CPugixmlNodeSet thisCls_t; 
        static TMethodEntry _Entries [];

        static int __cdecl thunk_Init (void *p,VALUE *v);
        void Init (int *firstParmOffs);

        static int __cdecl thunk_Next (void *p,VALUE *v);
        int Next (VALUE *retVal);

        static int __cdecl thunk_Item (void *p,VALUE *v);
        int Item (VALUE *retVal);

        static int __cdecl thunk_get_Size (void *p,VALUE *v);
        int get_Size (VALUE *retVal);

        static int __cdecl thunk_get_Length (void *p,VALUE *v);
        int get_Length (VALUE *retVal);

        static int __cdecl thunk_get_Empty (void *p,VALUE *v); 
        int get_Empty (VALUE *retVal);

    private:
        pugi::xpath_node_set node_set;
        int iterate_count; //  = 0
        pugi::xpath_node_set::const_iterator it;
};

#endif 