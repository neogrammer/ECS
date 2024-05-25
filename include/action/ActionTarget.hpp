#ifndef ACTIONTARGET_HPP__
#define ACTIONTARGET_HPP__

#include "ActionMap.hpp"

#include <functional> //function
#include <utility> //pair
#include <list> //list
#include <string>


 template<typename T = int>
    class ActionTarget
    {
        public:
            ActionTarget(const ActionTarget<T>&) = default;
            ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

            using FuncType = std::function<void(const sf::Event&)>;

            ActionTarget(const ActionMap<T>& map);

            bool processEvent(const sf::Event& event)const;
            void processEvents()const;

            void bind(const T& key,const FuncType& callback);
            void unbind(const T& key);

        private:
            std::list<std::pair<T,FuncType>> _eventsRealTime;
            std::list<std::pair<T,FuncType>> _eventsPoll;

            const ActionMap<T>& _actionMap;
    };


  


#include "tpl/ActionTarget.tpl"

#endif
