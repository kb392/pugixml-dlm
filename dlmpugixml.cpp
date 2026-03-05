/*****************************************************************************/
/* DLM модуль для RSL                                                        */   
/* XML parser https://github.com/zeux/pugixml                                */
/* версия 0.0.0 (08.02.2026)                                                 */
/* tema@mail.ru                                                              */
/*****************************************************************************/

//#define RSL_EXTERN_IMPL
//#include <boost/bimap.hpp>

#include <string>
#include <regex>
#include <windows.h>
#include "pugixml.hpp"
#include <rsl/dlmintf.h>
#include "dlmpugixml.hpp"
#include "dlmpugixml_node.hpp"
#include "dlmpugixml_nodeset.hpp"
#include "dlmparmtools.hpp"

char * rsGetStringParam(int iParam, char * defStr) {
    VALUE *vString;
    if (!GetParm (iParam,&vString) || vString->v_type != V_STRING) {
        if(defStr)
            return defStr;
        else
            RslError("Параметр №%i должен быть строкой",(iParam+1));
        }
    return vString->value.string;
}

char * rsGetFilePathParam(int iParam) {
    VALUE *vFilePath;
    if (!GetParm (iParam,&vFilePath) || vFilePath->v_type != V_STRING)
        RslError("Параметр №%i должен быть строкой",(iParam+1));
    char * sPath=(char *)malloc(sizeof(char)*strlen(vFilePath->value.string)+sizeof(char));
    OemToCharBuff(vFilePath->value.string, sPath, strlen(vFilePath->value.string));
    sPath[strlen(vFilePath->value.string)]='\0';
    return sPath;
}


char * rsGetXPathParamCutNS(int iParam) {
    VALUE *vFilePath;
    if (!GetParm (iParam,&vFilePath) || vFilePath->v_type != V_STRING)
        RslError("Параметр №%i должен быть строкой",(iParam+1));
    char * sPath=(char *)malloc(sizeof(char)*strlen(vFilePath->value.string)+sizeof(char));
    OemToCharBuff(vFilePath->value.string, sPath, strlen(vFilePath->value.string));
    sPath[strlen(vFilePath->value.string)]='\0';

    //print("xpath %s", sPath);

    std::string result = std::regex_replace(std::string(sPath), std::regex("\\w+:"), std::string(""));
    strcpy(sPath, result.c_str());

    //print("-> %s\n", sPath);

    return sPath;
}



class  CPugixmlXPathNode{

    public:

        void Set(pugi::xpath_node node_) {
            node = node_;
        }

        CPugixmlXPathNode(TGenObject *pThis = NULL) {

        }

        ~CPugixmlXPathNode() {
        }

        RSL_CLASS(CPugixmlXPathNode)

        RSL_INIT_DECL() 
        { 
            VALUE *v;
            GetParm (*firstParmOffs, &v);
        }

        RSL_METHOD_DECL(GetName)
        {
            int iRet;
            const pugi::char_t* name = node.node().name();
            //char * name = node.node().name();

            ValueClear(retVal);
            ValueSet(retVal, V_STRING, (void *)name);

            return 0;
        }

    private:
        pugi::xpath_node node;
};





class  CPugixml{
    public:

        CPugixml (TGenObject *pThis = NULL) {
            ValueMake(&m_MuVar);

        }

        ~CPugixml () {
            ValueClear(&m_MuVar);
        }

        RSL_CLASS(CPugixml)

        RSL_INIT_DECL() 
        { 
            VALUE *v;
            GetParm (*firstParmOffs,&v);
        }

        RSL_METHOD_DECL(LoadFile)
        {
            int iRet;
            char * szFilePath;

            if ((szFilePath = rsGetFilePathParam(1)) == NULL)
                RslError("Ошибка получения имени файла"); 

            parse_result =  doc.load_file(szFilePath);

            iRet = parse_result.status;

            ValueClear(retVal);
            ValueSet(retVal, V_INTEGER, &iRet);
            free(szFilePath);
            return 0;
        }

        RSL_METHOD_DECL(SelectNodes)
        {
            char * szXPath;

            if ((szXPath = rsGetFilePathParam(1)) == NULL)
                RslError("Ошибка получения xpath"); 

            pugi::xpath_node_set node_set = doc.select_nodes(szXPath);

            TGenObject *obj;
            CPugixmlNodeSet *cppObj;
            TGenClass *cls;

            cls = RslFindUniClass("CPugixmlNodeSet");
            obj = CreateObjectOfClassEx(cls, NULL, (void**)&cppObj);
            cppObj->Set(node_set);

            ReturnVal(V_GENOBJ,obj);
            free(szXPath);
            return 0;
        }

        RSL_METHOD_DECL(SelectSingleNode)
        {
            char * szXPath;

            if ((szXPath = rsGetFilePathParam(1)) == NULL)
                RslError("Ошибка получения xpath"); 

            pugi::xpath_node node = doc.select_node(szXPath);

            TGenObject *obj;
            CPugixmlNode *cppObj;
            TGenClass *cls;

            cls = RslFindUniClass("CPugixmlNode");
            obj = CreateObjectOfClassEx(cls, NULL, (void**)&cppObj);
            cppObj->Set(node.node());

            ReturnVal(V_GENOBJ, obj);
            free(szXPath);
            return 0;
        }

    private:
        VALUE m_MuVar;
        pugi::xml_document doc;
        pugi::xml_parse_result parse_result; //  = doc.load_file("tree.xml")

};


RSL_CLASS_BEGIN(CPugixmlNode)
    RSL_INIT
    RSL_METH  (GetName)
    RSL_METH  (GetAttribute)
    RSL_METH  (SelectNodes)
    RSL_METH  (SelectSingleNode)
    RSL_METH  (Text)
RSL_CLASS_END  

RSL_CLASS_BEGIN(CPugixmlXPathNode)
    RSL_INIT
    RSL_METH  (GetName)
RSL_CLASS_END  

RSL_CLASS_BEGIN(CPugixmlNodeSet)
    RSL_INIT
    RSL_METH  (Next)
    RSL_PROP_METH  (Size)
    RSL_PROP_METH  (Length)
    RSL_PROP_METH  (Empty)
    RSL_METH  (Item)
RSL_CLASS_END  

RSL_CLASS_BEGIN(CPugixml)
    RSL_INIT
    RSL_METH  (LoadFile)
    RSL_METH  (SelectNodes)
    RSL_METH  (SelectSingleNode)
RSL_CLASS_END  


EXP32 void DLMAPI EXP AddModuleObjects (void)
{
    // setlocale(LC_ALL,".866");
    RslAddUniClass(CPugixml::TablePtr,          true);
    RslAddUniClass(CPugixmlNodeSet::TablePtr,   false);
    RslAddUniClass(CPugixmlNode::TablePtr,      false);
    RslAddUniClass(CPugixmlXPathNode::TablePtr, false);
}                     
