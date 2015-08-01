/*!
 * \class  ExtractWithoutWrapper 
 * \brief  ��ȡ���������࣬����wrapper��ȡ��
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef EXTRACTWITHOUTWRAPPER_H_
#define EXTRACTWITHOUTWRAPPER_H_

#include "ExtractBase.h"
#include "Interface.h"
namespace arise
{
	class ExtractWithoutWrapper : public ExtractBase
	{
	public:
		ExtractWithoutWrapper():ExtractBase(){}



		~ExtractWithoutWrapper(){}



		/*!
		 * \fn arise_ErrorCode ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult);
		 * \brief  withoutwrapper��ȡ��¼����
		 * \param  [in]DOM��
		 * \param  [out]ȫ��Ԫ��Ϣ�ṹ������
		 * \return �Զ��巵���룺==arise_E_OK��ȡOK��<0��ȡʧ��
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		arise_ErrorCode ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult);
	protected:
	private:
	};
}
#endif