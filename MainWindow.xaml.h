#pragma once

#include "MainWindow.g.h"

namespace winrt::RSSN::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        //{
        //    // Xaml objects should not call InitializeComponent during construction.
        //    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        //    this->ExtendsContentIntoTitleBar(true);
        //    this->SetTitleBar(AppTitleBar());
        //}
        int32_t MyProperty();
        void MyProperty(int32_t value);
        void ClassNameHyperlinkButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::RSSN::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
