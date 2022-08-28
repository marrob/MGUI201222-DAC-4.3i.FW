/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDHEAPBASE_HPP
#define FRONTENDHEAPBASE_HPP

#include <common/Meta.hpp>
#include <common/Partition.hpp>
#include <mvp/MVPHeap.hpp>

#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <touchgfx/transitions/WipeTransition.hpp>

#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>

#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/offscreen_screen/OffScreenView.hpp>
#include <gui/offscreen_screen/OffScreenPresenter.hpp>
#include <gui/settingsscreen_screen/SettingsScreenView.hpp>
#include <gui/settingsscreen_screen/SettingsScreenPresenter.hpp>
#include <gui/displayscreen_screen/DisplayScreenView.hpp>
#include <gui/displayscreen_screen/DisplayScreenPresenter.hpp>
#include <gui/servicescreen_screen/ServiceScreenView.hpp>
#include <gui/servicescreen_screen/ServiceScreenPresenter.hpp>
#include <gui/passwordscreen_screen/PasswordScreenView.hpp>
#include <gui/passwordscreen_screen/PasswordScreenPresenter.hpp>
#include <gui/clockscreen_screen/ClockScreenView.hpp>
#include <gui/clockscreen_screen/ClockScreenPresenter.hpp>
#include <gui/logscreen_screen/LogScreenView.hpp>
#include <gui/logscreen_screen/LogScreenPresenter.hpp>
#include <gui/splashscreen_screen/SplashScreenView.hpp>
#include <gui/splashscreen_screen/SplashScreenPresenter.hpp>
#include <gui/saverscreen_screen/SaverScreenView.hpp>
#include <gui/saverscreen_screen/SaverScreenPresenter.hpp>
#include <gui/debugscreen_screen/DebugScreenView.hpp>
#include <gui/debugscreen_screen/DebugScreenPresenter.hpp>


/**
 * This class provides the memory that shall be used for memory allocations
 * in the frontend. A single instance of the FrontendHeap is allocated once (in heap
 * memory), and all other frontend objects such as views, presenters and data model are
 * allocated within the scope of this FrontendHeap. As such, the RAM usage of the entire
 * user interface is sizeof(FrontendHeap).
 *
 * @note The FrontendHeap reserves memory for the most memory-consuming presenter and
 * view only. The largest of these classes are determined at compile-time using template
 * magic. As such, it is important to add all presenters, views and transitions to the
 * type lists in this class.
 *
 */
class FrontendHeapBase : public touchgfx::MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< MainView,
            touchgfx::meta::TypeList< OffScreenView,
            touchgfx::meta::TypeList< SettingsScreenView,
            touchgfx::meta::TypeList< DisplayScreenView,
            touchgfx::meta::TypeList< ServiceScreenView,
            touchgfx::meta::TypeList< PasswordScreenView,
            touchgfx::meta::TypeList< ClockScreenView,
            touchgfx::meta::TypeList< LogScreenView,
            touchgfx::meta::TypeList< SplashScreenView,
            touchgfx::meta::TypeList< SaverScreenView,
            touchgfx::meta::TypeList< DebugScreenView,
            touchgfx::meta::Nil > > > > > > > > > >
            > GeneratedViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedViewTypes >::type MaxGeneratedViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< MainPresenter,
            touchgfx::meta::TypeList< OffScreenPresenter,
            touchgfx::meta::TypeList< SettingsScreenPresenter,
            touchgfx::meta::TypeList< DisplayScreenPresenter,
            touchgfx::meta::TypeList< ServiceScreenPresenter,
            touchgfx::meta::TypeList< PasswordScreenPresenter,
            touchgfx::meta::TypeList< ClockScreenPresenter,
            touchgfx::meta::TypeList< LogScreenPresenter,
            touchgfx::meta::TypeList< SplashScreenPresenter,
            touchgfx::meta::TypeList< SaverScreenPresenter,
            touchgfx::meta::TypeList< DebugScreenPresenter,
            touchgfx::meta::Nil > > > > > > > > > >
            > GeneratedPresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedPresenterTypes >::type MaxGeneratedPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< touchgfx::NoTransition,
            touchgfx::meta::TypeList< SlideTransition<EAST>,
            touchgfx::meta::TypeList< WipeTransition<EAST>,
            touchgfx::meta::TypeList< SlideTransition<WEST>,
            touchgfx::meta::TypeList< WipeTransition<WEST>,
            touchgfx::meta::Nil > > > >
            > GeneratedTransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedTransitionTypes >::type MaxGeneratedTransitionType;

    virtual void gotoStartScreen(FrontendApplication& app)
    {
        app.gotoSplashScreenScreenNoTransition();
    }
protected:
    FrontendHeapBase(touchgfx::AbstractPartition& presenters, touchgfx::AbstractPartition& views, touchgfx::AbstractPartition& transitions, FrontendApplication& app)
        : MVPHeap(presenters, views, transitions, app)
    {

    }

};

#endif // FRONTENDHEAPBASE_HPP
