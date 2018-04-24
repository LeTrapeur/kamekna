//
// Created by tklempka on 24/04/18.
//

#ifndef FRK2D_PROJECT_CAPPLICATION_HPP
#define FRK2D_PROJECT_CAPPLICATION_HPP

#include <FRK2D/Application.hpp>

class CApplication : public Application
{
    public:
                            CApplication();
        virtual             ~CApplication()= default;
        virtual void        registerStates();
        virtual void        loadContent();
        virtual void        loadSettings();
};


#endif //FRK2D_PROJECT_CAPPLICATION_HPP
