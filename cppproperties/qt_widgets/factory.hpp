#pragma once

#include <memory>

#include <QFormLayout>

#include "../properties.hpp"
#include "boolean.hpp"
#include "integer.hpp"
#include "nested.hpp"

namespace tct::properties::qt_widgets
{

    class factory
    {
    private:
        template<typename T>
        [[nodiscard]]
        static
        bool
        is_type(property_base* pb)
        {
            return dynamic_cast<property<T>*>(pb) != nullptr;
        }

        template<typename T_raw, typename T_editor>
        [[nodiscard]]
        static
        std::unique_ptr<QWidget> build_widget(property_base* pb)
        {
            // Make sure the editor can handle this type
            static_assert(std::is_same_v<T_raw, typename T_editor::type>);

            // Convert to property<T>*
            property<T_raw>* p = dynamic_cast<property<T_raw>*>(pb);
            if (!p)
                return nullptr;

            return std::make_unique<T_editor>(*p);
        }

    public:
        [[nodiscard]]
        static
        std::unique_ptr<QWidget>
        build_widget(property_base* pb)
        {
            // Sanity check
            if (!pb)
                return nullptr;

            // Get the appropriate widget
            // ToDo: Improve this. Use self-registering factory type pattern
            {
                if (is_type<bool>(pb))
                    return build_widget<bool, boolean>(pb);

                if (is_type<int>(pb))
                    return build_widget<int, integer>(pb);
            }

            return nullptr;
        }

        [[nodiscard]]
        static
        std::unique_ptr<QWidget> build_form(tct::properties::properties& p)
        {
            // Layout
            QFormLayout* layout = new QFormLayout;
            for (const auto& [property_name, property_value] : p) {
                // Get widget
                std::unique_ptr<QWidget> w;
                {
                    // Nested?
                    if (auto n = p.get_nested_properties(property_name); n)
                        w = std::make_unique<nested>();

                    // Regular property
                    else
                        w = build_widget(property_value);
                }
                if (!w)
                    w = std::make_unique<QWidget>();

                // Add to layout
                layout->addRow(QString::fromStdString(property_name), w.release());
            }

            // Widget
            auto w = std::make_unique<QWidget>();
            w->setLayout(layout);

            return w;
        }
    };

}
