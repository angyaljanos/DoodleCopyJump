#ifdef MEMTRACE
#include "gtest_lite.h"
#include "SDL_Fake.h"
#include "Display.h"
#include "Menu.hpp"

int main() {
    
    TEST(Display, Sanity) {
        FakeSDLMakeError(true);
        EXPECT_THROW(Display d, std::logic_error&);
        FakeSDLMakeError(false);
        EXPECT_NO_THROW(Display d);
    } ENDM
    
    Display d;
    
    TEST(Menu, Draw) {
        SDL_Event event;
        Vector2D mousePosition(0, 0);
        Menu menu;
        EXPECT_NO_THROW(menu.DrawMenu(d, mousePosition,event));
    } ENDM
    
    TEST(Menu, Select) {
        SDL_Event event;
        event.type = SDL_MOUSEBUTTONDOWN;
        Vector2D mousePosition(25.0, 25.0);
        Menu menu;
        int ret = menu.chooseMenu(mousePosition, event);
        EXPECT_EQ(0, ret);
    } ENDM
    
    TEST(Playground, Sanity) {
        EXPECT_NO_THROW(
                Playground p(d);
                p.Draw(d);
                );
    } ENDM
    
    return 0;
}

#endif