#pragma once

#include "Envelope.Math.Consts.h"
#include "Envelope.Core.Consts.h"

#include "ModelParameters.h"
#include "CalculationParameters.h"
#include "SkirtData.h"
#include "LandscapeData.h"

#include "Envelope.Math.h"

#include "TpUtils.h"
#include "InOut.h"



#include "FiveNodePattern.h"

#include "Summary.h"

#include "Forces.h"

using namespace alglib;
using namespace EnvelopeMath;
using namespace std;

namespace EnvelopeCore {

	/**
	* @class	ModelProvider
	*
	* @brief	Предоставляет сервисные функции, необходимые для моделирования, например начальное распределение и т.д.
	*
	* @author	Vasiliy
	* @date	18.10.2012
	*/

	class DllExport ModelProvider
	{
	private:

		/**
		* @fn	ModelProvider::void (*callbackFunc)(ModelProvider *sender, Summary &s);
		*
		* @brief	Callback function to output summary information.
		*
		* @author	Vs
		* @date	03.04.2013
		*
		* @param [in,out]	sender	If non-null, the sender.
		* @param [in,out]	s	  	The Summary &amp; to process.
		*/

		void (*callbackFunc)(ModelProvider *sender, Summary &s);

		/**
		* @brief	Сумма длин ребер в состоянии покоя.
		*/

		double initTotalEdge;

		/**
		* @brief	The null vector.
		*/

		const TVector nullVector;

		/**
		* @brief	Options for controlling the model.
		*/

		ModelParameters modelParameters;

		/**
		* @brief	Options for controlling the calculation.
		*/

		CalculationParameters calculationParameters;

		/**
		* @brief	Промежуточная информация о состоянии юбки.
		* 			Необходима для хранения предыдущего состояния
		*/

		SkirtData * tempSkirtData;

		/**
		* @brief	Информация о недеформированной юбке.
		*/

		SkirtData * restSkirtData;

		/**
		* @brief	Информация о состоянии юбки на позапрошлом шаге интегрирования.
		*/

		SkirtData * prevSkirtData;

		/**
		* @brief	Information describing the landscape.
		*/

		LandscapeData * landscapeData;

		/**
		* Матрица поворота
		*/

		alglib::real_2d_array M; 

		/**
		* @brief Вектор смещения ДСК оболочки относительно ДСК ландшафта.
		*/

		alglib::real_1d_array s; 

		/**
		* @brief	Вектор ускорения свободного падения.
		*/

		TVector g;



#pragma region Заглушки
		/**
		* @fn	bool static ModelProvider::InitializeLandscapeDummy(LandscapeData *landscapeData);
		*
		* @brief	Initializes the landscape dummy.
		*
		* @author	Vasiliy
		* @date	23.11.2012
		*
		* @param [in,out]	landscapeData	If non-null, information describing the landscape.
		*
		* @return	true if it succeeds, false if it fails.
		*/

		bool static InitializeLandscapeDummy(LandscapeData *landscapeData);



		double static GetInternalPressureDummy( double t );


		void static GetSkirtBasisPlacementDummy(double t, TPoint &centre, double &alpha, double &beta, double &gamma );

		/**
		* @fn	double static ModelProvider::GetHeightDummy(double x, double y);
		*
		* @brief	Задает высоту по координатам. 
		* 			Метод используется для тестирования.
		*
		* @author	Vasiliy
		* @date	23.11.2012
		*
		* @param	x	The x coordinate.
		* @param	y	The y coordinate.
		*
		* @return	The height dummy.
		*/

		double static GetHeightDummy(double x, double y);  
#pragma endregion

		/**
		* @fn	void ModelProvider::setCallbackFunc(void (*func)(ModelProvider *sender, Summary &s));
		*
		* @brief	Sets callback function.
		*
		* @author	Vs
		* @date	31.05.2013
		*
		* @param [in,out]	func	If non-null, the function.
		*/

