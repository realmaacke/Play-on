#include "presentation/views/SettingsView.hpp"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "gtkmm/widget.h"
#include "presentation/views/settingViews/AccountView.hpp"
#include "presentation/views/settingViews/BaseSettingView.hpp"
#include "presentation/views/settingViews/GeneralView.hpp"
#include "presentation/views/settingViews/ProviderView.hpp"

void SettingsView::load_ui() {
    m_builder = Gtk::Builder::create_from_file("resources/ui/settings.ui");

    m_inner_sidebar = m_builder->get_widget<Gtk::Box>("settings_inner_sidebar");
    m_nav_box = m_builder->get_widget<Gtk::Box>("settings_nav_box");
    m_stack = m_builder->get_widget<Gtk::Stack>("settings_stack");

    append(*m_inner_sidebar);
    append(*m_stack);

    this->build_ui();
}

void SettingsView::build_ui() {
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_hexpand(true);
    set_vexpand(true);

    m_pages = {
        Gtk::make_managed<AccountView>(),
        Gtk::make_managed<ProviderView>(),
        Gtk::make_managed<GeneralView>(),
    };

    add_section("Account", "user-symbolic", "account");
    add_section("Provider", "network-wireless-symbolic", "provider");
    add_section("General", "view-filter-symbolic", "general");

    for (auto *page : m_pages) {
        register_view(page);
    }

    navigate_to("account");
}

void SettingsView::register_view(BaseSettingView *view) {
    m_stack->add(*view, view->get_name());
    m_page_map[view->get_name()] = view;
    view->load_ui();
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

    btn->signal_clicked().connect([this, btn, page]() {
        navigate_to(page);
        if (m_active_btn)
            m_active_btn->remove_css_class("active");
        btn->add_css_class("active");
        m_active_btn = btn;
    });

    m_nav_box->append(*btn);
}