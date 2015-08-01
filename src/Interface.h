/*!
 * \file   Interface.h 
 * \brief  元搜索抽取接口
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <string>
#include <vector>

using namespace std;


/**
 arise_E_OK = 0											    抽取OK 
 arise_E_ExtractMetaSearchResult_InputIsNull = -1			ExtractMetaSearchResult输入页面为空
 arise_E_TidyHtml_Failed = -2								ExtractMetaSearchResult TidyHtml失败
 arise_E_GenerateSubTree_Failed = -3						Pretreat::GenerateSubTree(string)可能没有找到body标签
 arise_E_ExtractMetaSearchResult_Exception = -4				ExtractMetaSearchResult异常类
 arise_E_ExtractMetaSearchResult_UnknownError = -5			ExtractMetaSearchResult未知异常
 arise_E_InfoStructIsEmpty = -6								ExtractWithoutWrapper::ExtractRecords信息结构体为空
 arise_E_OnePageAttIsBlank = -7								ExtractWithoutWrapper::ExtractRecords一个网页抽取属性为空
 arise_E_GroupInputIsEmpty = -8								ExtractBase::Group 输入lAllLinks为空
 arise_E_RegionStructNull = -9								ExtractBase::RegionStruct没有大于页面字数一半的，作为区域结构体
 arise_E_vvLinkGroupsIsEmpth = -10							ExtractBase::RegionStruct  vvLinkGroups为空
 arise_E_ReadFileFailed = 11								读取文件失败
 arise_E_WithWrapperInfoStructIsEmpty = -12					ExtractWithWrapper::ExtractRecords 信息结构体为空
 arise_E_WrireFileFailed = -13								ExtractWrapper::GenerateWrapper写文件失败
 arise_E_SubStringBody_Failed = -14							Pretreat::SubStringBody查找body标签失败
*/

/**< 错误代码 */
typedef enum
{
	arise_E_OK                                   = 0,
	arise_E_ExtractMetaSearchResult_InputIsNull  = -1,
	arise_E_TidyHtml_Failed						 = -2,
	arise_E_GenerateSubTree_Failed				 = -3,
	arise_E_ExtractMetaSearchResult_Exception    = -4,
	arise_E_ExtractMetaSearchResult_UnknownError = -5,
	arise_E_InfoStructIsEmpty				     = -6,
	arise_E_OnePageAttIsBlank					 = -7,
	arise_E_GroupInputIsEmpty					 = -8,
	arise_E_RegionStructNull					 = -9,
	arise_E_vvLinkGroupsIsEmpty					 = -10,
	arise_E_ReadFileFailed						 = -11,
	arise_E_WithWrapperInfoStructIsEmpty         = -12,
	arise_E_WrireFileFailed						 = -13,
	arise_E_SubStringBody_Failed				 = -14

}arise_ErrorCode;



/**< 元信息结构体*/
typedef struct _stMetaSearchResult{  /**< 元搜索检索页抽取结果数据结构（先实现前三项）*/
	string title;
	string url;
	string snippet;
	string pubtime;
	string domain;
	string sitename;
	_stMetaSearchResult(){
		title = "";
		url = "";
		snippet = "";
		pubtime = "";
		domain = "";
		sitename = "";
	}
}_stMetaSearchResult, *_pstMetaSearchResult;



/*!
 * \fn arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult);
 * \brief  元搜索抽取接口函数
 * \param  [in]待抽取网页存储字符串
 * \param  [in]是否用htmltidy修复标签
 * \param  [out]抽取结果元信息向量
 * \return 自定义错误码，定位错误位置：==0抽取正确，<0抽取失败
 * \date   2011-06-01 
 * \author nanjunxiao
 */
arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult);

#endif