		void SetCallbackFunc(void (*func)(ModelProvider *sender, Summary &s));

		/**
		* @fn	void ModelProvider::SetUnstressedState( SkirtData * skirtData);
		*
		* @brief	Устанавливает состояние без напряжения.
		*
		* @author	Vasiliy
		* @date	20.10.2012
		*
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*/

		void SetUnstressedState( SkirtData * skirtData);

		/**
		* @fn	void ModelProvider::SetNeighbourhoodData( SkirtData * skirtData) const;
		*
		* @brief	Устанавливает данные, зависящие от соседей.
		*
		* @author	Vs
		* @date	25.02.2013
		*
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*/

		void SetNeighbourhoodData( SkirtData * skirtData) const;

		/**
		* @fn	void ModelProvider::SetBoundaryConditions(SkirtData * skirtData) const;
		*
		* @brief	Sets boundary conditions.
		*
		* @author	Vs
		* @date	31.05.2013
		*
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*/

		void SetBoundaryConditions(SkirtData * skirtData) const;

		/**
		* @fn	bool static ModelProvider::InitializeLandscape(LandscapeData * landscapeData)
		*
		* @brief	Инициализирует ландшафт.
		*
		* @author	Vasiliy
		* @date	23.11.2012
		*
		* @param [in,out]	landscapeData	If non-null, information describing the landscape.
		*
		* @return	true if it succeeds, false if it fails.
		*/

		bool static InitializeLandscape(LandscapeData * landscapeData);

		/**
		* @fn void ModelProvider::UpdateTransformationData(const TPoint & centre,
		* const double &a, const double & b, const double & g)
		*
		* @brief Updates the transformation data.
		*
		* @author Vasily Salosyatov
		* @date 06.12.2012
		*
		* @param centre
		* The centre.
		* @param a
		* Угол Эйлера.
		* @param b
		* Угол Эйлера.
		* @param g
		* Угол Эйлера.
		*
		* @return .
		*/

		void UpdateTransformationData(const TPoint & centre, const double &a, const double & b, const double & g);

#pragma region Вычисления

		/**
		* @fn TVector ModelProvider::CalculateGravitation() const;
		*
		* @brief	Рассчитывает гравитационную составляющую силы.
		*
		* @author	Vasiliy
		* @date	21.11.2012
		*

		* @return	The calculated gravitation.
		*/

		TVector CalculateGravitation() const;



		/**
		* @fn TVector ModelProvider::CalculatePressure(const Node & n_cur, const TVector & normal,
		* const double & p ) const;
		*
		* @brief Рассчитывает силу давления.
		*
		* @author Vasily Salosyatov
		* @date 06.12.2012
		*
		* @param n_cur
		* The current.
		* @param normal
		* The normal.
		* @param p
		* Давление.
		*
		* @return The calculated pressure.
		*/

		TVector CalculatePressure(const Node & n_cur, const TVector & normal,  const double & p ) const;

		/**
		* @fn	TVector ModelProvider :: ModelProvider::CalculateFriction(const Node & n_cur_rest,
		* 		const Node & n_cur, const TVector & normal, const double & p, const double & mu ) const;
		*
		* @brief	Рассчитывает силу трения.
		*
		* @author	Vasily Salosyatov
		* @date	06.12.2012
		*
		* @param	n_cur_rest	The rest current.
		* @param	n_cur	  	Текущий узел.
		* @param	normal	  	Нормаль.
		* @param	p		  	Давление.
		* @param	mu		  	Коэффициент трения.
		*
		* @return	The calculated friction.
		*/

		TVector ModelProvider :: CalculateFriction(const Node & n_cur_rest, const Node & n_cur, const TVector & normal, const double & p, const double & mu  ) const;

		/**
		* @fn void ModelProvider::ProcessPenetration(SkirtData * skirtData);
		*
		* @brief Обработка случая проникновения сквозь ландшафт.
		*
		* @author Vasily Salosyatov
		* @date 07.12.2012
		*
		* @param [in,out] skirtData
		* If non-null, information describing the skirt.
		*/

