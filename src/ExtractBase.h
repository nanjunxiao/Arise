/*!
 * \class  ExtractBase 
 * \brief  抽取基类
 * \date   2011-06-01
 * \author nanjunxiao 
*/ 


#ifndef EXTRACTBASE_H_
#define EXTRACTBASE_H_

#include "htmlcxx/ParserDom.h"
#include "NodeBase.h"
#include <vector>
#include "Interface.h"
using namespace htmlcxx;
namespace arise
{
	class ExtractBase
	{
	public:
		ExtractBase(){}


		virtual ~ExtractBase(){}


		/*!
		 * \fn arise_ErrorCode Extract(const tree<HTML::Node> &tDom);
		 * \brief  抽取基类主函数，一直抽取到信息结构体
		 * \param  [in]DOM树
		 * \return 自定义返回码
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode Extract(const tree<HTML::Node> &tDom);


	
		/*!
		 * \fn void WriteWrapper(const tree<HTML::Node> &tDom, ofstream &ofs);
		 * \brief  将标准链接组、信息结构体Rpath写入wrapper
		 * \param  [in]DOM树
		 * \param  [out]输出文件流
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void WriteWrapper(const tree<HTML::Node> &tDom, ofstream &ofs);
		
	protected:
		
		/*!
		 * \fn const vector<NodeBase> & ReadInfoStruct(void) const;
		 * \brief  读取信息结构体，只读
		 * \param  void
		 * \return 信息结构体引用
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		const vector<NodeBase> & ReadInfoStruct(void) const;





		/*!
		 * \fn void IdentifyInfoStruct(const tree<HTML::Node> &tDom);
		 * \brief  由标准链接组确定信息结构体
		 * \param  [in]DOM树
		 * \param  [out]this->m_vInfoStruct
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void IdentifyInfoStruct(const tree<HTML::Node> &tDom);



		/*!
		 * \fn void FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks);
		 * \brief  遍历查找DOM树中的所有链接
		 * \param  [in]DOM树
		 * \param  [out]this->m_lAllLinks
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void FindAllLinks(const tree<HTML::Node> &tDom, list<NodeBase> &lAllLinks);



		/*!
		 * \fn arise_ErrorCode Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups);
		 * \brief  所有链接分组，Rpath相同分为一组
		 * \param  [in]所有链接
		 * \param  [out]链接组
		 * \return 自定义返回码
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode Group(list<NodeBase> lAllLinks, vector<vector<NodeBase> > &vvLinkGroups);




		/*!
		 * \fn void IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
									  const vector<vector<NodeBase> > &vvLinkGroups,
									  const vector<NodeBase> &vMinStructs,
									  vector<NodeBase> &vOrderedLinks);
		 * \brief  识别有序链接组
		 * \param  [in]DOM树
		 * \param  [in]链接组
		 * \param  [in]每个链接组元素的最小父结构
		 * \param  [out]有序链接组
		 * \return void
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		void IdentifyOrderedLinkGroup(const tree<HTML::Node> &tDom, 
									  const vector<vector<NodeBase> > &vvLinkGroups,
									  const vector<NodeBase> &vMinStructs,
									  vector<NodeBase> &vOrderedLinks);




		
		/*!
		 * \fn arise_ErrorCode RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs);
		 * \brief  寻找区域结构体
		 * \param  [in]DOM树
		 * \param  [in]链接组
		 * \param  [out]区域结构体
		 * \param  [out]每个链接组元素的最小父结构
		 * \return 自定义返回码
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		arise_ErrorCode RegionStruct(const tree<HTML::Node> &tDom, vector<vector<NodeBase> > &vvLinkGroups, arise::NodeBase &nodeRegionStruct ,vector <NodeBase> &vMinStructs);



		/*!
		 * \fn int CountPageChars(const tree<HTML::Node> &tDom);
		 * \brief  统计网页字符数
		 * \param  [in]DOM树
		 * \return int
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		int CountPageChars(const tree<HTML::Node> &tDom);

	private:
		/*!
		 * \fn NodeBase MaxFather(const tree<HTML::Node> &tDom, const NodeBase &SeparatedResult, const NodeBase &SeparatedRoot) const;
		 * \brief  结构体分离结果相对于分离根节点的最大父节点
		 * \param  [in]DOM树
		 * \param  [in]结构体分离算法分离结果
		 * \param  [in]分离根节点：区域结构体/主结构体
		 * \return 最大父节点
		 * \date   2011-06-01
		 * \author nanjunxiao
		 */
		NodeBase MaxFather(const tree<HTML::Node> &tDom, const NodeBase &SeparatedResult, const NodeBase &SeparatedRoot) const;


		list<NodeBase> m_lAllLinks;/**< 所有链接*/
		vector< vector<NodeBase> > m_vvLinkGroups;/**< 所有链接分组后的结果*/
		NodeBase m_RegionStruct;/**< 区域接构体，用NodeBase存储*/

		vector<NodeBase> m_vOrderedLinks;/**< 有序连接组*/

		vector<NodeBase> m_vInfoStruct;/**< 信息结构体集合*/

	};
}
#endif
