/*!
 * \file   FunTools.h 
 * \brief  ���ú���ͷ�ļ�
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
	 * \brief  ������Խ���ʱDOM���ڵ��е�ǰ��˿հף�like trim
	 * \param  [in]sText
	 * \param  [out]sText
	 * \return void
	 * \date   2011-06-01 
	 * \author nanjunxiao
	 */
	void EraseBlank(string &sText);


	
	/*!
	 * \fn void ReplaceSpecialSymbols(string &sText);
	 * \brief  �滻���Խ���ʱDOM���ڵ��е������ַ���Ŀǰֻ����&nbsp;
	 * \param  [in]sText
	 * \param  [out]sText
	 * \return void
	 * \date   2011-06-01 
	 * \author nanjunxiao
	 */
	void ReplaceSpecialSymbols(string &sText);
}
#endif