		void ProcessPenetration(SkirtData * skirtData);

#pragma endregion


		int ModelProvider :: Transform(TransformDirection dir, TPoint & skirtPoint, TPoint & landscapePoint) const;

		/**
		* @fn	bool ModelProvider :: ModelProvider::TransformSkirtDataToLandscape(SkirtData * skirtData);
		*
		* @brief	Преобразовывает данные оболочки в системе ландшафта .
		*
		* @author	Vs
		* @date	12.03.2013
		*
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*
		* @return	.
		*/

		bool ModelProvider :: TransformSkirtDataToLandscape(SkirtData * skirtData);

		/**
		* @fn bool ModelProvider::IsNodeOverLandscape(const TPoint & p) const;
		*
		* @brief Query if 'p' is node over landscape.
		*
		* @author Vasily Salosyatov
		* @date 21.01.2013
		*
		* @param p
		* The const TPoint &amp; to process.
		*
		* @return true if node over landscape, false if not.
		*/

		bool IsNodeOverLandscape(const TPoint & p) const;

		/**
		* @fn void ModelProvider::MoveToLandscape(TPoint & p);
		*
		* @brief Передвигает точку под ландшафтом на ландшафт.
		*
		* @author Vasily Salosyatov
		* @date 21.01.2013
		*
		* @param [in,out] p
		* Передвигаемая точка.
		*/

		void MoveToLandscape(TPoint & p);



		/**
		* @fn	void ModelProvider :: ModelProvider::OutputModelToTecplot(double t, SkirtData * skirtData,
		* 		bool outputLandscapeToTecplot) const;
		*
		* @brief	Выводит массив узлов и ландшафт в tecplot файл. НАзвание формируется автоматически и
		* 			имеет метку времени.
		*
		* @author	Vs
		* @date	26.03.2013
		*
		* @param	t							The double to process.
		* @param [in,out]	skirtData			If non-null, information describing the skirt.
		* @param	outputLandscapeToTecplot	true to output landscape to tecplot.
		*
		* @return	.
		*/

		void ModelProvider :: OutputModelToTecplot(double t, SkirtData * skirtData, bool outputLandscapeToTecplot) const;

		/**
		* @fn	void ModelProvider :: ModelProvider::PreCalculate(SkirtData * skirtData) const;
		*
		* @brief	Предварительные вычисления промежуточных величин.
		*
		* @author	Vs
		* @date	15.06.2013
		*
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*
		* @return	.
		*/

		void  ModelProvider :: PreCalculate(SkirtData * skirtData) const;

				/**
		* @fn	bool ModelProvider::InitStep(double t, SkirtData * skirtData);
		*
		* @brief	Устанавливает значения на начале временного шага.
		*
		* @author	Vasiliy
		* @date	20.10.2012
		*
		* @param	t				 	Время.
		* @param [in,out]	skirtData	Данные, описывающие оболочку.
		*
		* @return	Определяет, необходим ли дальнейший расчет.
		*/

		bool InitStep(double t, SkirtData * skirtData);

		/**
		* @fn	bool ModelProvider::FinishStep(SkirtData * skirtData);
		*
		* @brief	Обрабатывает конец временного шага. Сохраняет конечное состояние для расчета
		* 			следующего шага.
		*
		* @author	Vs
		* @date	05.03.2013
		*
		* @param [in,out]	skirtData	Данные, описывающие оболочку.
		*
		* @return	true if it succeeds, false if it fails.
		*
		*/

		bool FinishStep(SkirtData * skirtData);

		
		/**
		* @fn	void ModelProvider::Output(double t, SkirtData * skirtData);
		*
		* @brief	Выводит рассчитанную информацию, сохраняя промежуточные значения.
		*
		* @author	Vasiliy
		* @date	20.10.2012
		*
		* @param	t				 	The double to process.
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*/

