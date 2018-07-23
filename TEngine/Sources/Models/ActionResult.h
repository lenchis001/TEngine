#ifndef TENGINE_ACTIONRESULT_H
#define TENGINE_ACTIONRESULT_H

namespace TEngine::Models
{
    template<class E> class ActionResult {
        public:
            ActionResult(E error) : _error(error) {}

            E getError() const {
                return _error;
            }
        private:
            E _error;
    };
}

#endif // TENGINE_ACTIONRESULT_H