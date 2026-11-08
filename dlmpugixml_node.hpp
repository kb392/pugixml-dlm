
#ifndef DLMPUGIXML_NODE_H
#define DLMPUGIXML_NODE_H

class  CPugixmlNode{

    private:
        pugi::xml_node node;

    public:

        void Set(pugi::xml_node); 
        
        CPugixmlNode(TGenObject *); 

        ~CPugixmlNode(); 

    private: 
        static int __cdecl thunk_Constructor (void *, VALUE *); 

        static void * __cdecl thunk_Constructor2 (void *, TGenObject *);

        static int __cdecl thunk_Destructor (void *, VALUE*);

        void *operator new (size_t,void *p);

        void operator delete (void*,void*);

        void *operator new (size_t);

        void operator delete (void*); 

    public: 
        static TMethodTable *TablePtr; 
        static TMethodTable _Table; 

    private: 
        typedef CPugixmlNode thisCls_t; 
        static TMethodEntry _Entries [];

        static int __cdecl thunk_Init (void *, VALUE *);
        void Init (int *);

        static int __cdecl thunk_GetName (void *, VALUE *);
        int GetName (VALUE *);

        static int __cdecl thunk_GetAttribute (void *, VALUE *);
        int GetAttribute (VALUE *);

        static int __cdecl thunk_SelectNodes (void *, VALUE *);
        int SelectNodes (VALUE *);

        static int __cdecl thunk_SelectSingleNode (void *, VALUE *);
        int SelectSingleNode (VALUE *);

        static int __cdecl thunk_Text (void *, VALUE *);
        int Text (VALUE *);
/* */
};

#endif 