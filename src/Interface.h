/*!
 * \file   Interface.h 
 * \brief  Ԫ������ȡ�ӿ�
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <string>
#include <vector>

using namespace std;


/**
 arise_E_OK = 0											    ��ȡOK 
 arise_E_ExtractMetaSearchResult_InputIsNull = -1			ExtractMetaSearchResult����ҳ��Ϊ��
 arise_E_TidyHtml_Failed = -2								ExtractMetaSearchResult TidyHtmlʧ��
 arise_E_GenerateSubTree_Failed = -3						Pretreat::GenerateSubTree(string)����û���ҵ�body��ǩ
 arise_E_ExtractMetaSearchResult_Exception = -4				ExtractMetaSearchResult�쳣��
 arise_E_ExtractMetaSearchResult_UnknownError = -5			ExtractMetaSearchResultδ֪�쳣
 arise_E_InfoStructIsEmpty = -6								ExtractWithoutWrapper::ExtractRecords��Ϣ�ṹ��Ϊ��
 arise_E_OnePageAttIsBlank = -7								ExtractWithoutWrapper::ExtractRecordsһ����ҳ��ȡ����Ϊ��
 arise_E_GroupInputIsEmpty = -8								ExtractBase::Group ����lAllLinksΪ��
 arise_E_RegionStructNull = -9								ExtractBase::RegionStructû�д���ҳ������һ��ģ���Ϊ����ṹ��
 arise_E_vvLinkGroupsIsEmpth = -10							ExtractBase::RegionStruct  vvLinkGroupsΪ��
 arise_E_ReadFileFailed = 11								��ȡ�ļ�ʧ��
 arise_E_WithWrapperInfoStructIsEmpty = -12					ExtractWithWrapper::ExtractRecords ��Ϣ�ṹ��Ϊ��
 arise_E_WrireFileFailed = -13								ExtractWrapper::GenerateWrapperд�ļ�ʧ��
 arise_E_SubStringBody_Failed = -14							Pretreat::SubStringBody����body��ǩʧ��
*/

/**< ������� */
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



/**< Ԫ��Ϣ�ṹ��*/
typedef struct _stMetaSearchResult{  /**< Ԫ��������ҳ��ȡ������ݽṹ����ʵ��ǰ���*/
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
 * \brief  Ԫ������ȡ�ӿں���
 * \param  [in]����ȡ��ҳ�洢�ַ���
 * \param  [in]�Ƿ���htmltidy�޸���ǩ
 * \param  [out]��ȡ���Ԫ��Ϣ����
 * \return �Զ�������룬��λ����λ�ã�==0��ȡ��ȷ��<0��ȡʧ��
 * \date   2011-06-01 
 * \author nanjunxiao
 */
arise_ErrorCode ExtractMetaSearchResult(const char *pcContent, bool bTidyNeeded, vector<_stMetaSearchResult> &vstResult);

#endif