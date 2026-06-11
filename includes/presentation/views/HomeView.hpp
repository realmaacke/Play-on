#pragma once
#include <gtkmm.h>
#include "presentation/views/BaseView.hpp"

class HomeView : public BaseView
{
public:
    HomeView() : BaseView("home", "home-view") {}
    void build_ui() override;

    sigc::signal<void(std::string)> signal_navigate;

private:
    Gtk::Box m_center_box;
    Gtk::Label m_title;
    Gtk::Box m_grid;

    void add_card(
        const std::string &label,
        const std::string &view);
};
