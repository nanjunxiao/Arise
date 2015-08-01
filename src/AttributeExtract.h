/*!
 * \class  AttributeExtract 
 * \brief  Ԫ���Գ�ȡ��
 * \date   2011-06-01 
 * \author nanjunxiao
 */ 


#ifndef ATTRIBUTEEXTRACT_H_
#define ATTRIBUTEEXTRACT_H_

#include "htmlcxx/ParserDom.h"
#include "NodeBase.h"
#include "Interface.h"
#include <vector>
//#include <fstream>

using namespace htmlcxx;
namespace arise
{
	class AttributeExtract
	{
	public:
		/*!
		 * \fn void ParseAttributes(const tree<HTML::Node> &tDom, const NodeBase &nodeInfoStruct ,vector<_stMetaSearchResult> &vstResult);
		 * \brief  ������Ϣ�ṹ����������
		 * \param  [in]DOM��
		 * \param  [in]��Ϣ�ṹ��ڵ�
		 * \param  [out]Interface�еĽṹ������
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void ParseAttributes(const tree<HTML::Node> &tDom, const NodeBase &nodeInfoStruct ,vector<_stMetaSearchResult> &vstResult);


	private:
		//vector<_stMetaSearchResult> m_OnePageAttributes; //�����ģ��������Ҫ�����Էŵ�����
		
	};
}
#endif