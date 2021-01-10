#pragma once

#include <memory>
#include <iostream>

#include <QFormLayout>

#include "../properties.hpp"
#include "boolean.hpp"

namespace tct::properties::qt_widgets
{
    class factory
    {
    public:
        template<typename T>
        [[nodiscard]] static std::unique_ptr<QWidget> build_widget(property<T>& p)
        {
            if constexpr (std::is_same_v<T, bool>)
                return std::make_unique<boolean>();

            return nullptr;
        }

        [[nodiscard]] static std::unique_ptr<QWidget> build_form(tct::properties::properties& p)
        {
            // Layout
            QFormLayout* layout = new QFormLayout;
            for (const auto& it : p) {
                std::cout << it.first << ": " << it.second << std::endl;
            }

            // Widget
            auto w = std::make_unique<QWidget>();
            w->setLayout(layout);

            return nullptr;
        }
    };

}

