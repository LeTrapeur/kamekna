//
// Created by tklempka on 24/04/18.
//

#ifndef FRK2D_PROJECT_CAPPLICATION_HPP
#define FRK2D_PROJECT_CAPPLICATION_HPP

#include <FRK2D/IApplication.hpp>

class CApplication : public IApplication
{
    public:
                            CApplication();
        virtual             ~CApplication()= default;
        virtual void        registerStates();
        virtual void        loadContent();
        virtual void        loadSettings();
};


#endif //FRK2D_PROJECT_CAPPLICATION_HPP
