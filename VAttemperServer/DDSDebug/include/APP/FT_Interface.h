
#ifdef FT_Interface_API
#else
#define FT_Interface_API extern "C" _declspec(dllimport)
#endif
#include "PubData.h"


/*******************************************************

  函数名: FT_Appregister
  函数功能:应用构件注册函数接口
  
    返回值：注册成功则返回1，
    查找配置文件失败或配置文件格式不正确，返回-1101；
    配置文件中的元素名不正确，返回-1102;返回应用构件
    注册名无效,返回-1201，IP地址无效，返回-1301；关键变
    量超过限制长度，返回-1401
    参数:  Func            应用构件提供的关键变量更新的回调函数的入口地址
    IPInfo          本节点所在的IP
    KeyValue        关键变量注册信息
    pComponentName   应用构件注册名
********************************************************/
// 20110806 wenyan 修改　将void型改为CallShow
FT_Interface_API int FT_Appregister(char *pComponentName, Type_keyword KeyValue, char *IPInfo, CallShow Func);



/**************************************************

  函数名: FT_PublishKey
  函数功能: 关键变量更新接口，当应用构架算出关键
  变量的之后，调用此函数更
  
    返回值: 新成功则返回1，当更新的关键变量名称未被注
    册时，则更新失败，返回-2101；若更新的关键变
    量信息为NULL时，则更新失败，返回-2102,返回
		  -2103,表示应用构件注册名无效
          参数: pKeybuff         存放关键变量值的缓存
          keyName         关键变量名
          pComponentName   应用构件名
          
**************************************************/
FT_Interface_API int FT_PublishKey(char *pKeybuff, char *KeyName, char* pComponentName);





/**************************************************

  函数名: FT_SendJudge
  
    函数功能: 向通信中间件返回的实现函数。告知通
    信中间件是否将当前应用构件的信息发
				布到网络中
                
                  返回值:返回1表示同意发布，否则返回-1,－301表示
                  此应用构件名之前没有注册过
                  参数 :  pComponentName   应用构件注册名
                  
**************************************************/
FT_Interface_API int FT_SendJudge(char *pComponentName);



/**************************************************

  函数名: FT_CloseServer
  函数功能: 当退出容错服务时，调用此函数，关闭所
  有任务，指针释放
  
    参数: pComponentName 应用构件注册名
    
**************************************************/
FT_Interface_API int FT_CloseServer(char* pComponentName);

