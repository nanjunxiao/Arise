/*!
 * \class  AttributeExtract 
 * \brief  元属性抽取类
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
		 * \brief  解析信息结构体三个属性
		 * \param  [in]DOM树
		 * \param  [in]信息结构体节点
		 * \param  [out]Interface中的结构体向量
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void ParseAttributes(const tree<HTML::Node> &tDom, const NodeBase &nodeInfoStruct ,vector<_stMetaSearchResult> &vstResult);


	private:
		//vector<_stMetaSearchResult> m_OnePageAttributes; //递增的，如后续需要，可以放到类外
		
	};
}
#endif