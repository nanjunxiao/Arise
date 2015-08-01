/*!
 * \class  ExtractWithoutWrapper 
 * \brief  抽取基类派生类，不用wrapper抽取类
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
		 * \brief  withoutwrapper抽取记录属性
		 * \param  [in]DOM树
		 * \param  [out]全局元信息结构体向量
		 * \return 自定义返回码：==arise_E_OK抽取OK，<0抽取失败
		 * \date   2011-06-01 
		 * \author nanjunxiao
		 */
		arise_ErrorCode ExtractRecords(const tree<HTML::Node> &tBodyDom, vector<_stMetaSearchResult> &vstResult);
	protected:
	private:
	};
}
#endif