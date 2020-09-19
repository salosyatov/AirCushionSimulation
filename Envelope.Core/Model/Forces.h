#pragma once

#include "utils.h"
#include "BigPointPattern.h"
#include "FivePointPattern.h"
#include "FiveNodePattern.h"


namespace EnvelopeCore {

		/**
		 * @fn	void CalculateFlexural(const Node & n_rest_cur, const PointPattern & pattern,
		 * 		const double & kb_hor, const double & kb_ver, TVector & f_cur, TVector & f_l,
		 * 		TVector & f_r, TVector & f_b, TVector & f_t );
		 *
		 * @brief	Рассчитывает силу упругости изгиба.
		 *
		 * @author	Vasily Salosyatov
		 * @date	06.12.2012
		 *
		 * @param	n_rest_cur   	The rest current.
		 * @param	pattern		 	Точечный шаблон.
		 * @param	kb_hor		 	.
		 * @param	kb_ver		 	.
		 * @param [in,out]	f_cur	The current.
		 * @param [in,out]	f_l  	The.
		 * @param [in,out]	f_r  	The.
		 * @param [in,out]	f_b  	The.
		 * @param [in,out]	f_t  	The.
		 *
		 * ### param	nodePattern	A pattern specifying the node.
		 * ### return	Сила упругости изгиба.
		 */

		void CalculateFlexural(const Node & n_rest_cur, const PointPattern & pattern, const double & kb_hor, const double & kb_ver, TVector & f_cur, TVector & f_l, TVector & f_r, TVector & f_b, TVector & f_t ) ;
}
