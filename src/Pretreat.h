/*!
 * \class  Pretreat 
 * \brief  预处理类
 * \date   2011-06-01 
 * \author nanjunxiao
 */ 


#ifndef PRETREAT_H_
#define PRETREAT_H_

#include "htmlcxx/ParserDom.h"
#include <string>

using namespace htmlcxx;
using namespace std;

namespace arise
{
	class Pretreat
	{
	public:
		
		/*!
		 * \fn static bool GenerateSubTree(const tree<HTML::Node> &tDom, const string &tagname, tree<HTML::Node> &tSubDom);
		 * \brief  生成子树
		 * \param  [in]DOM原树
		 * \param  [in]子树根节点的标签名
		 * \param  [out]DOM子树
		 * \return bool
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static bool GenerateSubTree(const tree<HTML::Node> &tDom, const string &tagname, tree<HTML::Node> &tSubDom);


		
		/*!
		 * \fn static void GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom);
		 * \brief  生成子树
		 * \param  [in]DOM原树
		 * \param  [in]子树根节点的迭代器
		 * \param  [out]DOM子树
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void GenerateSubTree(const tree<HTML::Node> &tDom, const tree<HTML::Node>::iterator &tIter, tree<HTML::Node> &tSubDom);


		
		/*!
		 * \fn static void CleanUpFormTag(tree<HTML::Node> &m_TagTree);
		 * \brief  剪枝，去除scrip等无用节点
		 * \param  [in]DOM树
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void CleanUpFormTag(tree<HTML::Node> &m_TagTree);



		
		/*!
		 * \fn static int TidyHtml(const char *pcSourcePage, string &sDestPage);
		 * \brief  修补丢失、错误标签
		 * \param  [in]待修补网页字符串
		 * \param  [out]修补后的网页string
		 * \return 结果码，==0修补正确，<0修补失败
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static int TidyHtml(const char *pcSourcePage, string &sDestPage);



		
		/*!
		 * \fn static void ReadOnePage(const string &path,string &html);
		 * \brief  读取本地磁盘上的文件
		 * \param  [in]文件存储路径
		 * \param  [out]文件内容string
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void ReadOnePage(const string &path,string &html);
		//static void TagNameToLower(tree<HTML::Node> &tDom);


		
		/*!
		 * \fn static void EraseBaiduAD(string &sContent);
		 * \brief  针对百度，去除百度推广链接（右面）
		 * \param  [in]网页string
		 * \param  [out]网页string
		 * \return void
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static void EraseBaiduAD(string &sContent);


		
		/*!
		 * \fn static string SubStringBody(string &sContent);
		 * \brief  字符串处理截取body字串,备注	：无法处理大小写问题，效率相比子树也没快多少
		 * \param  [in]网页string
		 * \return body字串
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		static string SubStringBody(string &sContent);
	};
}
#endif