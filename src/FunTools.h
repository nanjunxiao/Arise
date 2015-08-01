/*!
 * \file   FunTools.h 
 * \brief  公用函数头文件
 * \date   2011-06-01 
 * \author nanjunxiao
*/ 


#ifndef FUNTOOLS_H_
#define FUNTOOLS_H_

#include <string>
using std::string;
namespace arise
{
	
	/*!
	 * \fn void EraseBlank(string &sText);
	 * \brief  清除属性解析时DOM树节点中的前后端空白，like trim
	 * \param  [in]sText
	 * \param  [out]sText
	 * \return void
	 * \date   2011-06-01 
	 * \author nanjunxiao
	 */
	void EraseBlank(string &sText);


	
	/*!
	 * \fn void ReplaceSpecialSymbols(string &sText);
	 * \brief  替换属性解析时DOM树节点中的特殊字符，目前只处理&nbsp;
	 * \param  [in]sText
	 * \param  [out]sText
	 * \return void
	 * \date   2011-06-01 
	 * \author nanjunxiao
	 */
	void ReplaceSpecialSymbols(string &sText);
}
#endif