		Summary Output(double t, SkirtData * skirtData);

		/**
		* @fn	void ModelProvider::Calculate(double t, double & t_out, double & dt,
		* 		SkirtData * skirtData);
		*
		* @brief	Выполняет основные вычисления.
		*
		* @author	Vasiliy
		* @date	20.11.2012
		*
		* @param	t				 	Время в начале шага интегрирования.
		* @param [in,out]	t_out	 	Время в конце шага интегрирования.
		* @param	dt				 	Шаг интегрирования.
		* @param [in,out]	skirtData	If non-null, information describing the skirt.
		*/

		void Calculate(double t, double & t_out, double & dt, SkirtData * skirtData);

		/**
		* @fn	void ModelProvider::InitializeModel(CalculationParameters calculationParameters,
		* 		ModelParameters modelParameters);
		*
		* @brief	Initializes the model.
		*
		* @author	Vasiliy
		* @date	23.11.2012
		*
		* @param	calculationParameters	Options for controlling the calculation.
		* @param	modelParameters		 	Options for controlling the model.
		*/



		void InitializeModel(CalculationParameters calculationParameters, ModelParameters modelParameters);

		/**
		 * @fn	virtual int ModelProvider::CalculateBySolver(double t, double & t_out, double & dt,
		 * 		SkirtData * skirtData);
		 *
		 * @brief	Calculates by solver.
		 *
		 * @author	Vs
		 * @date	03.06.2013
		 *
		 * @param	t				 	The double to process.
		 * @param [in,out]	t_out	 	The out.
		 * @param	dt				 	The dt.
		 * @param [in,out]	skirtData	If non-null, information describing the skirt.
		 *
		 * @return	The calculated by internal solver.
		 */

		virtual int  CalculateBySolver(double t, double & t_out, double & dt, SkirtData * skirtData);
	public:



		/**
		* @fn	double static ModelProvider::GetInternalPressure( double t );
		*
		* @brief	Получает внутреннее давление в конусе в момент времени t.
		*
		* @author	Vasiliy
		* @date	20.11.2012
		*
		* @param	t	The double to process.
		*
		* @return	The internal pressure.
		*/

		double static GetInternalPressure( double t );

		/**
		* @fn	double static ModelProvider::CalcHeight(double x, double y);
		*
		* @brief	Вычисляет  высоту в точке (x, y).
		* 			Как правило, для этого необходима интерполяция.
		*
		* @author	Vasiliy
		* @date	23.11.2012
		*
		* @param	x	The x coordinate.
		* @param	y	The y coordinate.
		*
		* @return	The calculated height.
		*/

		double static CalcHeight(double x, double y);

		/**
		* @fn	void static ModelProvider::GetSkirtBasisPlacement(double t, TPoint centre, double alpha,
		* 		double beta, double gamma );
		*
		* @brief	Определяет положение юбки - координаты центра основания и ориентацию через углы Эйлера.
		*
		* @author	Vasiliy
		* @date	21.11.2012
		*
		* @param	t	  	Время.
		* @param	centre	Центр основания конуса (относительно СК, связанной с ландшафтом).
		* @param	alpha 	Угол прецессии.
		* @param	beta  	Угол нутации.
		* @param	gamma 	Угол собственного вращения.
		*/

		void static GetSkirtBasisPlacement(double t, TPoint &centre, double &alpha, double &beta, double &gamma );


		/**
		 * @fn	double ModelProvider::CalcDt();
		 *
		 * @brief	Рассчитывает шаг по времени.
		 *
		 * @author	Vasily Salosyatov
		 * @date	06.12.2012
		 *
		 * @return	The calculated dt.
		 */

		double CalcDt();

		void ModelProvider :: Start(void (*func)(ModelProvider *sender, Summary &s) = NULL);

		ModelProvider(void);
		ModelProvider(CalculationParameters calculationParameters, ModelParameters modelParameters);
		~ModelProvider(void);
	};
}
