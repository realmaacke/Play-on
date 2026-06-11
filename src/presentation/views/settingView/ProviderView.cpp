#include "presentation/views/settingViews/ProviderView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"

void ProviderView::build_ui() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_hexpand(true);
    set_vexpand(true);
    add_css_class("settings-provider");

    auto manage_section = build_provider_management();
    auto list_section = build_provider_list();

    append(*manage_section);
    append(*list_section);
}

Gtk::Box *ProviderView::build_provider_management() {
    auto section = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 12);
    section->set_hexpand(true);
    section->set_vexpand(false);
    section->add_css_class("settings-provider-manage-section");

    // Title
    auto title = Gtk::make_managed<Gtk::Label>("Add new Provider");
    title->set_halign(Gtk::Align::START);
    title->add_css_class("settings-provider-manage-label");
    section->append(*title);

    // Toggle buttons: Credentials / M3U
    auto toggle_box =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 0);
    toggle_box->add_css_class("provider-toggle-box");

    auto btn_credentials = Gtk::make_managed<Gtk::Button>("Credentials");
    auto btn_m3u = Gtk::make_managed<Gtk::Button>("M3U URL");
    btn_credentials->add_css_class("provider-toggle-btn");
    btn_credentials->add_css_class("active");
    btn_m3u->add_css_class("provider-toggle-btn");
    btn_credentials->set_hexpand(true);
    btn_m3u->set_hexpand(true);
    toggle_box->append(*btn_credentials);
    toggle_box->append(*btn_m3u);
    section->append(*toggle_box);

    // Credentials form
    auto credentials_box =
        Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
    credentials_box->set_hexpand(true);

    auto name_entry = Gtk::make_managed<Gtk::Entry>();
    auto username_entry = Gtk::make_managed<Gtk::Entry>();
    auto password_entry = Gtk::make_managed<Gtk::Entry>();
    auto portal_entry = Gtk::make_managed<Gtk::Entry>();
    name_entry->set_placeholder_text("Name...");
    username_entry->set_placeholder_text("Username...");
    password_entry->set_placeholder_text("Password...");
    password_entry->set_visibility(false);
    portal_entry->set_placeholder_text("Portal URL...");
    name_entry->add_css_class("provider-entry");
    username_entry->add_css_class("provider-entry");
    password_entry->add_css_class("provider-entry");
    portal_entry->add_css_class("provider-entry");
    credentials_box->append(*name_entry);
    credentials_box->append(*username_entry);
    credentials_box->append(*password_entry);
    credentials_box->append(*portal_entry);

    // M3U form
    auto m3u_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 8);
    m3u_box->set_hexpand(true);

    auto m3u_name_entry = Gtk::make_managed<Gtk::Entry>();
    auto m3u_entry = Gtk::make_managed<Gtk::Entry>();
    m3u_name_entry->set_placeholder_text("Name...");
    m3u_entry->set_placeholder_text("M3U URL...");
    m3u_name_entry->add_css_class("provider-entry");
    m3u_entry->add_css_class("provider-entry");
    m3u_box->append(*m3u_name_entry);
    m3u_box->append(*m3u_entry);

    // Input stack
    m_input_stack.add(*credentials_box, "credentials");
    m_input_stack.add(*m3u_box, "m3u");
    m_input_stack.set_visible_child(*credentials_box);
    section->append(m_input_stack);

    // Toggle logic
    btn_credentials->signal_clicked().connect(
        [this, btn_credentials, btn_m3u, credentials_box]() {
            m_input_stack.set_visible_child(*credentials_box);
            btn_credentials->add_css_class("active");
            btn_m3u->remove_css_class("active");
        });
    btn_m3u->signal_clicked().connect(
        [this, btn_credentials, btn_m3u, m3u_box]() {
            m_input_stack.set_visible_child(*m3u_box);
            btn_m3u->add_css_class("active");
            btn_credentials->remove_css_class("active");
        });

    // Add button
    auto add_btn = Gtk::make_managed<Gtk::Button>("Add Provider");
    add_btn->add_css_class("provider-add-btn");
    add_btn->set_halign(Gtk::Align::END);
    add_btn->signal_clicked().connect([this, name_entry, username_entry,
                                       password_entry, portal_entry,
                                       m3u_name_entry, m3u_entry]() {
        Provider p;
        if (m_input_stack.get_visible_child_name() == "credentials") {
            p.name = name_entry->get_text();
            p.type = "credentials";
        } else {
            p.name = m3u_name_entry->get_text();
            p.type = "m3u";
        }
        if (p.name.empty())
            return;
        m_providers.push_back(p);
        refresh_list();
    });
    section->append(*add_btn);

    return section;
}

Gtk::Box *ProviderView::build_provider_list() {
    auto wrapper = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
    wrapper->set_hexpand(true);
    wrapper->set_vexpand(true);
    wrapper->add_css_class("settings-provider-list-wrapper");

    auto list_title = Gtk::make_managed<Gtk::Label>("Providers");
    list_title->set_halign(Gtk::Align::START);
    list_title->add_css_class("settings-provider-list-title");
    wrapper->append(*list_title);

    m_providers_list.set_orientation(Gtk::Orientation::VERTICAL);
    m_providers_list.set_hexpand(true);
    m_providers_list.add_css_class("provider-list");
    wrapper->append(m_providers_list);

    return wrapper;
}

void ProviderView::refresh_list() {
    // Clear existing rows
    while (auto *child = m_providers_list.get_first_child()) {
        m_providers_list.remove(*child);
    }
    for (const auto &p : m_providers) {
        add_provider_row(p);
    }
}

void ProviderView::add_provider_row(const Provider &p) {
    auto row = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 12);
    row->set_hexpand(true);
    row->add_css_class("provider-row");

    // Type badge
    auto badge =
        Gtk::make_managed<Gtk::Label>(p.type == "m3u" ? "M3U" : "CREDS");
    badge->add_css_class("provider-badge");

    // Name
    auto name_lbl = Gtk::make_managed<Gtk::Label>(p.name);
    name_lbl->set_halign(Gtk::Align::START);
    name_lbl->set_hexpand(true);
    name_lbl->add_css_class("provider-row-name");

    auto active_btn = Gtk::make_managed<Gtk::Button>("Activate");
    active_btn->add_css_class("provider-row-btn");
    active_btn->add_css_class("provider-row-btn-success");

    // Edit button
    auto edit_btn = Gtk::make_managed<Gtk::Button>("Edit");
    edit_btn->add_css_class("provider-row-btn");

    // Delete button
    auto del_btn = Gtk::make_managed<Gtk::Button>("Delete");
    del_btn->add_css_class("provider-row-btn");
    del_btn->add_css_class("provider-row-btn-danger");
    del_btn->signal_clicked().connect([this, p]() {
        m_providers.erase(std::remove_if(m_providers.begin(), m_providers.end(),
                                         [&p](const Provider &x) {
                                             return x.name == p.name;
                                         }),
                          m_providers.end());
        refresh_list();
    });

    row->append(*badge);
    row->append(*name_lbl);
    row->append(*active_btn);
    row->append(*edit_btn);
    row->append(*del_btn);
    m_providers_list.append(*row);
}