#pragma once
#include "gtkmm/button.h"
#include "gtkmm/image.h"
#include "gtkmm/label.h"
#include "presentation/views/BaseView.hpp"
#include <functional>
#include <gtkmm.h>
#include <vector>

class Sidebar : public BaseView {
  public:
    Sidebar(std::function<void(const std::string &)> on_navigate)
        : BaseView("sidebar", "sidebar"), m_on_navigate(on_navigate) {
        setup_hover();
    }
    void build_ui() override;
    void load_ui() override;

  private:
    void setup_hover();
    void set_collapsed(bool collapsed);

    Gtk::Box *m_nav_box = nullptr;
    Gtk::Image *m_logo_image = nullptr;

    Gtk::Button *m_active_btn = nullptr;
    std::vector<Gtk::Label *> m_nav_labels;
    bool m_collapsed = true;
    std::function<void(const std::string &)> m_on_navigate;
};