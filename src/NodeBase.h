/*!
 * \class  NodeBase 
 * \brief  节点基类
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef NODEBASE_H_
#define NODEBASE_H_

#include <string>
#include <list>
#include <utility>
#include <vector>
#include "htmlcxx/ParserDom.h"
#include "Pretreat.h"

using std::string;
using namespace htmlcxx;

namespace arise
{
	class NodeBase
	{
	public:
		NodeBase():m_iCountOfChars(0){}
		~NodeBase(){}

		
		/*!
		 * \fn void Rpath(const tree<HTML::Node > &tDom);
		 * \brief  由迭代器求Rpath
		 * \param  [in]DOM树
		 * \param  [out]this->m_lRpath
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void Rpath(const tree<HTML::Node > &tDom);


		
		/*!
		 * \fn void Ipath(const tree<HTML::Node > &tDom);
		 * \brief  由迭代器求Ipath
		 * \param  [in]DOM树
		 * \param  [out]this->m_lIpath
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void Ipath(const tree<HTML::Node > &tDom);


		
		/*!
		 * \fn bool RpathIsEqual(const NodeBase &Other) const;
		 * \brief  判断节点的Rpath是否相同
		 * \param  [in]另一个NodeBase
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool RpathIsEqual(const NodeBase &Other) const;


		
		/*!
		 * \fn void CountNodeChars(const tree<HTML::Node > &tDom) ;
		 * \brief  统计节点字符数
		 * \param  [in]DOM树
		 * \param  [out]this->m_iCountOfChars
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void CountNodeChars(const tree<HTML::Node > &tDom) ;


		
		/*!
		 * \fn int ReadNodeChars() const;
		 * \brief  读取节点字符数，只读
		 * \param  void
		 * \return int，节点字符数
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		int ReadNodeChars() const;


		
		/*!
		 * \fn bool IpathIsEqual(const NodeBase &Other) const;
		 * \brief  判断节点的Ipath是否相同
		 * \param  [in]另一个节点
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool IpathIsEqual(const NodeBase &Other) const;

		
		
		/*!
		 * \fn const list< pair <string, int> > & ReadIpath() const;
		 * \brief  读取节点的Ipath，只读
		 * \param  void
		 * \return 节点Ipath的引用
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		const list< pair <string, int> > & ReadIpath() const;
		
		
		
		/*!
		 * \fn list <string> & ReadRpath();
		 * \brief  读取节点的Rpath,可修改
		 * \param  void
		 * \return 节点Rpath的引用
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		list <string> & ReadRpath();
		

		
		/*!
		 * \fn bool IsSon(const NodeBase &Other) const;
		 * \brief  判断该节点是否为另一个的孩子
		 * \param  [in]另一个节点
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool IsSon(const NodeBase &Other) const;


		
		/*!
		 * \fn bool operator== (const NodeBase &Other) const;
		 * \brief  重载==
		 * \param  [in]另一个节点
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool operator== (const NodeBase &Other) const;

		
		
		/*!
		 * \fn NodeBase & FindMinStruct(const tree<HTML::Node > &tDom,  NodeBase &Other);
		 * \brief  寻找两节点的最小公共结构体
		 * \param  [in]DOM树
		 * \param  [in]另一个节点
		 * \return 该节点的引用
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		NodeBase & FindMinStruct(const tree<HTML::Node > &tDom,  NodeBase &Other);
		
		
		
		/*!
		 * \fn void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//抽取同类网页时使用
		 * \brief  由Rpath确定迭代器
		 * \param  [in]DOM树
		 * \param  [out]具有该Rpath的迭代器向量
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		void RpathToIterator(const tree<HTML::Node> &tDom, vector<tree<HTML::Node>::iterator > &vecIters);//抽取同类网页时使用


		
		/*!
		 * \fn tree<HTML::Node>::iterator IpathToIterator(const tree<HTML::Node > &tDom);
		 * \brief  由Ipath确定迭代器（更新）
		 * \param  [in]DOM树
		 * \return 具有该Ipath的节点对应DOM树的迭代器
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		tree<HTML::Node>::iterator IpathToIterator(const tree<HTML::Node > &tDom);



		/*!
		 * \fn bool operator < (const NodeBase &Other) const;
		 * \brief  重载<
		 * \param  [in]另一个节点
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		bool operator < (const NodeBase &Other) const;


		tree<HTML::Node>::iterator m_tIter; /**< 节点在dom树中的迭代器*/


	protected:
	private:
		//tree<HTML::Node>::iterator m_tIter;
		list<string> m_lRpath; /*< Rpath*/
		list< pair <string, int> > m_lIpath; /**< Ipath*/
		int m_iCountOfChars; /**< 字符数*/
	
	};
}
#endif
