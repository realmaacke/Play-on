#include "presentation/views/SettingsView.hpp"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "presentation/views/settingViews/AccountView.hpp"
#include "presentation/views/settingViews/BaseSettingView.hpp"

void SettingsView::load_ui() {
    std::cout << "SettingsView::load_ui\n";
    m_builder = Gtk::Builder::create_from_file("resources/ui/settings.ui");

    if (!m_builder) {
        std::cerr << "Failed to load the ui file with builder\n";
        return;
    }

    m_inner_sidebar = m_builder->get_widget<Gtk::Box>("settings_inner_sidebar");

    if (!m_inner_sidebar) {
        std::cerr << "Failed to load inner sidebar\n";
        return;
    }

    m_nav_box = m_builder->get_widget<Gtk::Box>("settings_nav_box");

    if (!m_nav_box) {
        std::cerr << "Failed to load nav_box\n";
        return;
    }

    m_stack = m_builder->get_widget<Gtk::Stack>("settings_stack");

    if (!m_stack) {
        std::cerr << "Failed to find settings_stack in UI file\n";
        return;
    }

    std::cout << "sidebar = " << m_inner_sidebar << '\n';
    std::cout << "nav_box = " << m_nav_box << '\n';
    std::cout << "stack = " << m_stack << '\n';

    append(*m_inner_sidebar);
    append(*m_stack);
}

void SettingsView::build_ui() {
    std::cout << "SettingsView::build_ui\n";
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_hexpand(true);
    set_vexpand(true);

    m_pages = {
        Gtk::make_managed<AccountView>(),
        Gtk::make_managed<AccountView>(),
        Gtk::make_managed<AccountView>(),
    };

    // add_section("Account", "user-symbolic", "account");
    // add_section("Account", "user-symbolic", "account");
    // add_section("Account", "user-symbolic", "account");
    // add_section("Provider", "network-wireless-symbolic", "provider");
    // add_section("General", "view-filter-symbolic", "general");

    // for (auto *page : m_pages) {
    //     register_view(page);
    // }

    // m_stack->set_hexpand(true);
    // m_stack->set_vexpand(true);

    // navigate_to("account");
}

void SettingsView::register_view(BaseSettingView *view) {
    view->load_ui();
    view->build_ui();
    m_page_map[view->get_name()] = view;
    m_stack->add(*view, view->get_name());
}

void SettingsView::navigate_to(const std::string &page) {
    auto it = m_page_map.find(page);
    if (it != m_page_map.end()) {
        m_stack->set_visible_child(*it->second);
    }
}

void SettingsView::add_section(const std::string &label,
                               const std::string &icon_name,
                               const std::string &page) {

    auto btn = Gtk::make_managed<Gtk::Button>();
    btn->set_hexpand(true);
    btn->set_size_request(-1, 64);
    btn->add_css_class("settings-nav-item");

    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 12);
    hbox->set_halign(Gtk::Align::START);
    hbox->set_margin_start(8);

    auto icon = Gtk::make_managed<Gtk::Image>();
    icon->set_from_icon_name(icon_name);
    icon->set_pixel_size(20);
    icon->set_opacity(0.75);

    auto lbl = Gtk::make_managed<Gtk::Label>(label);
    lbl->set_halign(Gtk::Align::START);

    hbox->append(*icon);
    hbox->append(*lbl);
    btn->set_child(*hbox);

    m_nav_box->append(*btn);

    // btn->signal_clicked().connect([this, btn, page]() {
    //     navigate_to(page);
    //     if (m_active_btn)
    //         m_active_btn->remove_css_class("active");
    //     btn->add_css_class("active");
    //     m_active_btn = btn;
    // });
    // m_nav_box->append(*btn);
}