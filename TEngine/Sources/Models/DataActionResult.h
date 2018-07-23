#ifndef TENGINE_DATAACTIONRESULT_H
#define TENGINE_DATAACTIONRESULT_H

#include "memory"

#include "ActionResult.h"

namespace TEngine::Models
{
	template<class E, class D> class DataActionResult : public ActionResult<E> {
	public:
		DataActionResult(E error, std::shared_ptr<D> data) : 
			ActionResult<E>(error), 
			_data(data) {}

		std::shared_ptr<D> getData() {
			return _data;
		}
	private:
		std::shared_ptr<D> _data;
	};
}

#endif // TENGINE_DATAACTIONRESULT_H